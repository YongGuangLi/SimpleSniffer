
#include "simplesniffer.h"
#include "logutils.h"

#include <QCoreApplication>

#define VERSION "20190115"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    SingletonConfig->initConfigFile(qApp->applicationDirPath() + "/sysconfig.ini");
    QDir dir;
    if(!dir.exists(SingletonConfig->getPcapPath()))
        dir.mkpath(SingletonConfig->getPcapPath());

    if(!dir.exists(qApp->applicationDirPath() + "/logs"))
        dir.mkpath(qApp->applicationDirPath() + "/logs");

    LogUtils::instance()->initLogger(qApp->applicationDirPath().toStdString() + "/log4cplus.properties", "Sniffer");

    DEBUG(QString::fromLocal8Bit("Version:%1").arg(VERSION).toLocal8Bit().data());

    DEBUG(QString::fromLocal8Bit("Pcap Save Path:%1").arg(SingletonConfig->getPcapPath()).toLocal8Bit().data());

    SimpleSniffer simpleSniffer;
    simpleSniffer.start();

    return a.exec();
}
