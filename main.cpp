
#include "simplesniffer.h"

#include "log4qt/propertyconfigurator.h"
#include "log4qt/logmanager.h"

#include <QCoreApplication>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Log4Qt::PropertyConfigurator::configure(a.applicationDirPath() + "/log4qt.properties");
    Log4Qt::LogManager::setHandleQtMessages(true);


    SimpleSniffer simpleSniffer;
    simpleSniffer.start();

    return a.exec();
}
