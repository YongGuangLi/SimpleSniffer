#include "logutils.h"


LogUtils *LogUtils::logUtils = NULL;

LogUtils::LogUtils()
{
    log4cplus::initialize();  //linux下不用
}

LogUtils::~LogUtils()
{
    log4cplus::Logger::shutdown();
}

LogUtils* LogUtils::instance()
{
    if(logUtils == NULL)
    {
        logUtils = new LogUtils();
    }
    return logUtils;
}

void LogUtils::initLogger(string properties, string logger)
{
    configureThread = new log4cplus::ConfigureAndWatchThread(LOG4CPLUS_TEXT(properties), 1000);
    logger_ = log4cplus::Logger::getInstance(logger);
}
