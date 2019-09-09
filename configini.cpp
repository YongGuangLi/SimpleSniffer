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
    m_channel = "SimpleSniffer";
}
 
bool ConfigIni::initConfigFile(QString fileName)
{
	bool result = false;
	if(QFile::exists(fileName))
	{
		result = true;
		QSettings* settings_ = new QSettings(fileName,QSettings::IniFormat);
		settings_->setIniCodec("UTF-8");

        settings_->beginGroup("redis");
        m_redisIp =  settings_->value("redis_ip").toString();
        m_redisPort =  settings_->value("redis_port").toInt();
        m_redisPasswd =  settings_->value("redis_passwd").toString();
        settings_->endGroup();

        settings_->beginGroup("PCAPPATH");
        m_pcapSrcPath = settings_->value("pcapsrcpath").toString();
        m_pcapDstPath = settings_->value("pcapdstpath").toString();
        settings_->endGroup();


        settings_->beginGroup("ETH");
        m_eths = settings_->value("eths").toString().split(" ");
        settings_->endGroup();

        settings_->beginGroup("TIMEINTERVAL");
        m_saveTimeInterval = settings_->value("savetimeinterval").toInt();
        settings_->endGroup();
	}
	else
	{
        WARN(fileName.toLocal8Bit().data()<<" not exist");
	}
    return result;
}

QString ConfigIni::getChannelName() const
{
    return m_channel;
}


QString ConfigIni::getIpRedis() const
{
    return m_redisIp;
}


int ConfigIni::getPortRedis() const
{
    return m_redisPort;
}

QString ConfigIni::getPasswdRedis() const
{
    return m_redisPasswd;
}


QStringList ConfigIni::getEths() const
{
    return m_eths;
}

QString ConfigIni::getPcapSrcPath() const
{
    return m_pcapSrcPath;
}

int ConfigIni::getSaveTimeInterval() const
{
    return m_saveTimeInterval;
}

