#include "globalchannellist.h"

namespace oscilloscope {
    /// КОНСТРУКТОР СПИСКА ОРИГИНАЛЬНЫХ КАНАЛОВ

    GlobalChannelList::GlobalChannelList(QLayout *parent) : iChannelList() {
        _channelsView = new GlobalChannelListView();

        connect(_channelsView, SIGNAL(channelDeleted(const QString)), this, SLOT(channelDelete(const QString)));

        if (parent) parent->addWidget(_channelsView);
            else _channelsView->show();
    }

    /// ОБНОВЛЕНИЕ ОТОБРАЖЕНИЯ КАНАЛА

    void GlobalChannelList::channelUpdate(Channel *channel) {
        if (channel->status()) _channelsView->item(_channels->indexOf(channel))->setForeground(CH_ALIVE);
            else _channelsView->item(_channels->indexOf(channel))->setForeground(CH_DEAD);

        _channelsView->repaint();

        emit channelUpdated();
    }

    /// ПОЛУЧЕНИЕ ИНДЕКСА ОРИГИНАЛЬНОГО КАНАЛА ПО ЕГО ИМЕНИ

    int GlobalChannelList::indexByName(const QString name) const {
        for (int i = 0; i < _channels->length(); i++)
            if (_channels->at(i)->data()->frame()->_channelName == name)
                return i;

        return -1;
    }

    /// ДОБАВЛЕНИЕ ОРИГИНАЛЬНОГО КАНАЛА В СПИСОК

    void GlobalChannelList::add(iChannel *channel, bool alive) {
        iChannelList::add(channel);
        _channelsView->addItem(channel->data()->frame()->_channelName);

        if (alive) _channelsView->item(_channelsView->count() - 1)->setTextColor(CH_ALIVE);
            else _channelsView->item(_channelsView->count() - 1)->setTextColor(CH_DEAD);
    }

    /// ДЕСТРУКТОР

    GlobalChannelList::~GlobalChannelList() {
        delete _channelsView;
    }
}
