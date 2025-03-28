#include "CommunicationWindow.h"
#include "ui_communicationwindow.h"
#include "AppManager.h"
#include <QDateTime>
#include"logger.h"
CommunicationWindow::CommunicationWindow(CommunicationMode mode, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommunicationWindow),
    m_mode(mode),
    m_isConnected(false)
{
    ui->setupUi(this);

    // 根据模式设置窗口标题
    setWindowTitle(mode == LocalMode ? "本地通信" : "远程通信");

    // 设置模式标签文本
    ui->modeLabel->setText(mode == LocalMode ? "本地模式" : "远程模式");

    // 设置默认IP和端口
    ui->ipLineEdit->setText("127.0.0.1");
    ui->portSpinBox->setText("8888");

    // 初始化UDP管理器
    m_udpManager = new UDPManager(mode, this);

    // 连接信号和槽
    connect(ui->sendButton, &QPushButton::clicked, this, &CommunicationWindow::onSendButtonClicked);
    connect(ui->connectButton, &QPushButton::clicked, this, &CommunicationWindow::onConnectButtonClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &CommunicationWindow::onBackButtonClicked);
    connect(m_udpManager, &UDPManager::messageReceived, this, &CommunicationWindow::onMessageReceived);
    connect(m_udpManager, &UDPManager::connectionStatusChanged, this, &CommunicationWindow::onConnectionStatusChanged);

    // 设置应用程序状态
    AppManager::instance()->setCurrentMode(mode);

    // 禁用发送按钮，直到连接成功
    ui->sendButton->setEnabled(false);

    // 日志记录
    Logger::instance()->logInfo(QString("%1 模式窗口已打开").arg(mode == LocalMode ? "本地" : "远程"));
}

CommunicationWindow::~CommunicationWindow()
{
    // 重置应用程序状态
    AppManager::instance()->reset();
    delete ui;
}
void CommunicationWindow::onConnectButtonClicked()
{

    QString ip = ui->ipLineEdit->text();
    int port = ui->portSpinBox->text().toInt();

    // 禁用连接按钮，避免重复点击
    ui->connectButton->setEnabled(false);
    ui->connectButton->setText("连接中...");

    // 显示连接尝试信息
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    ui->messagesTextEdit->append(QString("[%1] 系统: 正在连接到 %2:%3...").arg(timestamp).arg(ip).arg(port));

    // 尝试连接到指定的IP和端口
    Logger::instance()->logInfo(QString("尝试连接到 %1:%2").arg(ip).arg(port));

    // 连接UDPManager的pingProgress信号
    connect(m_udpManager, &UDPManager::pingProgress, this, [this](const QString &message) {
        QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
        ui->messagesTextEdit->append(QString("[%1] 系统: %2").arg(timestamp).arg(message));
    }, Qt::UniqueConnection);

    // 先ping然后再连接
    bool connected = m_udpManager->pingBeforeConnect(ip, port);

    // 恢复连接按钮状态
    ui->connectButton->setEnabled(true);
    ui->connectButton->setText("连接");

    // 根据连接结果更新UI
    ui->sendButton->setEnabled(connected);

    // 如果配置了状态标签，则更新它
    if (ui->statusLabel) {
        ui->statusLabel->setText(connected ? "已连接" : "未连接");
        ui->statusLabel->setStyleSheet(connected ? "color: green;" : "color: red;");
    }
}


void CommunicationWindow::onConnectionStatusChanged(bool connected, const QString &message)
{
    m_isConnected = connected;
    ui->sendButton->setEnabled(connected);

    // 在消息区域显示连接状态
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    ui->messagesTextEdit->append(QString("[%1] 系统: %2").arg(timestamp).arg(message));

    // 日志记录
    if (connected) {
        Logger::instance()->logInfo(message);
    } else {
        Logger::instance()->logWarning(message);
    }
}

void CommunicationWindow::onSendButtonClicked()
{
    QString message = ui->messageLineEdit->text();
    if (!message.isEmpty()) {
        m_udpManager->sendMessage(message);

        // 在消息记录中添加发送的消息
        QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
        ui->messagesTextEdit->append(QString("[%1] 你: %2").arg(timestamp).arg(message));

        // 清空输入框
        ui->messageLineEdit->clear();
    }
}

void CommunicationWindow::onMessageReceived(const QString &message, const QString &sender)
{
    // 在消息记录中添加接收到的消息
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    ui->messagesTextEdit->append(QString("[%1] %2: %3").arg(timestamp).arg(sender).arg(message));
}

void CommunicationWindow::onBackButtonClicked()
{
    this->hide();  // 先隐藏窗口
    emit returnRequested();  // 发出返回信号
    this->close();  // 然后关闭窗口
}
