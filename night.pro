#-------------------------------------------------
#
# Project created by QtCreator 2023-05-11T22:57:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = night
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    startmenu.cpp \
    gamewindow.cpp \
    player.cpp \
    playerangle.cpp \
    enemy.cpp \
    dropitem.cpp \
    bullet.cpp \
    playerelf.cpp \
    enemydemon.cpp \
    subject.cpp \
    choosehero.cpp \
    playerwizzard.cpp \
    shop.cpp \
    enemyzombie.cpp \
    gameover.cpp \
    customdialog.cpp \
    pet.cpp

HEADERS += \
        widget.h \
    startmenu.h \
    gamewindow.h \
    config.h \
    player.h \
    playerangle.h \
    enemy.h \
    dropitem.h \
    bullet.h \
    playerelf.h \
    enemydemon.h \
    subject.h \
    choosehero.h \
    playerwizzard.h \
    shop.h \
    enemyzombie.h \
    gameover.h \
    customdialog.h \
    pet.h

FORMS += \
        widget.ui

RESOURCES += \
    res.qrc \
    res.qrc

DISTFILES +=
