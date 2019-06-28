#include <localchannellist.h>

namespace oscilloscope
{
    LocalChannelList::LocalChannelList(iChannel* ch) : ChannelList (ch)
    {
        Attributes atr;
        _attributes << atr;
    }

    LocalChannelList::LocalChannelList(iChannel* ch, Attributes atr) : ChannelList (ch)
    {
        _attributes << atr;
    }

    LocalChannelList::~LocalChannelList()
    {
        _attributes.clear();
    }

    void LocalChannelList::deleteChannelForLocalList(iChannel* ch)
    {
        _attributes.removeAt(this->indexOfChannel(ch->channelName));
    }

    Attributes LocalChannelList::attributesForOneChannel(QString channelName)
    {
        return _attributes[this->indexOfChannel(channelName)];
    }

    QList<Attributes> LocalChannelList::attributesForLocalList()
    {
        return _attributes;
    }

    void LocalChannelList::setAttributes(QString channelName, Attributes atr)
    {
        _attributes[this->indexOfChannel(channelName)]._collor = atr._collor;
        _attributes[this->indexOfChannel(channelName)]._lineType = atr._lineType;
        _attributes[this->indexOfChannel(channelName)]._lineWidth = atr._lineWidth;
    }

    void takeObject(); // Drag and Drop
}
