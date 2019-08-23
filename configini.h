#ifndef CONFIGINI_H
#define CONFIGINI_H

#include "logutils.h"
#include <QCoreApplication>
#include <QObject>
#include <QFile>
#include <QDebug>
#include <QSettings>

#define SingletonConfig ConfigIni::GetInstance()

class ConfigIni : public QObject
{
    Q_OBJECT
public:
    static ConfigIni *GetInstance();  
	bool initConfigFile(QString);

    QString getChannelName() const;

    //redis数据
    QString getIpRedis() const;
    int getPortRedis() const;
    QString getPasswdRedis() const;

    QString getPasswdMysql() const;

    QString getEth() const;

    QString getPcapPath() const;

    int getSaveTimeInterval() const;

    int getDeleteTimeInterval() const;
private:
    explicit ConfigIni(QObject *parent = 0);
    static ConfigIni* configIni; 
signals:
    
public slots:
    
private:
    int m_saveTimeInterval;     //保存间隔  单位:分钟

    QString m_redisIp;
    int m_redisPort;
    QString m_redisPasswd;

    QString m_eth;

    QString m_pcapSrcPath;
    QString m_pcapDstPath;


    QString m_channel;
};

#endif // CONFIGINI_H
