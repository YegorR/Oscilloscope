///     РОДИТЕЛЬ СПИСКОВ ОРИГИНАЛОВ И ДУБЛИКАТОВ КАНАЛОВ

#ifndef CHANNELLIST_H
#define CHANNELLIST_H

#define CH_ALIVE Qt::black
#define CH_DEAD Qt::gray

#include <QList>
#include <QObject>

#include "ichannel.h"

namespace oscilloscope
{
    class channelList : public QObject
    {
        Q_OBJECT

    protected:
        channelList(iChannel* ch);
        ~channelList();

        void add(iChannel* ch);
        iChannel* getChannel(const QString channelName) const;
        int indexChannelByName(const QString channelName) const;
        QList<iChannel*> getChannels() const;

        QList<iChannel*> _channels;


    public slots:
        // void channelDelete(const QString name);

    signals:
        // void channelDeleted(const QString name);

    };
}

#endif
