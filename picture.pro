#-------------------------------------------------
#
# Project created by QtCreator 2014-11-29T18:19:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = picture
TEMPLATE = app


SOURCES += main.cpp\
        picture.cpp \
    icondelegate.cpp

HEADERS  += picture.h \
    icondelegate.h

FORMS    += picture.ui

RESOURCES += \
    res.qrc
