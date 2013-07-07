#-------------------------------------------------
#
# Project created by QtCreator 2013-07-04T23:13:00
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_testduplicatesfinder
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    MeTeM_File_Manager/filesfinder.cpp \
    MeTeM_File_Manager/fileinfoex.cpp \
    MeTeM_File_Manager/duplicatesfinder.cpp \
    tst_main.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    MeTeM_File_Manager/filesfinder.h \
    MeTeM_File_Manager/fileinfoex.h \
    MeTeM_File_Manager/duplicatesfinder.h
