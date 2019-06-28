#ifndef LOCALCHANNELLISTVIEW_H
#define LOCALCHANNELLISTVIEW_H

#include <QList>

#include <ChannelList/ChannelAttributes/attributes.h>
#include <ChannelList/channellist.h>

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
        LocalChannelList(iChannel* ch);
        LocalChannelList(iChannel* ch, Attributes atr);
        ~LocalChannelList();

        QList<Attributes> _attributes;
        // LocalChannelListView _channelView;
    };
}

#endif // LOCALCHANNELLISTVIEW_H
