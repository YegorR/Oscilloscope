///     РОДИТЕЛЬ КАНАЛОВ (ДУБЛИКАТОВ И ОРИГИНАЛОВ)

#ifndef ICHANNEL_H
#define ICHANNEL_H

#define CH_ORIGINAL 0
#define CH_DUBLICATE 1

#include <QVector>
#include <QString>
#include <QObject>

#include "datastream.h"
#include "enums.h"

namespace oscilloscope {
    class iChannel : public QObject {
        Q_OBJECT
    public:
        int channelType() const;
        DataStream *data() const;
        QVector <std::complex<double>> points() const;

        void transform(Enums::TransformateType type = Enums::TransformateType::None, double expSmthCoef = 0.0, int movingAvgCoef = 0);

        ~iChannel();

    private:
        QVector <std::complex<double>> _points;

    protected:
        explicit iChannel(DataStream *data);
        iChannel(const iChannel *channel);

        int _channelType;
        DataStream *_data;
    };

    QVector<std::complex<double>> bpf(const QVector<std::complex<double>> &points);
    QVector<std::complex<double>> threePointFilter(const QVector<std::complex<double>> &points);
    QVector<std::complex<double>> expSmoothing(const QVector<std::complex<double>> &points, double coef);
    QVector<std::complex<double>> movingAvg(const QVector<std::complex<double>> &points, int coef);
}

#endif
