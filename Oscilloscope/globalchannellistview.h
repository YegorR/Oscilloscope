#ifndef GLOBALCHANNELLISTVIEW_H
#define GLOBALCHANNELLISTVIEW_H

#pragma once
#include <QString>
#include <QVector>
#include <globalchannellist.h>

class GlobalChannelListView{
public:
    void deleteChannel(QString channelName);
private:
    QVector<GlobalChannelList> _channels;
};

#endif // GLOBALCHANNELLISTVIEW_H
