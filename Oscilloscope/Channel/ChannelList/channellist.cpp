#include <Channel/ChannelList/channellist.h>

namespace oscilloscope
{
    ChannelList::ChannelList(iChannel* ch)
    {
        connect(this, SIGNAL(deleteChannel(*ch)), iChannel, SLOT());
        _channelList << ch;
    }

    ChannelList::~ChannelList()
    {
        _channelList.clear();
    }

    void ChannelList::addChannel(iChannel* ch)
    {
        _channelList << ch;
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

    QList<iChannel*> ChannelList::channels()
    {
        return(_channelList);
    }
}
