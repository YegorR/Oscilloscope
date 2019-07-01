#ifndef CHANNELLIST_H
#define CHANNELLIST_H

#pragma once
//#include <ichannel.h>
#include <QList>
#include <QString>

class iChannel;
class ChannelList{
private:
    QList<iChannel*> _channels;
public:
    void add(iChannel ch);
    QList<iChannel*> channels();
    iChannel* channelByName(QString channelName);
};

#endif // CHANNELLIST_H
