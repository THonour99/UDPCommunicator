#include "AppManager.h"

AppManager* AppManager::m_instance = nullptr;

AppManager *AppManager::instance()
{
    if (!m_instance) {
        m_instance = new AppManager();
    }
    return m_instance;
}

AppManager::AppManager(QObject *parent)
    : QObject(parent), m_currentMode(NoMode)
{
}

CommunicationMode AppManager::currentMode() const
{
    return m_currentMode;
}

bool AppManager::setCurrentMode(CommunicationMode mode)
{
    // 如果当前没有模式或者要切换至无模式，则可以设置
    if (m_currentMode == NoMode || mode == NoMode) {
        m_currentMode = mode;
        emit modeChanged(m_currentMode);
        return true;
    }
    // 已经在这个模式，返回true
    if (m_currentMode == mode) {
        return true;
    }
    // 其他情况，不能同时运行本地和远程模式
    return false;
}

void AppManager::reset()
{
    setCurrentMode(NoMode);
}
