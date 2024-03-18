QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ball.cpp \
    gamescene.cpp \
    main.cpp \
    mainwindow.cpp \
    server.cpp \
    sprite.cpp \
    threadmanager.cpp \
    wall.cpp

HEADERS += \
    ball.h \
    gamescene.h \
    mainwindow.h \
    server.h \
    sprite.h \
    threadmanager.h \
    wall.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
