#include "configini.h"

ConfigIni* ConfigIni::configIni = NULL;

ConfigIni *ConfigIni::GetInstance()
{
    if(configIni == NULL) 
        configIni = new ConfigIni();
    
    return configIni;
}

ConfigIni::ConfigIni(QObject *parent) : QObject(parent)
{
    m_saveTimeInterval = 10;
    m_eth = "eth2";
    m_deleteTimeInterval = 1;
    m_pcapPath = "/home/pcap";
}
 
bool ConfigIni::initConfigFile(QString fileName)
{
	bool result = false;
	if(QFile::exists(fileName))
	{
		result = true;
		QSettings* settings_ = new QSettings(fileName,QSettings::IniFormat);
		settings_->setIniCodec("UTF-8");

		settings_->beginGroup("MYSQL"); 
		settings_->endGroup();
	}
	else
	{
		qWarning()<<fileName + " not exist";
	}
    return result;
}

QString ConfigIni::getEth() const
{
    return m_eth;
}

QString ConfigIni::getPcapPath() const
{
    return m_pcapPath;
}

int ConfigIni::getSaveTimeInterval() const
{
    return m_saveTimeInterval;
}

int ConfigIni::getDeleteTimeInterval() const
{
    return m_deleteTimeInterval;
}

