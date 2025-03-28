#include "CommunicationWindow.h"
#include "ui_communicationwindow.h"
#include "AppManager.h"
#include <QDateTime>

CommunicationWindow::CommunicationWindow(CommunicationMode mode, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommunicationWindow),
    m_mode(mode)
{
    ui->setupUi(this);

    // 根据模式设置窗口标题
    setWindowTitle(mode == LocalMode ? "本地通信" : "远程通信");

    // 设置模式标签文本
    ui->modeLabel->setText(mode == LocalMode ? "本地模式" : "远程模式");

    // 初始化UDP管理器
    m_udpManager = new UDPManager(mode, this);

    // 连接信号和槽
    connect(ui->sendButton, &QPushButton::clicked, this, &CommunicationWindow::onSendButtonClicked);
    connect(m_udpManager, &UDPManager::messageReceived, this, &CommunicationWindow::onMessageReceived);
    connect(ui->backButton, &QPushButton::clicked, this, &CommunicationWindow::onBackButtonClicked);

    // 设置应用程序状态
    AppManager::instance()->setCurrentMode(mode);
}

CommunicationWindow::~CommunicationWindow()
{
    // 重置应用程序状态
    AppManager::instance()->reset();
    delete ui;
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
