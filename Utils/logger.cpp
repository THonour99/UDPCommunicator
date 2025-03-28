#include "Logger.h"
#include <QDir>

Logger* Logger::m_instance = nullptr;

Logger *Logger::instance()
{
    if (!m_instance) {
        m_instance = new Logger();
    }
    return m_instance;
}

Logger::Logger()
{
    QString logFileName = QDir::currentPath() + "/application.log";
    m_logFile.setFileName(logFileName);

    if (m_logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        m_textStream.setDevice(&m_logFile);
    }
}

Logger::~Logger()
{
    if (m_logFile.isOpen()) {
        m_logFile.close();
    }
}

void Logger::log(const QString &level, const QString &message)
{
    if (m_logFile.isOpen()) {
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        m_textStream << QString("[%1] [%2] %3\n").arg(timestamp).arg(level).arg(message);
        m_textStream.flush();
    }
}

void Logger::logInfo(const QString &message)
{
    log("INFO", message);
}

void Logger::logWarning(const QString &message)
{
    log("WARNING", message);
}

void Logger::logError(const QString &message)
{
    log("ERROR", message);
}
