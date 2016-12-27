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

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    resource/HUNNU.png

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

RESOURCES += \
    res.qrc

RC_FILE = \
    resource/xSnow.rc
