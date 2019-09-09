
#include "simplesniffer.h"
#include "logutils.h"

#include <QCoreApplication>

#define VERSION "20190115"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LogUtils::instance()->initLogger(qApp->applicationDirPath().toStdString() + "/log4cplus.properties", "Sniffer");
    INFO(QString::fromLocal8Bit("Version:%1").arg(VERSION).toLocal8Bit().data());

    if(!SingletonConfig->initConfigFile(qApp->applicationDirPath() + "/sysconfig.ini"))
        return -1;

    for(int i = 0; i < SingletonConfig->getEths().size(); ++i)
    {
        QString eth = SingletonConfig->getEths().at(i);
        INFO(QString::fromLocal8Bit("Pcap Save Path:%1/%2").arg(SingletonConfig->getPcapSrcPath()).arg(eth).toLocal8Bit().data());
        QDir dir;
        if(!dir.exists(QString("%1/%2").arg(SingletonConfig->getPcapSrcPath()).arg(eth)))
            dir.mkpath(QString("%1/%2").arg(SingletonConfig->getPcapSrcPath()).arg(eth));
    }


    SimpleSniffer simpleSniffer;
    simpleSniffer.start();

    return a.exec();
}
