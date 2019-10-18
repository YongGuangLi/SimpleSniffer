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
    NetworkAwareness.pb.cc

HEADERS += \
    simplesniffer.h \
    configini.h \
    logutils.h \
    logutils.h \
    RedisHelper.h \
    NetworkCollect.pb.h \
    RedisHelper.h \
    NetworkAwareness.pb.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libpcap/lib/release/ -lpcap
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libpcap/lib/debug/ -lpcap
else:unix: LIBS += -L$$PWD/../libpcap/lib/ -lpcap

INCLUDEPATH += $$PWD/../libpcap/include
DEPENDPATH += $$PWD/../libpcap/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../protobuf-3.3.0/lib/release/ -lprotobuf-lite
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../protobuf-3.3.0/lib/debug/ -lprotobuf-lite
else:unix: LIBS += -L$$PWD/../protobuf-3.3.0/lib/ -lprotobuf-lite

INCLUDEPATH += $$PWD/../protobuf-3.3.0/include
DEPENDPATH += $$PWD/../protobuf-3.3.0/include


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../log4cplus/lib/release/ -llog4cplus
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../log4cplus/lib/debug/ -llog4cplus
else:unix: LIBS += -L$$PWD/../log4cplus/lib/ -llog4cplus

INCLUDEPATH += $$PWD/../log4cplus/include
DEPENDPATH += $$PWD/../log4cplus/include



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../acl/lib_acl_cpp/lib/release/ -l_acl_cpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../acl/lib_acl_cpp/lib/debug/ -l_acl_cpp
else:unix: LIBS += -L$$PWD/../acl/lib_acl_cpp/lib/ -l_acl_cpp

INCLUDEPATH += $$PWD/../acl/lib_acl_cpp/include
DEPENDPATH += $$PWD/../acl/lib_acl_cpp/include

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../acl/lib_acl_cpp/lib/release/_acl_cpp.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../acl/lib_acl_cpp/lib/debug/_acl_cpp.lib
else:unix: PRE_TARGETDEPS += $$PWD/../acl/lib_acl_cpp/lib/lib_acl_cpp.a


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../acl/lib_acl/lib/release/ -lacl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../acl/lib_acl/lib/debug/ -lacl
else:unix: LIBS += -L$$PWD/../acl/lib_acl/lib/ -lacl

INCLUDEPATH += $$PWD/../acl/lib_acl/include
DEPENDPATH += $$PWD/../acl/lib_acl/include

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../acl/lib_acl/lib/release/acl.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../acl/lib_acl/lib/debug/acl.lib
else:unix: PRE_TARGETDEPS += $$PWD/../acl/lib_acl/lib/libacl.a
