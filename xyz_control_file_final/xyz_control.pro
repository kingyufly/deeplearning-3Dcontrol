#-------------------------------------------------
#
# Project created by QtCreator 2011-11-06T21:37:41
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += multimediawidgets

contains(QT_VERSION, ^5\\..*\\..*): QT += widgets

TARGET = xyz_control
TEMPLATE = app

include(src/qextserialport.pri)

SOURCES += main.cpp\
        mainwindow.cpp\
        hled.cpp

HEADERS  += mainwindow.h \
            hled.h

FORMS    += mainwindow.ui
