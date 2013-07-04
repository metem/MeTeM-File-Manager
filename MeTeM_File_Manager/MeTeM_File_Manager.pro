#-------------------------------------------------
#
# Project created by QtCreator 2013-07-04T23:14:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MeTeM_File_Manager
TEMPLATE = app


SOURCES += \
    mainwindow.cpp \
    main.cpp \
    filechartdockview.cpp \
    finderdialog.cpp \
    filesfinder.cpp \
    filemodel.cpp \
    fileinfoex.cpp \
    duplicatesfinder.cpp \
    directorytree.cpp \
    comparatordialog.cpp \
    aboutbox.cpp \
    NightCharts/nightcharts.cpp

HEADERS  += \
    qexfile.h \
    mainwindow.h \
    textformatter.h \
    duplicatesfinder.h \
    finderdialog.h \
    filesfinder.h \
    filemodel.h \
    fileinfoex.h \
    filechartdockview.h \
    directorytree.h \
    comparatordialog.h \
    aboutbox.h \
    NightCharts/nightcharts.h

FORMS    += \
    mainwindow.ui \
    finderdialog.ui \
    directorytree.ui \
    comparatordialog.ui \
    aboutbox.ui

RESOURCES += \
    icons.qrc

OTHER_FILES +=
