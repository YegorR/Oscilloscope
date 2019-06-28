#include <globalchannellist.h>

namespace oscilloscope
{
    GlobalChannelList::GlobalChannelList(iChannel* ch) : ChannelList (ch) {}

    void GlobalChannelList::deleteChannel(QString channelName)
    {
        _channelList.removeAt(this->indexOfChannel(channelName));
    }

    void GlobalChannelList::deleteGlobalList()
    {

    }
}
