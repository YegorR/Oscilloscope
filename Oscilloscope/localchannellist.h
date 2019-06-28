#ifndef LOCALCHANNELLIST_H
#define LOCALCHANNELLIST_H

#include <QList>

#include <attributes.h>
#include <channellist.h>

namespace oscilloscope
{
    class LocalChannelList : public ChannelList
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

#endif // LOCALCHANNELLIST_H
