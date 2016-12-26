#-------------------------------------------------
#
# Project created by QtCreator 2016-12-26T12:59:37
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HunnuStuInfoLookupTool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    resultswnd.cpp \
    aboutwnd.cpp

HEADERS  += mainwindow.h \
    resultswnd.h \
    aboutwnd.h \
    xsnow.h

FORMS    += mainwindow.ui \
    resultswnd.ui \
    aboutwnd.ui

CONFIG += mobility
MOBILITY = 

