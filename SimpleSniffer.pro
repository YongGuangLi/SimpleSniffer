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
    logutils.cpp \
    RedisHelper.cpp \
    NetworkCollect.pb.cc

HEADERS += \
    simplesniffer.h \
    configini.h \
    logutils.h \
    logutils.h \
    RedisHelper.h \
    NetworkCollect.pb.h

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



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libacl/lib/release/ -lacl_cpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libacl/lib/debug/ -lacl_cpp
else:unix: LIBS += -L$$PWD/../libacl/lib/ -lacl_cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libacl/lib/release/ -lacl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libacl/lib/debug/ -lacl
else:unix: LIBS += -L$$PWD/../libacl/lib/ -lacl

INCLUDEPATH += $$PWD/../libacl/include
DEPENDPATH += $$PWD/../libacl/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../protobuf-3.3.0/lib/release/ -lprotobuf-lite
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../protobuf-3.3.0/lib/debug/ -lprotobuf-lite
else:unix: LIBS += -L$$PWD/../protobuf-3.3.0/lib/ -lprotobuf-lite

INCLUDEPATH += $$PWD/../protobuf-3.3.0/include
DEPENDPATH += $$PWD/../protobuf-3.3.0/include
