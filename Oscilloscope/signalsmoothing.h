#ifndef SIGNALSMOOTHING_H
#define SIGNALSMOOTHING_H

#include<QVector>
#include<QVariant>

class signalSmoothing{
public:
    static QVector<double> threePoints(QVector<QVariant> data);//трехточечный фильтр
    static QVector<double> expFilter(QVector<QVariant> data, double coef);//экспоненциальное сглаживание
    static QVector<double> movAverage(QVector<QVariant> data, int order);//скользящее среднее
};

#endif // SIGNALSMOOTHING_H
