#include "channellist.h"

namespace oscilloscope {
    channelList::channelList() {
        _channels = new QList<QString>;
    }

    QList<QString> *channelList::channels() const {
        return _channels;
    }

    void channelList::add(QString channel) {
        _channels->push_back(channel);
    }

    channelList::~channelList() {
        delete[] _channels;
    }
}

void oscilloscope::channelList::channelDelete(const QString name) {
    _channels->removeAt(_channels->indexOf(name));
    emit channelDeleted(name);
}
