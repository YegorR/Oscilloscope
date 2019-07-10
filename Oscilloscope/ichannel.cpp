#include "ichannel.h"
#include "kiss_fft.h"
#include "signalsmoothing.h"

#include <complex>

namespace oscilloscope {
    /// СОЗДАНИЕ КАНАЛА НА ОСНОВЕ ПОЛУЧЕННЫХ СТРУКТУРИРОВАННЫХ ДАННЫХ

    iChannel::iChannel(DataStream *data) {
        _data = data;
    }

    /// СОЗДАНИЕ КАНАЛА (ДУБЛИКАТА) НА ОСНОВЕ УЖЕ СУЩЕСТВУЮЩЕГО КАНАЛА

    iChannel::iChannel(const iChannel *channel) : iChannel(channel->data()) {}

    /// ПОЛУЧЕНИЕ ТИПА КАНАЛА (ДУБЛИКАТ ИЛИ ОРИГИНАЛ)

    int iChannel::channelType() const {
        return _channelType;
    }

    /// ПОЛУЧЕНИЕ ДАННЫХ КАНАЛА

    DataStream *iChannel::data() const {
        return _data;
    }

    /// ПОЛУЧЕНИЕ МАССИВА ТОЧЕК

    QVector<std::complex<double>> iChannel::points() const {
        return _points;
    }

    /// ПРЕОБРАЗОВАНИЕ ДАННЫХ В НУЖНЫЙ НАМ ВИД

    void iChannel::transform(Enums::TransformateType type, double expSmthCoef, int movingAvgCoef) {
        if (type == Enums::TransformateType::BPF) _points = bpf(_data->frame()->_points);
        else if (type == Enums::TransformateType::ThreePointFilter) _points = threePointFilter(_data->frame()->_points);
        else if (type == Enums::TransformateType::ExponentialSmoothing) _points = expSmoothing(_data->frame()->_points, expSmthCoef);
        else if (type == Enums::TransformateType::MovingAverage) _points = movingAvg(_data->frame()->_points, movingAvgCoef);
        else _points = _data->frame()->_points;
    }

    /// ДЕСТРУКТОР

    iChannel::~iChannel() {}

    /// ВНЕШНЯЯ ФУНКЦИЯ ПРЕОБРАЗОВАНИЯ БПФ

    QVector<std::complex<double>> bpf(const QVector<std::complex<double>> &points) {
        if (points.length() <= 0) return QVector<std::complex<double>>();

        QVector<std::complex<double>> vector;

        kiss_fft_cfg cfg = kiss_fft_alloc(points.size(), 0, 0, 0);
        kiss_fft_cpx cx_in[points.size()], cx_out[points.size()];

        for (int index = 0; index < points.size(); index++) {
            cx_in[index].r = points.at(index).real();
            cx_in[index].i = points.at(index).imag();
        }

        kiss_fft(cfg, cx_in, cx_out);
        kiss_fft_free(cfg);

        for (int index = 0; index < points.size(); index++) {
            std::complex<double> point(cx_out[index].r, cx_out[index].i);
            vector.push_back(point);
        }

        return vector;
    }

    /// ВНЕШНЯЯ ФУНКЦИЯ ТРЕХТОЧЕЧНОГО ФИЛЬТРА

    QVector<std::complex<double>> threePointFilter(const QVector<std::complex<double> > &points) {
        return SignalSmoothing::threePoints(points);
    }

    /// ВНЕШНЯЯ ФУНКЦИЯ ЭКСПОНЕНЦИАЛЬНОГО СГЛАЖИВАНИЯ

    QVector<std::complex<double>> expSmoothing(const QVector<std::complex<double> > &points, double coef) {
        return SignalSmoothing::expFilter(points, coef);
    }

    /// ВНЕШНЯЯ ФУНКЦИЯ СКОЛЬЗЯЩЕГО СРЕДНЕГО

    QVector<std::complex<double>> movingAvg(const QVector<std::complex<double> > &points, int coef) {
        return SignalSmoothing::movAverage(points, coef);
    }
}

