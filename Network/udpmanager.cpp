#include "UDPManager.h"
#include <QNetworkDatagram>
#include <QDebug>

UDPManager::UDPManager(CommunicationMode mode, QObject *parent)
    : QObject(parent), m_mode(mode), m_isConnected(false)
{
    // 创建UDP Socket
    m_socket = new QUdpSocket(this);

    if (m_mode == LocalMode) {
        m_localPort = 7777;  // 本地模式监听端口
    } else {
        m_localPort = 7779;  // 远程模式监听端口
    }

    // 默认远程地址和端口
    m_remoteAddress = QHostAddress::LocalHost;
    m_remotePort = 8888;

    // 绑定本地端口
    if (m_socket->bind(QHostAddress::Any, m_localPort)) {
        qDebug() << "UDP socket bound to port" << m_localPort;
        emit connectionStatusChanged(true, QString("监听端口 %1").arg(m_localPort));
    } else {
        qDebug() << "Failed to bind UDP socket to port" << m_localPort;
        emit connectionStatusChanged(false, QString("无法绑定端口 %1").arg(m_localPort));
    }

    // 连接数据接收信号
    connect(m_socket, &QUdpSocket::readyRead, this, &UDPManager::processPendingDatagrams);
}

UDPManager::~UDPManager()
{
    if (m_socket) {
        m_socket->close();
    }
}

void UDPManager::sendMessage(const QString &message)
{
    QByteArray datagram = message.toUtf8();
    qint64 result = m_socket->writeDatagram(datagram, m_remoteAddress, m_remotePort);

    if (result == -1) {
        qDebug() << "Failed to send message:" << m_socket->errorString();
    } else {
        qDebug() << "Message sent to" << m_remoteAddress.toString() << ":" << m_remotePort;
    }
}

void UDPManager::processPendingDatagrams()
{
    while (m_socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = m_socket->receiveDatagram();
        QString message = QString::fromUtf8(datagram.data());
        QString sender = datagram.senderAddress().toString() + ":" + QString::number(datagram.senderPort());

        qDebug() << "Received message from" << sender << ":" << message;

        emit messageReceived(message, sender);
    }
}

bool UDPManager::connectToHost(const QString &hostAddress, int port)
{
    // 更新远程地址和端口
    m_remoteAddress = QHostAddress(hostAddress);
    m_remotePort = port;

    // 简单的连通性测试，发送一个测试消息
    QByteArray datagram = "CONNECTION_TEST";
    qint64 result = m_socket->writeDatagram(datagram, m_remoteAddress, m_remotePort);

    if (result == -1) {
        qDebug() << "Failed to connect:" << m_socket->errorString();
        m_isConnected = false;
        emit connectionStatusChanged(false, "连接失败: " + m_socket->errorString());
        return false;
    } else {
        qDebug() << "Successfully connected to" << m_remoteAddress.toString() << ":" << m_remotePort;
        m_isConnected = true;
        emit connectionStatusChanged(true, QString("已连接到 %1:%2").arg(hostAddress).arg(port));
        return true;
    }
}

bool UDPManager::pingBeforeConnect(const QString &hostAddress, int port)
{
    // 更新远程地址和端口
    m_remoteAddress = QHostAddress(hostAddress);
    m_remotePort = port;

    emit pingProgress("开始 Ping " + hostAddress + "...");

    // 创建ping进程
    if (m_pingProcess) {
        m_pingProcess->kill();
        m_pingProcess->deleteLater();
    }

    m_pingProcess = new QProcess(this);

    // 连接信号以读取输出
    connect(m_pingProcess, &QProcess::readyReadStandardOutput, [this]() {
        QString output = QString::fromLocal8Bit(m_pingProcess->readAllStandardOutput());
        emit pingProgress(output);
    });

    // 设置ping完成处理
    QEventLoop loop;
    bool pingSuccess = false;

    connect(m_pingProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [this, &loop, &pingSuccess](int exitCode, QProcess::ExitStatus exitStatus) {
                if (exitCode == 0) {
                    pingSuccess = true;
                    emit pingProgress("Ping成功 - 目标可达");
                } else {
                    emit pingProgress("Ping失败 - 目标不可达");
                }
                loop.quit();
            });

    // 设置ping命令参数
    QStringList arguments;
#ifdef Q_OS_WIN
    arguments << "-n" << "2" << "-w" << "1000" << hostAddress;  // Windows: 2次尝试，每次超时1秒
#else
    arguments << "-c" << "2" << "-W" << "1" << hostAddress;  // Linux/macOS: 2次尝试，每次超时1秒
#endif

    // 启动ping命令
    m_pingProcess->start("ping", arguments);

    // 等待ping完成
    loop.exec();

    // 清理
    m_pingProcess->deleteLater();
    m_pingProcess = nullptr;

    // 如果ping成功，则设置连接状态
    if (pingSuccess) {
        m_isConnected = true;
        emit connectionStatusChanged(true, "目标可达，连接成功");
    } else {
        m_isConnected = false;
        emit connectionStatusChanged(false, "目标不可达，连接失败");
    }

    return pingSuccess;
}
