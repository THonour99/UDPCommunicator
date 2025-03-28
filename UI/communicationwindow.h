#ifndef COMMUNICATIONWINDOW_H
#define COMMUNICATIONWINDOW_H

#include <QWidget>
#include "UDPManager.h"
#include "AppManager.h"

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
    void onMessageReceived(const QString &message, const QString &sender);
    void onBackButtonClicked();

private:
    Ui::CommunicationWindow *ui;
    UDPManager *m_udpManager;
    CommunicationMode m_mode;
};

#endif // COMMUNICATIONWINDOW_H
