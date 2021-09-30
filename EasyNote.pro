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

CONFIG += resources_big

unix:UI_DIR = ../tmp/ui
win32:UI_DIR = tmp/ui

#CONFIG(release, debug|release){
#    DEFINES += QT_NO_WARNING_OUTPUT QT_NO_DEBUG_OUTPUT
#}

win32:QMAKE_LFLAGS_WINDOWS += /LARGEADDRESSAWARE

INCLUDEPATH += include

SOURCES += source/main.cpp\
    source/datamgr.cpp \
    source/mainwnd.cpp \
    source/notelistpane.cpp \
    source/noteviewpane.cpp \
    source/noteitem.cpp \
    source/about.cpp \
    source/navpane.cpp \
    source/addfolder.cpp \
    source/popconfirm.cpp \
    source/login.cpp \
    source/setpwddlg.cpp

HEADERS  += include/mainwnd.h \
    include/datamgr.h \
    include/notelistpane.h \
    include/noteviewpane.h \
    include/global.h \
    include/noteitem.h \
    include/about.h \
    include/navpane.h \
    include/addfolder.h \
    include/popconfirm.h \
    include/login.h \
    include/setpwddlg.h

unix|win32: LIBS += -L$$PWD/lib/ -lBasicSdk

INCLUDEPATH += $$PWD/lib/
DEPENDPATH += $$PWD/lib/

RESOURCES += \
    res/res.qrc

RC_FILE +=  \
    res/icon.rc
