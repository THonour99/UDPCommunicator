#ifndef UDPMANAGER_H
#define UDPMANAGER_H

#include <QObject>
#include <QUdpSocket>
#include "AppManager.h"
#include <QProcess>
#include <QEventLoop>
class UDPManager : public QObject
{
    Q_OBJECT

public:
    explicit UDPManager(CommunicationMode mode, QObject *parent = nullptr);
    ~UDPManager();

    void sendMessage(const QString &message);
    bool connectToHost(const QString &hostAddress, int port);
    bool pingBeforeConnect(const QString &hostAddress, int port);


signals:
    void messageReceived(const QString &message, const QString &sender);
    void connectionStatusChanged(bool connected, const QString &message);
    void pingProgress(const QString &message);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket *m_socket;
    QProcess *m_pingProcess = nullptr;
    CommunicationMode m_mode;
    int m_localPort;
    QHostAddress m_remoteAddress;
    int m_remotePort;
    bool m_isConnected;
};

#endif // UDPMANAGER_H
