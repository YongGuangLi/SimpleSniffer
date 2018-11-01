#ifndef CONFIGINI_H
#define CONFIGINI_H

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

    int m_deleteTimeInterval;

    QString m_eth;

    QString m_pcapPath;
};

#endif // CONFIGINI_H
