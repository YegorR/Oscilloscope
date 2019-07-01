///     СПИСОК ОРИГИНАЛЬНЫХ КАНАЛОВ И СОЗДАНИЕ ИХ ВЫВОДА

#ifndef GLOBALCHANNELLIST_H
#define GLOBALCHANNELLIST_H

#include <QLayout>
#include <QObject>

#include "channellist.h"
#include "globalchannellistview.h"

namespace oscilloscope
{
    class globalChannelList : public channelList
    {
        Q_OBJECT

    public:
        globalChannelList();
        ~globalChannelList();

        void add(QString channel, bool alive = true);

    private:
        globalChannelListView *_channelsView;
    };
}

#endif
