#ifndef MARKERMEASUREMENTS_H
#define MARKERMEASUREMENTS_H

#include <QtCharts/QtCharts>
#include <QVector>
#include <complex>

#include "marker.h"

namespace oscilloscope {
    class MarkerMeasurements
    {
    public:
        // Математическое ожиание
        const std::complex<double> expectedValue(const QVector<double> offsetX, const QVector<std::complex<double>> &data,
                                                          QList<Marker*> _displayMarkers);

        // Среднеквадратическое отклонение
        const std::complex<double> standardDeviation(const QVector<double> offsetX, const QVector<std::complex<double>> &data,
                                                              QList<Marker*> _displayMarkers);

        // Мощность
        const std::complex<double> signalCapacity  (const QVector<double> offsetX, const QVector<std::complex<double>> &data,
                                                             QList<Marker*> _displayMarkers);

        // Амплитуда
        const std::complex<double> signalAmplitude (const QVector<double> offsetX, const QVector<std::complex<double>> &data,
                                                             QList<Marker*> _displayMarkers);

        // Поиск экстремумов
        const QVector<QPointF*> minAndMax (const QVector<double> offsetX, const QVector<std::complex<double>> &data,
                                                       QList<Marker*> _displayMarkers);
    };
}

#endif // MARKERMEASUREMENTS_H
