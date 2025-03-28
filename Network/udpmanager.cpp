#include "UDPManager.h"
#include <QNetworkDatagram>
#include <QDebug>

UDPManager::UDPManager(CommunicationMode mode, QObject *parent)
    : QObject(parent), m_mode(mode)
{
    // 创建UDP Socket
    m_socket = new QUdpSocket(this);

    if (m_mode == LocalMode) {
        // 本地模式配置
        m_localPort = 7777;
        m_remotePort = 7778;
        m_remoteAddress = QHostAddress::LocalHost;
    } else {
        // 远程模式配置
        m_localPort = 7779;
        m_remotePort = 8888;  // Python服务器端口
        m_remoteAddress = QHostAddress::LocalHost; // 可以更改为实际的远程地址
    }

    // 绑定本地端口
    if (m_socket->bind(QHostAddress::Any, m_localPort)) {
        qDebug() << "UDP socket bound to port" << m_localPort;
    } else {
        qDebug() << "Failed to bind UDP socket to port" << m_localPort;
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
