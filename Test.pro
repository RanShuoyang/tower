#-------------------------------------------------
#
# Project created by QtCreator 2020-06-22T19:14:25
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
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
    enemy.cpp \
    towerposition.cpp \
    tower.cpp \
    track.cpp \
    bullet.cpp \
    easymode.cpp \
    button.cpp \
    choosemode.cpp \
    end.cpp \
    hardmode.cpp \
    introduce.cpp

HEADERS += \
        mainwindow.h \
    enemy.h \
    towerposition.h \
    tower.h \
    track.h \
    bullet.h \
    check_enemy.h \
    easymode.h \
    button.h \
    choosemode.h \
    end.h \
    hardmode.h \
    introduce.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    picture.qrc
