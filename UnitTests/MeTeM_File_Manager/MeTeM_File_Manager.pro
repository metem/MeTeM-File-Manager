#-------------------------------------------------
#
# Project created by QtCreator 2013-07-04T23:14:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MeTeM_File_Manager
TEMPLATE = app

RC_FILE = app.rc

SOURCES += \
    main.cpp \
    filechartdockview.cpp \
    filesfinder.cpp \
    filemodel.cpp \
    fileinfoex.cpp \
    duplicatesfinder.cpp \
    NightCharts/nightcharts.cpp \
    mainwindow.cpp \
    finderdialog.cpp \
    directorytree.cpp \
    comparatordialog.cpp \
    aboutbox.cpp \
    movedialog.cpp \
    filescopier.cpp

HEADERS  += \
    textformatter.h \
    duplicatesfinder.h \
    filesfinder.h \
    filemodel.h \
    fileinfoex.h \
    filechartdockview.h \
    NightCharts/nightcharts.h \
    mainwindow.h \
    finderdialog.h \
    directorytree.h \
    comparatordialog.h \
    aboutbox.h \
    movedialog.h \
    filescopier.h

FORMS    += \
    mainwindow.ui \
    finderdialog.ui \
    directorytree.ui \
    comparatordialog.ui \
    aboutbox.ui \
    movedialog.ui

RESOURCES += \
    icons.qrc

OTHER_FILES += \
    app.rc
