#ifndef LOCALCHANNELLISTVIEW_H
#define LOCALCHANNELLISTVIEW_H

#include <QListWidget>
#include <QList>

#include <Channel/ChannelList/ChannelAttributes/attributes.h>
#include <Channel/ChannelList/dublicatechannellist.h>
#include <Channel/ChannelList/globalchannellistview.h>

namespace oscilloscope
{
    class LocalChannelListView
    {
    public:
        void deleteChannelForLocalList(iChannel* ch);
        Attributes attributesForOneChannel(QString channelName);
        QList<Attributes> attributesForLocalList();
        void setAttributes(QString channelName, Attributes atr);
        void takeObject(); // Drag and Drop

    private:
        QList<Attributes> _attributes;
        DublicateChannelList *_dublicateChannels;
        GlobalChannelList *_channelView;
    };
}

#endif // LOCALCHANNELLISTVIEW_H
