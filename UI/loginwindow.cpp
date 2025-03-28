#include "LoginWindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setWindowTitle("用户登录");

    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginButtonClicked);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::onLoginButtonClicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "错误", "用户名和密码不能为空");
        return;
    }

    if (m_auth.authenticate(username, password)) {
        emit loginSuccessful();
    } else {
        QMessageBox::warning(this, "错误", "用户名或密码不正确");
    }
}
