#ifndef TRIGGER_H
#define TRIGGER_H

#include <QVector>
#include <complex>

class Trigger{
public:
    static QVector<std::complex<double>> triggerByForwardFront(QVector<std::complex<double>> data, double level, bool isReal);
    static QVector<std::complex<double>> triggerByBackFront(QVector<std::complex<double>> data, double level, bool isReal);
    static QVector<std::complex<double>> triggerByTime(QVector<std::complex<double>> data, double time, double step);
};

#endif // TRIGGER_H
