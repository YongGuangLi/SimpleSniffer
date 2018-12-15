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

SOURCES += main.cpp \
    simplesniffer.cpp \
    configini.cpp \
    logutils.cpp

HEADERS += \
    simplesniffer.h \
    configini.h \
    logutils.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libpcap/lib/release/ -lpcap
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libpcap/lib/debug/ -lpcap
else:unix: LIBS += -L$$PWD/../libpcap/lib/ -lpcap

INCLUDEPATH += $$PWD/../libpcap/include
DEPENDPATH += $$PWD/../libpcap/include


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../log4cplus/lib/release/ -llog4cplus
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../log4cplus/lib/debug/ -llog4cplus
else:unix: LIBS += -L$$PWD/../log4cplus/lib/ -llog4cplus

INCLUDEPATH += $$PWD/../log4cplus/include
DEPENDPATH += $$PWD/../log4cplus/include

