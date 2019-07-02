#ifndef FFT_H
#define FFT_H

#include <complex>
#include <QtMath>
#include <QVector>
#include <QVariant>

class FFT{
public:
static QVector<double> goFFT(QVector<QVariant> data);
};

#endif // FFT_H
