#ifndef DUBLICATECHANNELLIST_H
#define DUBLICATECHANNELLIST_H

#include <QList>

#include <ChannelList/channellist.h>
#include <dublicatechannel.h>

namespace oscilloscope
{
    class DublicateChannelList : public ChannelList
    {
    private:
        QList<DublicateChannel*> _dublicateChannelas;
    };
}

#endif // DUBLICATECHANNELLIST_H
