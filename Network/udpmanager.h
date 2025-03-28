#ifndef UDPMANAGER_H
#define UDPMANAGER_H

#include <QObject>
#include <QUdpSocket>
#include "AppManager.h"

class UDPManager : public QObject
{
    Q_OBJECT

public:
    explicit UDPManager(CommunicationMode mode, QObject *parent = nullptr);
    ~UDPManager();

    void sendMessage(const QString &message);

signals:
    void messageReceived(const QString &message, const QString &sender);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket *m_socket;
    CommunicationMode m_mode;
    int m_localPort;
    QHostAddress m_remoteAddress;
    int m_remotePort;
};

#endif // UDPMANAGER_H
