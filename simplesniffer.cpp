#include "simplesniffer.h"


SimpleSniffer::SimpleSniffer(QObject *parent) :
    QObject(parent)
{
    isRunning = true;

    QTimer *timerHeart = new QTimer();
    connect(timerHeart, SIGNAL(timeout()), this, SLOT(sendHeartBeat()));
    timerHeart->start(10 * 1000);

    for(int i = 0; i < SingletonConfig->getEths().size(); ++i)
    {
        QString eth = SingletonConfig->getEths().at(i);
        QtConcurrent::run(this, &SimpleSniffer::snifferEth, eth);
    }

    //保存时间间隔，数据保存到新文件
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(breakLoop()));
    timer->start(SingletonConfig->getSaveTimeInterval() * 60 * 1000);
}

SimpleSniffer::~SimpleSniffer()
{
    timer->stop();
    timer->deleteLater();

    isRunning = false;
    breakLoop();
}

void SimpleSniffer::snifferEth(QString eth)
{
    pcap_t* handle = OpenDev(eth.toLatin1().data());
    if(handle != NULL)
    {
        INFO(QString::fromLocal8Bit("Open Device:%1 Success").arg(eth).toLocal8Bit().data());
        listHandle.push_back(handle);
    }
    else
        WARN(QString::fromLocal8Bit("Open Device:%1 Failure").arg(eth).toLocal8Bit().data());

    while(isRunning)
    {
        QString startTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz");
        QString pcapfile = QString("%1/%2/%2%3.pcap").arg(SingletonConfig->getPcapSrcPath()).arg(eth).arg(startTime);
        pcap_dumper_t *dumpfile = pcap_dump_open(handle, pcapfile.toStdString().c_str());

        INFO(QString::fromLocal8Bit("Start Sniffer，Packet Save:%1").arg(pcapfile).toLocal8Bit().data());

        pcap_loop( handle, -1, loop_callback, (u_char *)dumpfile);

        pcap_dump_close(dumpfile);
    }
    //关闭会话
    pcap_close(handle);
}



pcap_t* SimpleSniffer::OpenDev(const char *pszFdevice)
{
    if (NULL == pszFdevice)
        return NULL;

    char  pcap_err_buf[PCAP_ERRBUF_SIZE];
    pcap_t * pcap_handle = NULL;

    if( (pcap_handle = pcap_create(pszFdevice,  pcap_err_buf))!= NULL)
    {
        // don't care whether is successful
        if(pcap_set_snaplen(pcap_handle, 65536) != 0)
            WARN("pcap_set_snaplen() is failed for len:"<<65536);

        if(pcap_set_promisc(pcap_handle, true) != 0)
            WARN("pcap_set_promisc() is failure");

        if(pcap_set_timeout(pcap_handle, 0) != 0)
            WARN("pcap_set_timeout() is failure");

        const size_t pcap_buf_size =  512 * 1024 * 1024;
        if(pcap_set_buffer_size(pcap_handle, pcap_buf_size) != 0)
            WARN("pcap_set_buffer_size failed for size:"<<pcap_buf_size);

        if(pcap_activate(pcap_handle) != 0)
        {
            pcap_close(pcap_handle);
            WARN("pcap_activate failed:"<<sizeof(pcap_err_buf));
            return NULL;
        }
    }

    return pcap_handle;
}

void SimpleSniffer::loop_callback(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
    pcap_dump(args,  header, packet);
    pcap_dump_flush((pcap_dumper_t *)args);
}


void SimpleSniffer::breakLoop()
{
    for(int i = 0; i < listHandle.size(); ++i)
    {
        pcap_breakloop(listHandle.at(i));
        INFO(QString::fromLocal8Bit("Complete Sniffer").toLocal8Bit().data());
    }
}


void SimpleSniffer::sendHeartBeat()
{
    MainMessage mainMessage;
    mainMessage.set_msgtype(MT_HeartBeatMessage);
    HeartBeatMessage *heartBeatMessage = mainMessage.mutable_heartbeatmessage();
    heartBeatMessage->set_time(QDateTime::currentDateTime().toTime_t());
    heartBeatMessage->set_channelname(SingletonConfig->getChannelName().toLocal8Bit().data());

    string message;
    mainMessage.SerializeToString(&message);
    if(SingleRedisHelp->publish(REDIS_PROCESSMANAGE, message) >= 0)
        DEBUG("Heart Send Success!");
    else
        WARN("Heart Send Failure!");
}

