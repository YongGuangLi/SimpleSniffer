#include "simplesniffer.h"


SimpleSniffer::SimpleSniffer(QObject *parent) :
    QThread(parent)
{
    isRunning = true;
    QDir dir(SingletonConfig->getPcapPath());
    if(!dir.exists())
        dir.mkpath(SingletonConfig->getPcapPath());

    qDebug()<<QString::fromLocal8Bit("报文存放路径:%1").arg(SingletonConfig->getPcapPath());

    //保存时间间隔，数据保存到新文件
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(stopSniffer()));
    timer->start(SingletonConfig->getSaveTimeInterval() * 60 * 1000);
}

SimpleSniffer::~SimpleSniffer()
{
    timer->stop();
    timer->deleteLater();

    isRunning = false;
    stopSniffer();
    quit();
    wait();
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
            printf("pcap_set_snaplen() is failed for len[%d]", 65536);

        if(pcap_set_promisc(pcap_handle, true) != 0)
            qDebug()<<"pcap_set_promisc() is failure";

        if(pcap_set_timeout(pcap_handle, 0) != 0)
            qDebug()<<"pcap_set_timeout() is failure";

        const size_t pcap_buf_size =  32 * 1024 * 1024;
        if(pcap_set_buffer_size(pcap_handle, pcap_buf_size) != 0)
            qDebug()<<"pcap_set_buffer_size failed for size:"<<pcap_buf_size;

        if(pcap_activate(pcap_handle) != 0)
        {
            pcap_close(pcap_handle);
            pcap_handle = NULL;
            strncpy(pcap_err_buf, "pcap_activate failed",sizeof(pcap_err_buf));
        }
    }

    if(pcap_handle==NULL)
        qDebug()<<szErr;

    return pcap_handle;
}

void SimpleSniffer::run()
{
    handle = OpenDev(SingletonConfig->getEth().toLatin1().data());
    if(handle != NULL)
        qDebug()<<QString::fromLocal8Bit("打开设备:%1 成功").arg(SingletonConfig->getEth());
    else
        qDebug()<<QString::fromLocal8Bit("打开设备:%1 失败").arg(SingletonConfig->getEth());

    while(isRunning)
    {
        startTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
        QString pcapfile = QString("%1/%2.pcap").arg(SingletonConfig->getPcapPath()).arg(startTime);
        dumpfile = pcap_dump_open(handle, pcapfile.toStdString().c_str());

        qDebug()<<QString::fromLocal8Bit("开始抓包，数据保存到:%1").arg(pcapfile);

        pcap_loop( handle, 65535, loop_callback, (u_char *)dumpfile);

        qDebug()<<QString::fromLocal8Bit("抓包完成");

        pcap_dump_close(dumpfile);
    }
    pcap_close(handle); /* 关闭会话 */
}


void SimpleSniffer::loop_callback(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
    pcap_dump(args,  header, packet);
    pcap_dump_flush((pcap_dumper_t *)args);
}


void SimpleSniffer::stopSniffer()
{
    pcap_breakloop(handle);
}


