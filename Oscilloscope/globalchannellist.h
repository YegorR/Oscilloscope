#ifndef GLOBALCHANNELLIST_H
#define GLOBALCHANNELLIST_H

#include <channellist.h>
#include <globalchannellistview.h>

namespace oscilloscope
{
    class GlobalChannelList : public ChannelList
    {
    public:
        GlobalChannelList(iChannel* ch);
        ~GlobalChannelList();

        void deleteChannel(QString channelName);
        void deleteGlobalList();
    };
}
#endif // GLOBALCHANNELLIST_H
