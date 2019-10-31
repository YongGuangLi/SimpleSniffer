
#include "simplesniffer.h"
#include "logutils.h"

#include <QCoreApplication>

#define VERSION "20191031"

void redisSubscribe()
{
    QString redisAddr = QString("%1:%2").arg(SingletonConfig->getIpRedis()).arg(SingletonConfig->getPortRedis());
    SingleRedisHelp->setConnParas(redisAddr.toLocal8Bit().data(), SingletonConfig->getPasswdRedis().toStdString());

    while(1)
    {
        if(!SingleRedisHelp->check_connect())
        {
            if(SingleRedisHelp->open())
            {
                INFO(QString("Redis Connect Success:%1").arg(redisAddr).toStdString());

                if(SingleRedisHelp->subscribe(SingletonConfig->getChannelName().toLocal8Bit().data(), NULL) >= 1)
                    INFO(QString("Redis Subscribe Success:%1").arg(SingletonConfig->getChannelName()).toStdString());
                else
                    WARN(QString("Redis Subscribe Failure:%1").arg(SingletonConfig->getChannelName()).toStdString());
            }else
            {
                WARN(QString("Redis Connect Failure:%1").arg(redisAddr).toStdString());
                sleep(1);
                continue;
            }
        }

        string message;
        if(SingleRedisHelp->getMessage(message))
        {
            INFO(message);
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThreadPool::globalInstance()->setMaxThreadCount(32);

    LogUtils::instance()->initLogger(qApp->applicationDirPath().toStdString() + "/log4cplus.properties", "Sniffer");
    INFO(QString::fromLocal8Bit("----------Version:%1----------").arg(VERSION).toStdString());

    if(!SingletonConfig->initConfigFile(qApp->applicationDirPath() + "/sysconfig.ini"))
    {
        WARN(QString("%1 not exist").arg(qApp->applicationDirPath() + "/sysconfig.ini").toStdString());
        return -1;
    }

    //订阅Redis,用于重连
    QtConcurrent::run(redisSubscribe);

    for(int i = 0; i < SingletonConfig->getEths().size(); ++i)
    {
        QString eth = SingletonConfig->getEths().at(i);

        QDir dir;
        if(!dir.exists(QString("%1/%2").arg(SingletonConfig->getPcapSrcPrePath()).arg(eth)))
            dir.mkpath(QString("%1/%2").arg(SingletonConfig->getPcapSrcPrePath()).arg(eth));

        if(!dir.exists(QString("%1/%2").arg(SingletonConfig->getPcapDstPrePath()).arg(eth)))
            dir.mkpath(QString("%1/%2").arg(SingletonConfig->getPcapDstPrePath()).arg(eth));
    }


    SimpleSniffer simpleSniffer;

    return a.exec();
}
