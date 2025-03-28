#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "Authentication.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

signals:
    void loginSuccessful();

private slots:
    void onLoginButtonClicked();

private:
    Ui::LoginWindow *ui;
    Authentication m_auth;
};

#endif // LOGINWINDOW_H
