#include "channellist.h"

namespace oscilloscope
{
    channelList::channelList(iChannel* ch)
    {
        _channels.push_back(ch);
    }

    channelList::~channelList()
    {
        _channels.clear();
    }

    void channelList::add(iChannel *ch)
    {
        _channels.push_back(ch);
    }

    iChannel* channelList::getChannel(const QString channelName) const
    {
        return _channels[indexChannelByName(channelName)];
    }

    int channelList::indexChannelByName(const QString channelName) const
    {
        for (int  i = 0; i < _channels.size(); i++) {
            if (_channels[i]->channelName() == channelName) {
                return i;
            }
        }
        return -1;
    }

    QList<iChannel*> channelList::getChannels() const
    {
        return _channels;
    }

    void channelList::channelDelete(const QString name) {
        _channels->removeAt(_channels->indexOf(name));
        emit channelDeleted(name);
    }
}
