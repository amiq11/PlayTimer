#-------------------------------------------------
#
# Project created by QtCreator 2013-11-21T00:11:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlayTimer
TEMPLATE = app


SOURCES += main.cpp\
        playtimerwindow.cpp \
    processdetector.cpp

HEADERS  += playtimerwindow.h \
    processdetector.h

FORMS    += playtimerwindow.ui

RESOURCES += \
    resources.qrc
