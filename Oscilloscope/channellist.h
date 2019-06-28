#ifndef CHANNELLIST_H
#define CHANNELLIST_H

#include <QList>
#include <QString>

#include <ichannel.h>

// xcxz

namespace oscilloscope
{
    class ChannelList
    {
        Q_OBJECT

    public:
        int indexOfChannel(QString channelName);
        iChannel* channelByName(QString channelName);
        void addChannel(iChannel* ch);
        QList<iChannel*> channels();

    protected:
        QList<iChannel*>_channelList;

    private:
        ChannelList(iChannel* ch);
        virtual ~ChannelList();
    };
}

#endif // CHANNELLIST_H
