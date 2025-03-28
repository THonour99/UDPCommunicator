#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QString>
#include <QMap>

class Authentication
{
public:
    Authentication();
    bool authenticate(const QString &username, const QString &password);
    void addUser(const QString &username, const QString &password);

private:
    QMap<QString, QString> m_users; // 用户名->密码映射
};

#endif // AUTHENTICATION_H
