#ifndef GLOBALCHANNELLIST_H
#define GLOBALCHANNELLIST_H

#pragma once
//#include<globalchannellistview.h>

class GlobalChannelListView;
class GlobalChannelList : public channellist{
private:
    GlobalChannelListView *_channelsView;
};

#endif // GLOBALCHANNELLIST_H
