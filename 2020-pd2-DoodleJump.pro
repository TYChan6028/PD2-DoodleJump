#-------------------------------------------------
#
# Project created by QtCreator 2020-04-22T13:25:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2020-pd2-DoodleJump
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    player.cpp \
    game.cpp \
    platform.cpp \
    platform_g.cpp \
    platform_b.cpp \
    platgenerator.cpp \
    entity.cpp \
    prop.cpp \
    hazard.cpp \
    monster.cpp \
    bullet.cpp \
    blackhole.cpp \
    spring.cpp \
    pogoshoes.cpp \
    sidemenu.cpp \
    ggscene.cpp

HEADERS += \
        mainwindow.h \
    player.h \
    game.h \
    platform.h \
    platform_g.h \
    platform_b.h \
    platgenerator.h \
    entity.h \
    prop.h \
    hazard.h \
    monster.h \
    bullet.h \
    blackhole.h \
    spring.h \
    pogoshoes.h \
    sidemenu.h \
    ggscene.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
