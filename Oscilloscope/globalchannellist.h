#ifndef GLOBALCHANNELLIST_H
#define GLOBALCHANNELLIST_H

#pragma once
#include<channellist.h>

class GlobalChannelListView;
class GlobalChannelList : public ChannelList{
private:
    GlobalChannelListView *_channelsView;
};

#endif // GLOBALCHANNELLIST_H
