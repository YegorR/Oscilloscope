#ifndef CHANNELLIST_H
#define CHANNELLIST_H

#include <QList>
#include <QString>
#include <QObject>

#include <Channel/ichannel.h>

namespace oscilloscope
{
    class ChannelList : public QObject
    {
        Q_OBJECT

    public:
        ChannelList(iChannel* ch);
        virtual ~ChannelList();

        void addChannel(iChannel* ch);

        int indexOfChannel(QString channelName);
        iChannel* channelByName(QString channelName);
        QList<iChannel*> channels();

    signals:
        void deleteChannel(iChannel* ch);

    public slots:

    protected:
        QList<iChannel*>_channelList;
    };
}

#endif // CHANNELLIST_H
