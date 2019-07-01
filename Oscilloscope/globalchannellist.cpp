#include <QLayout>

#include "globalchannellist.h"

namespace oscilloscope {
    globalChannelList::globalChannelList(QLayout *parent) : channelList() {
        _channelsView = new globalChannelListView();

        connect(_channelsView, SIGNAL(channelDeleted(const QString)), this, SLOT(channelDelete(const QString)));

        add("Канал 1");
        add("Канал 2", false);
        add("Канал 3");

        if (parent) parent->addWidget(_channelsView);
            else _channelsView->show();
    }

    void globalChannelList::add(QString channel, bool alive) {
        channelList::add(channel);
        _channelsView->addItem(channel);

        if (alive) _channelsView->item(_channelsView->count() - 1)->setTextColor(CH_ALIVE);
            else _channelsView->item(_channelsView->count() - 1)->setTextColor(CH_DEAD);
    }

    globalChannelList::~globalChannelList() {}
}

