#include "common.h"
#include "device_discovery.h"
#include "inc/JVNSDKDef.h"
#include "inc/JvClient.h"
#include "src/yst_usedef.h"
#include <time.h>

DeviceDiscovery::DeviceDiscovery(QWidget *parent, bool use_yst, bool use_onvif)
    : QWidget(parent), use_yst_(use_yst), use_onvif_(use_onvif)
{
    if (use_yst_)
    {
        yst_discovery_ = new YstDiscovery(this);
    }
}

DeviceDiscovery::~DeviceDiscovery()
{
    if (yst_discovery_ && yst_discovery_->IsSearching())
    {
        yst_discovery_->StopSearch();
        delete yst_discovery_;
    }
}

void DeviceDiscovery::Init()
{
    if(yst_discovery_)
    {
        yst_discovery_->Init();
    }
}

void DeviceDiscovery::StartSearch()
{
    if (yst_discovery_)
    {
        yst_discovery_->StartSearch();
    }

    return;
}

void DeviceDiscovery::StopSearch()
{
    if(yst_discovery_ && yst_discovery_->IsSearching())
    {
        yst_discovery_->StopSearch();
    }

    return;
}

/* yst discovery
 *
*/
YstDiscovery::YstDiscovery(DeviceDiscovery *parent)
    : parent_(parent), bc_id_(-1), if_searching_(false)
{
}

YstDiscovery::~YstDiscovery()
{
}

void YstDiscovery::Init()
{
    int local_port;
#if defined(Q_OS_WIN32)
        bool r;
#elif defined(Q_OS_LINUX)
        int r;
#endif

    for (local_port = 9400; local_port < 9500; local_port++)
    {
        r = JVC_StartLANSerchServer(local_port, 6666, YST_ClientLanSearchCallBack);
        if (r == true)
        {
            logger->debug("start lan search, local port is %1, ret is %2", local_port, r);
            break;
        }

        logger->debug("lan: local port %1 was used, and try %2", local_port, local_port + 1);
    }

    if (r == 0)
    {
        logger->warn("search lan error");
    }

    for (local_port = 9500; local_port < 9600; local_port++)
    {
#if defined(Q_OS_WIN32)
        bool r;
#elif defined(Q_OS_LINUX)
        int r;
#endif
        r = JVC_StartBroadcastServer(local_port, 9106, YST_ClientBcCallBack);
        if (r == true)
        {
            logger->debug("start bc search, local port is %1, ret is %2", local_port, r);
            break;
        }
        logger->debug("bc: local port %1 was used, and try %2", local_port, local_port + 1);
    }

    if (r == 0)
    {
        logger->warn("search bc error");
    }

    return;
}

bool YstDiscovery::IsSearching()
{
    return if_searching_;
}

void YstDiscovery::StartSearch()
{
    // search lan
    srand(time(NULL));
    this->bc_id_ = rand() + rand() + 1;

    BCPACKET packet = {0};
    packet.nCmd = BC_SEARCH;
    JVC_BroadcastOnce(this->bc_id_, (unsigned char *)(&packet), sizeof(BCPACKET), 1000);

    // search vlan
    //JVC_LANSerchDevice("", 0, 0xE71A, 3, "", 6000, 3600);

    // TODO: search by onvif

    if_searching_ = true;

    return;
}

void YstDiscovery::StopSearch()
{
    if (if_searching_)
    {
        JVC_StopLANSerchServer();
        JVC_StopBroadcastServer();
    }

    return;
}
