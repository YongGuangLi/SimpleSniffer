#-------------------------------------------------
#
# Project created by QtCreator 2018-10-25T14:29:59
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = SimpleSniffer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(/home/liyg/log4qt/log4qt.pri)

SOURCES += main.cpp \
    simplesniffer.cpp \
    configini.cpp

HEADERS += \
    simplesniffer.h \
    configini.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libpcap/lib/release/ -lpcap
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libpcap/lib/debug/ -lpcap
else:unix: LIBS += -L$$PWD/../libpcap/lib/ -lpcap

INCLUDEPATH += $$PWD/../libpcap/include
DEPENDPATH += $$PWD/../libpcap/include

