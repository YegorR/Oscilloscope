#ifndef TRIGGER_H
#define TRIGGER_H

#include <QVector>
#include <complex>

namespace oscilloscope {
    class Trigger{
    public:
        static QVector<std::complex<double>> triggerByForwardFront(QVector<std::complex<double>> data, double level);       // Тригер по переднему фронту
        static QVector<std::complex<double>> triggerByBackFront(QVector<std::complex<double>> data, double level);          // Тригер по заднему фронту
        static QVector<std::complex<double>> triggerByTime(QVector<std::complex<double>> data, double time, double step);   // Тригер по времени
    };
}

#endif // TRIGGER_H
