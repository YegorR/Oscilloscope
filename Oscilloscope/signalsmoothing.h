#ifndef SIGNALSMOOTHING_H
#define SIGNALSMOOTHING_H

#include<QVector>
#include<QVariant>
#include <complex>

class signalSmoothing{
public:
    static QVector<double> threePoints(QVector<double> data);//трехточечный фильтр
    static QVector<double> expFilter(QVector<double> data, double coef);//экспоненциальное сглаживание
    static QVector<double> movAverage(QVector<double> data, int order);//скользящее среднее
};

#endif // SIGNALSMOOTHING_H
