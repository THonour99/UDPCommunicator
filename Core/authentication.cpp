#include "Authentication.h"

Authentication::Authentication()
{
    // 添加一些测试用户
    addUser("admin", "password");
    addUser("user", "123456");
}

bool Authentication::authenticate(const QString &username, const QString &password)
{
    if (m_users.contains(username)) {
        return m_users[username] == password;
    }
    return false;
}

void Authentication::addUser(const QString &username, const QString &password)
{
    m_users[username] = password;
}
