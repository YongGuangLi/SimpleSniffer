#ifndef SIMPLESNIFFER_H
#define SIMPLESNIFFER_H

#include "pcap.h"
#include "configini.h"
#include "logutils.h"
#include "RedisHelper.h"
#include "NetworkAwareness.pb.h"

#include <QObject>
#include <QtCore>
#include <QThread>
#include <QDebug>
#include <QList>
#include <QDir>
#include <QDateTime>
#include <QTimer>
#include <QMutex>

class SimpleSniffer : public QObject
{
    Q_OBJECT
public:
    explicit SimpleSniffer(QObject *parent = 0);
    ~SimpleSniffer();


    void snifferEth(QString eth);

    /**
    * @date      %{CurrentDate:yyyy-MM-dd}
    * @param
    * @return
    * @brief     摘要
    */
    pcap_t* OpenDev(const char *pszFdevice);
signals:
    
public slots:

    /**
    * @date     2018-12-05
    * @param
    * @return
    * @brief    发送心跳
    */
    void sendHeartBeat();


    /**
    * @date      2018-10-30
    * @param
    * @return
    * @brief     退出pcap_loop
    */
    void breakLoop();
private:
    static void loop_callback(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);
private:
    bool isRunning;
    QTimer *timer;
    QList<pcap_t *> listHandle;
};

#endif // SIMPLESNIFFER_H
