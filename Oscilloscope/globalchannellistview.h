#ifndef GLOBALCHANNELLISTVIEW_H
#define GLOBALCHANNELLISTVIEW_H


#include <QString>
#include <QVector>

class GlobalChannelListView{
public:
    void deleteChannel(QString channelName);
private:
    QVector<GlobalChannelList> _channels;
};

#endif // GLOBALCHANNELLISTVIEW_H
