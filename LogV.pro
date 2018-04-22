#-------------------------------------------------
#
# Project created by QtCreator 2018-04-14T14:55:44
#
#-------------------------------------------------

QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LogV
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    logvisualwidget.cpp \
    customtabstyle.cpp \
    logdataviewer.cpp \
    downloader.cpp \
    datareader.cpp \
    visualcenter.cpp

HEADERS += \
        mainwindow.h \
    logvisualwidget.h \
    customtabstyle.h \
    logdataviewer.h \
    downloader.h \
    datareader.h \
    own.h \
    visualcenter.h

FORMS += \
        mainwindow.ui \
    logvisualwidget.ui \
    logdataviewer.ui \
    form.ui \
    visualcenter.ui
INCLUDEPATH += -I /usr/include/python2.7/
LIBS += -L /usr/lib/python2.7 -lpython2.7
