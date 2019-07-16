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

        emit channelUpdated(channel->dataStream()->frame()->_channelName);
    }

    /// ПОЛУЧЕНИЕ ИНДЕКСА ОРИГИНАЛЬНОГО КАНАЛА ПО ЕГО ИМЕНИ

    int GlobalChannelList::indexByName(const QString name) const {
        for (int i = 0; i < _channels->length(); i++)
            if (_channels->at(i)->dataStream()->frame()->_channelName == name)
                return i;

        return -1;
    }

    /// ДОБАВЛЕНИЕ ОРИГИНАЛЬНОГО КАНАЛА В СПИСОК

    void GlobalChannelList::add(iChannel *channel, bool alive) {
        iChannelList::add(channel);
        _channelsView->addItem(channel->dataStream()->frame()->_channelName);

        if (alive) _channelsView->item(_channelsView->count() - 1)->setTextColor(CH_ALIVE);
            else _channelsView->item(_channelsView->count() - 1)->setTextColor(CH_DEAD);
    }

    /// ПОЛУЧЕНИЕ ВЫБРАННОГО КАНАЛА

    iChannel *GlobalChannelList::getSelectedChannel() const {
      QList <QListWidgetItem*> selectedItems = _channelsView->selectedItems();
      if (selectedItems.isEmpty()) {
          return nullptr;
        }
      QListWidgetItem* item = selectedItems.first();
      QString name = item->text();
      return _channels->at(indexByName(name));
    }

    /// ДЕСТРУКТОР

    GlobalChannelList::~GlobalChannelList() {}
}
