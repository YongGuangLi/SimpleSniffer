#ifndef LOGUTILS_H
#define LOGUTILS_H


#include <stdio.h>
#include <string>

#include <log4cplus/configurator.h>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>      //需要在redis庫之前引用

using namespace log4cplus;
using namespace log4cplus::helpers;


using namespace std;

//日志封装
#define TRACE(p) LOG4CPLUS_TRACE(LogUtils::instance()->logger_, p)
#define DEBUG(p) LOG4CPLUS_DEBUG(LogUtils::instance()->logger_, p)
#define INFO(p) LOG4CPLUS_INFO(LogUtils::instance()->logger_, p)
#define WARN(p) LOG4CPLUS_WARN(LogUtils::instance()->logger_, p)
#define FATAL(p) LOG4CPLUS_ERROR(LogUtils::instance()->logger_, p)

// 日志控制类，全局共用一个日志
class LogUtils
{
public:
    // 获得日志实例
    static LogUtils *instance();
    void initLogger(string properties,string logger);
    Logger logger_;
private:
    LogUtils();
    virtual ~LogUtils();

    static LogUtils *logUtils;

    log4cplus::ConfigureAndWatchThread *configureThread;
};


#endif // LOGUTILS_H
