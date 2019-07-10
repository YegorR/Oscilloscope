#ifndef SIGNALSMOOTHING_H
#define SIGNALSMOOTHING_H

#include<QVector>
#include<QVariant>
#include <complex>

class signalSmoothing{
public:
    static QVector<std::complex<double>> threePoints(QVector<std::complex<double>> data);//трехточечный фильтр
    static QVector<std::complex<double>> expFilter(QVector<std::complex<double>> data, double coef);//экспоненциальное сглаживание
    static QVector<std::complex<double>> movAverage(QVector<std::complex<double>> data, int order);//скользящее среднее
};

#endif // SIGNALSMOOTHING_H
