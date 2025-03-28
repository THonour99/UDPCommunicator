#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QObject>

enum CommunicationMode {
    NoMode,
    LocalMode,
    RemoteMode
};

class AppManager : public QObject
{
    Q_OBJECT

public:
    static AppManager *instance();
    CommunicationMode currentMode() const;
    bool setCurrentMode(CommunicationMode mode);
    void reset();

signals:
    void modeChanged(CommunicationMode newMode);

private:
    explicit AppManager(QObject *parent = nullptr);
    static AppManager *m_instance;
    CommunicationMode m_currentMode;
};

#endif // APPMANAGER_H
