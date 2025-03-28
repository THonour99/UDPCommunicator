#ifndef COMMUNICATIONWINDOW_H
#define COMMUNICATIONWINDOW_H

#include <QWidget>
#include "UDPManager.h"
#include "AppManager.h"
#include <QProcess>
namespace Ui {
class CommunicationWindow;
}

class CommunicationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CommunicationWindow(CommunicationMode mode, QWidget *parent = nullptr);
    ~CommunicationWindow();
signals:
    // 已有的其他信号...
    void returnRequested(); // 添加新信号，表示用户请求返回

private slots:
    void onSendButtonClicked();
    void onConnectButtonClicked();  // 确保添加这行
    void onMessageReceived(const QString &message, const QString &sender);
    void onBackButtonClicked();
    void onConnectionStatusChanged(bool connected, const QString &message);

private:
    Ui::CommunicationWindow *ui;
    UDPManager *m_udpManager;
    CommunicationMode m_mode;
    bool m_isConnected;
};

#endif // COMMUNICATIONWINDOW_H
