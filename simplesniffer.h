#ifndef SIMPLESNIFFER_H
#define SIMPLESNIFFER_H

#include "pcap.h"
#include "configini.h"

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QList>
#include <QDir>
#include <QDateTime>
#include <QTimer>

class SimpleSniffer : public QThread
{
    Q_OBJECT
public:
    explicit SimpleSniffer(QObject *parent = 0);
    ~SimpleSniffer();

    /**
    * @date      %{CurrentDate:yyyy-MM-dd}
    * @param
    * @return
    * @brief     摘要
    */
    pcap_t* OpenDev(const char *pszFdevice);

    /**
    * @date      2018-10-25
    * @param
    * @return
    * @brief     抓包
    */
    void run();

signals:
    
public slots:
    /**
    * @date      2018-10-30
    * @param
    * @return
    * @brief     停止抓包
    */
    void stopSniffer();
private:
    static void loop_callback(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);

private:
    pcap_t *handle;              /* 会话句柄 */
    pcap_dumper_t *dumpfile;

private:
    bool isRunning;
    QString startTime;
    QTimer *timer;
};

#endif // SIMPLESNIFFER_H
