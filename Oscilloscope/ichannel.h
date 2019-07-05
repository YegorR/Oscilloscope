///     РОДИТЕЛЬ КАНАЛОВ (ДУБЛИКАТОВ И ОРИГИНАЛОВ)

#ifndef ICHANNEL_H
#define ICHANNEL_H

#define CH_ORIGINAL 0
#define CH_DUBLICATE 1

#include <QVector>
#include <QString>
#include <QObject>

#include <datastream.h>

namespace oscilloscope {
    class iChannel : public QObject {
        Q_OBJECT
    public:
        int channelType() const;
        DataStream *data() const;

        ~iChannel();

    private:
        QVector <QVector<double>> _points;

        QVector <QVector<double>> (*_transformFunc)(const DataStream *data);

        void transform();

    protected:
        explicit iChannel(DataStream *data);
        iChannel(const iChannel *channel);

        int _channelType;
        DataStream *_data;
    };

    QVector <QVector<double>> bpf(const DataStream *data);
}

#endif
