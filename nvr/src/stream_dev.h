#ifndef STREAMDEV_H
#define STREAMDEV_H

#include <QtGlobal>
#include <QString>
#include <QHostAddress>

enum NETSTATUS
{
    NETSTATUS_VERY_GOOD,
    NETSTATUS_GOOD,
    NETSTATUS_bad,
    NETSTATUS_dead
};

enum DEVTYPE
{
    DEVICE_IPC,
    DEVICE_NVR,
    DEVICE_DVR
};

class StreamDev
{
public:
    StreamDev();

private:
    DEVTYPE dev_type_;          // 设备类型

    qint32 id_;                 // 所有设备统一编号
    QString name_;              // 设备名称
    QString yst_id_;            // 云视通id
    QHostAddress ip_address_;   // ip
    qint32 channel_counts_;     // 通道数

    NETSTATUS net_status_;      // 网络状况
};

#endif // STREAMDEV_H
