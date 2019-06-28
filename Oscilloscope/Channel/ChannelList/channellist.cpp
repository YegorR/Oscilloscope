#include <ChannelList/channellist.h>

namespace oscilloscope
{
    ChannelList::ChannelList(iChannel* ch)
    {
        _channelList << ch;
    }

    ChannelList::~ChannelList()
    {
        _channelList.clear();
    }

    int ChannelList::indexOfChannel(QString channelName)
    {
        for (int i = 0; i < _channelList.size(); i++) {
            if (_channelList[i]->channelName == channelName) {
                return i;
            }
        }
    }

    iChannel* ChannelList::channelByName(QString channelName)
    {
        return _channelList[this->indexOfChannel(channelName)];
    }

    void ChannelList::addChannel(iChannel* ch)
    {
        _channelList << ch;
    }

    QList<iChannel*> ChannelList::channels()
    {
        return(_channelList);
    }
}
