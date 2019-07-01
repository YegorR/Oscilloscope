#include <Channel/ChannelList/localchannellistview.h>

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

    void LocalChannelListView::deleteChannelForLocalList(iChannel* ch)
    {
        _attributes.removeAt(this->indexOfChannel(ch->channelName));
    }

    Attributes LocalChannelListView::attributesForOneChannel(QString channelName)
    {
        return _attributes[this->indexOfChannel(channelName)];
    }

    QList<Attributes> LocalChannelListView::attributesForLocalList()
    {
        return _attributes;
    }

    void LocalChannelListView::setAttributes(QString channelName, Attributes atr)
    {
        _attributes[this->indexOfChannel(channelName)]._collor = atr._collor;
        _attributes[this->indexOfChannel(channelName)]._lineType = atr._lineType;
        _attributes[this->indexOfChannel(channelName)]._lineWidth = atr._lineWidth;
    }

    void takeObject(); // Drag and Drop
}
