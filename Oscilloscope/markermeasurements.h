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
        static const std::complex<double> expectedValue(const QVector<double> offsetX, const QVector<std::complex<double>> &data,
                                                          QList<Marker*> _displayMarkers);

        // Среднеквадратическое отклонение
        static const std::complex<double> standardDeviation(const QVector<double> offsetX, const QVector<std::complex<double>> &data,
                                                              QList<Marker*> _displayMarkers);

        // Мощность
        static const std::complex<double> signalCapacity  (const QVector<double> offsetX, const QVector<std::complex<double>> &data,
                                                             QList<Marker*> _displayMarkers);

        // Амплитуда
        static const std::complex<double> signalAmplitude (const QVector<double> offsetX, const QVector<std::complex<double>> &data,
                                                             QList<Marker*> _displayMarkers);

        // Комплексная амплитуда
        static double complexAmplitude (const QVector<double> offsetX, const QVector<std::complex<double>> &data,
                                                             QList<Marker*> _displayMarkers);

        // Поиск экстремумов
        static const QVector<QPointF*> minAndMax (const QVector<double> offsetX, const QVector<std::complex<double>> &data,
                                                       QList<Marker*> _displayMarkers);
    };
}

#endif // MARKERMEASUREMENTS_H
