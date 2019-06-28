#ifndef CHANNELLIST_H
#define CHANNELLIST_H

#include <QList>
#include <QString>

#include <ichannel.h>

namespace oscilloscope
{
    class ChannelList
    {
        Q_OBJECT

    public:
        ChannelList(iChannel* ch);
        virtual ~ChannelList();

        int indexOfChannel(QString channelName);
        iChannel* channelByName(QString channelName);
        void addChannel(iChannel* ch);
        QList<iChannel*> channels();

    protected:
        QList<iChannel*>_channelList;
    };
}

#endif // CHANNELLIST_H
