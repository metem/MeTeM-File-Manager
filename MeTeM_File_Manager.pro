#-------------------------------------------------
#
# Project created by QtCreator 2013-03-11T11:29:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MeTeM_File_Manager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fileinfoex.cpp \
    duplicatesfinder.cpp \
    filesfinder.cpp \
    finderdialog.cpp \
    directorytree.cpp \
    filemodel.cpp \
    NightCharts/nightcharts.cpp \
    filechartdockview.cpp \
    comparatordialog.cpp \
    aboutbox.cpp

HEADERS  += mainwindow.h \
    fileinfoex.h \
    duplicatesfinder.h \
    filesfinder.h \
    finderdialog.h \
    textformatter.h \
    directorytree.h \
    filemodel.h \
    NightCharts/nightcharts.h \
    filechartdockview.h \
    comparatordialog.h \
    aboutbox.h

FORMS    += mainwindow.ui \
    finderdialog.ui \
    directorytree.ui \
    comparatordialog.ui \
    aboutbox.ui

RESOURCES += \
    icons.qrc