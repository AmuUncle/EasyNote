#-------------------------------------------------
#
# Project created by QtCreator 2021-09-18T18:56:18
#
#-------------------------------------------------

QT       += core gui
QT      += webenginewidgets
QT      += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasyNote
TEMPLATE = app
DESTDIR = bin

unix:UI_DIR = ../tmp/ui
win32:UI_DIR = tmp/ui

INCLUDEPATH += include

SOURCES += source/main.cpp\
    source/datamgr.cpp \
    source/mainwnd.cpp \
    source/nvrpane.cpp \
    source/notelistpane.cpp \
    source/noteviewpane.cpp

HEADERS  += include/mainwnd.h \
    include/datamgr.h \
    include/nvrpane.h \
    include/notelistpane.h \
    include/noteviewpane.h \
    include/global.h

unix|win32: LIBS += -L$$PWD/lib/ -lBasicSdk

INCLUDEPATH += $$PWD/lib/
DEPENDPATH += $$PWD/lib/

RESOURCES += \
    res/res.qrc
