#-------------------------------------------------
#
# Project created by QtCreator 2013-03-11T11:29:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = proj
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fileinfoex.cpp \
    duplicatesfinder.cpp \
    filesfinder.cpp \
    finderdialog.cpp \
    textformatter.cpp \
    directorytree.cpp \
    filemodel.cpp \
    NightCharts/nightcharts.cpp \
    chartdockwidget.cpp

HEADERS  += mainwindow.h \
    fileinfoex.h \
    duplicatesfinder.h \
    filesfinder.h \
    finderdialog.h \
    textformatter.h \
    directorytree.h \
    filemodel.h \
    NightCharts/nightcharts.h \
    chartdockwidget.h

FORMS    += mainwindow.ui \
    finderdialog.ui \
    directorytree.ui
