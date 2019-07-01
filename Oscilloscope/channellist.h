///     РОДИТЕЛЬ СПИСКОВ ОРИГИНАЛОВ И ДУБЛИКАТОВ КАНАЛОВ

#ifndef CHANNELLIST_H
#define CHANNELLIST_H

#define CH_ALIVE Qt::black
#define CH_DEAD Qt::gray

#include <QList>
#include <QObject>

namespace oscilloscope {
    class channelList : public QObject {
        Q_OBJECT

    protected:
        channelList();

        ~channelList();

        QList<QString> *_channels;

    public:
        QList<QString> *channels() const;

        void add(QString channel);

    public slots:
        void channelDelete(const QString name);

    signals:
        void channelDeleted(const QString name);

    };
}

#endif
