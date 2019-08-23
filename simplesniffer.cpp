#include "simplesniffer.h"


SimpleSniffer::SimpleSniffer(QObject *parent) :
    QThread(parent)
{
    isRunning = true;

    QtConcurrent::run(this, &SimpleSniffer::redisSubscribe);


    QTimer *timerHeart = new QTimer();
    connect(timerHeart, SIGNAL(timeout()), this, SLOT(sendHeartBeat()));
    timerHeart->start(10 * 1000);

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
    quit();
    wait();
}


void SimpleSniffer::redisSubscribe()
{
    QString redisAddr = QString("%1:%2").arg(SingletonConfig->getIpRedis()).arg(SingletonConfig->getPortRedis());
    m_redisHelper = new RedisHelper(redisAddr.toLocal8Bit().data(), SingletonConfig->getPasswdRedis().toLocal8Bit().data());
    INFO(QString("RedisAddr %1:%2").arg(SingletonConfig->getIpRedis()).arg(SingletonConfig->getPortRedis()).toStdString());
    while(1)
    {
        if(!m_redisHelper->check_connect())
        {
            if(m_redisHelper->open())
            {
                INFO(QString("Redis Connect Success:%1").arg(redisAddr).toLocal8Bit().data());

                if(m_redisHelper->subscribe(SingletonConfig->getChannelName().toLocal8Bit().data(), NULL) >= 1)
                    INFO(QString("Redis Subscribe Success:%1").arg(SingletonConfig->getChannelName()).toLocal8Bit().data());
                else
                    WARN(QString("Redis Subscribe Failure:%1").arg(SingletonConfig->getChannelName()).toLocal8Bit().data());
            }else
            {
                WARN(QString("Redis Connect Failure:%1").arg(redisAddr).toLocal8Bit().data());
                sleep(1);
                continue;
            }
        }

        string message;
        if(m_redisHelper->getMessage(message))
        {
            INFO(message);
        }
    }
}

pcap_t* SimpleSniffer::OpenDev(const char *pszFdevice)
{
    if (NULL == pszFdevice)
        return NULL;

    char szErr[256] = {0};

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
            pcap_handle = NULL;
            strncpy(pcap_err_buf, "pcap_activate failed",sizeof(pcap_err_buf));
        }
    }

    if(pcap_handle==NULL)
        WARN(szErr);

    return pcap_handle;
}

void SimpleSniffer::run()
{
    handle = OpenDev(SingletonConfig->getEth().toLatin1().data());
    if(handle != NULL)
        INFO(QString::fromLocal8Bit("Open Device:%1 Success").arg(SingletonConfig->getEth()).toLocal8Bit().data());
    else
        WARN(QString::fromLocal8Bit("Open Device:%1 Failure").arg(SingletonConfig->getEth()).toLocal8Bit().data());

    while(isRunning)
    {
        startTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
        QString pcapfile = QString("%1/%2.pcap").arg(SingletonConfig->getPcapPath()).arg(startTime);
        dumpfile = pcap_dump_open(handle, pcapfile.toStdString().c_str());

        INFO(QString::fromLocal8Bit("Start，Packet Save:%1").arg(pcapfile).toLocal8Bit().data());

        pcap_loop( handle, -1, loop_callback, (u_char *)dumpfile);

        INFO(QString::fromLocal8Bit("Sniffer Complete").toLocal8Bit().data());

        pcap_dump_close(dumpfile);
    }
    pcap_close(handle); /* 关闭会话 */
}


void SimpleSniffer::loop_callback(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
    pcap_dump(args,  header, packet);
    pcap_dump_flush((pcap_dumper_t *)args);
}


void SimpleSniffer::breakLoop()
{
    pcap_breakloop(handle);
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
    if(m_redisHelper->publish(REDIS_PROCESSMANAGE, message) >= 0)
        DEBUG("Heart Send Success!");
    else
        WARN("Heart Send Failure!");
}

