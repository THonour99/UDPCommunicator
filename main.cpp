#include <QApplication>
#include "LoginWindow.h"
#include "ModeSelectionWindow.h"
#include "CommunicationWindow.h"
#include "AppManager.h"
#include "Logger.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 初始化日志
    Logger::instance()->logInfo("Application started");

    // 创建登录窗口
    LoginWindow loginWindow;

    // 创建模式选择窗口
    ModeSelectionWindow modeWindow;
    modeWindow.hide();

    // 登录成功后显示模式选择窗口
    QObject::connect(&loginWindow, &LoginWindow::loginSuccessful, [&]() {
        loginWindow.hide();
        modeWindow.show();
        Logger::instance()->logInfo("User logged in successfully");
    });

    // 选择模式后创建并显示相应的通信窗口
    QObject::connect(&modeWindow, &ModeSelectionWindow::modeSelected, [&](CommunicationMode mode) {
        modeWindow.hide();

        CommunicationWindow *commWindow = new CommunicationWindow(mode);
        commWindow->setAttribute(Qt::WA_DeleteOnClose);
        commWindow->show();

        // 通信窗口关闭后回到模式选择窗口
        QObject::connect(commWindow, &CommunicationWindow::destroyed, [&]() {
            modeWindow.show();
        });

        Logger::instance()->logInfo(mode == LocalMode ? "Local mode selected" : "Remote mode selected");
    });

    // 显示登录窗口
    loginWindow.show();

    return app.exec();
}
