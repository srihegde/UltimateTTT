#-------------------------------------------------
#
# Project created by QtCreator 2015-10-29T15:39:19
#
#-------------------------------------------------

QT       += core gui

#CONFIG  += no_keywords

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UltimateTTT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    strategy.cpp \
    scoretracker.cpp

HEADERS  += mainwindow.h \
    strategy.h \
    scoretracker.h

FORMS    += \
    mainwindow.ui
