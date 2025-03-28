#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

class Logger
{
public:
    static Logger *instance();

    void logInfo(const QString &message);
    void logWarning(const QString &message);
    void logError(const QString &message);

private:
    Logger();
    ~Logger();

    void log(const QString &level, const QString &message);

    static Logger *m_instance;
    QFile m_logFile;
    QTextStream m_textStream;
};

#endif // LOGGER_H
