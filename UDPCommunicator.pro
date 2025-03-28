QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += \
    $$PWD/Core \
    $$PWD/UI \
    $$PWD/Network \
    $$PWD/Utils
SOURCES += \
    Core/appmanager.cpp \
    Core/authentication.cpp \
    Network/udpmanager.cpp \
    UI/communicationwindow.cpp \
    UI/loginwindow.cpp \
    UI/modeselectionwindow.cpp \
    Utils/logger.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Core/appmanager.h \
    Core/authentication.h \
    Network/udpmanager.h \
    UI/communicationwindow.h \
    UI/loginwindow.h \
    UI/modeselectionwindow.h \
    Utils/logger.h \
    mainwindow.h

FORMS += \
    UI/communicationwindow.ui \
    UI/loginwindow.ui \
    UI/modeselectionwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
