#ifndef DEVICEDISCOVERY_H
#define DEVICEDISCOVERY_H

#include <QWidget>

class YstDiscovery;
class DeviceDiscovery : public QWidget
{
public:
    DeviceDiscovery(QWidget *parent = NULL, bool use_yst = true, bool use_onvif = true);
    ~DeviceDiscovery();

    void Init();

    void StartSearch();
    void StopSearch();

private:
    bool use_yst_;
    YstDiscovery *yst_discovery_;

    bool use_onvif_;
};

class YstDiscovery
{
public:
    YstDiscovery(DeviceDiscovery *parent);
    ~YstDiscovery();

    void Init();

    bool IsSearching();
    void StartSearch();
    void StopSearch();

private:
    DeviceDiscovery *parent_;

    quint32 bc_id_;

    bool if_searching_;
};

#endif // DEVICEDISCOVERY_H
