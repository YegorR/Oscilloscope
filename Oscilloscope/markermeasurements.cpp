#include "markermeasurements.h"

namespace oscilloscope {
    // Математическое ожиание
    const std::complex<double> MarkerMeasurements::expectedValue(const QVector<double> offsetX,
                                                                          const QVector<std::complex<double>> &data,
                                                                          QList<Marker*> _displayMarkers) {
        double firstMarker = _displayMarkers[0]->getAnchor(), secondMarker = _displayMarkers[1]->getAnchor();
        double realY = 0.0, imagY = 0.0;
        int count = 0;

        if (firstMarker < secondMarker) {
            for (int i = 0; i < offsetX.size(); i++) {
                if ((firstMarker <= offsetX[i]) && (offsetX[i] <= secondMarker)) {
                    realY += data[i].real();
                    imagY += data[i].imag();
                    count++;
                }
            }
        } else {
            for (int i = 0; i < offsetX.size(); i++) {
                if ((secondMarker <= offsetX[i]) && (offsetX[i] <= firstMarker)) {
                    realY += data[i].real();
                    imagY += data[i].imag();
                    count++;
                }
            }
        }

        std::complex<double> result;
        result.real(realY/count);
        result.imag(imagY/count);
        return result;
    }

    // Среднеквадратическое отклонение
    const std::complex<double> MarkerMeasurements::standardDeviation(const QVector<double> offsetX,
                                                                              const QVector<std::complex<double>> &data,
                                                                              QList<Marker*> _displayMarkers) {
        std::complex<double> measur = expectedValue(offsetX, data, _displayMarkers);
        double firstMarker = _displayMarkers[0]->getAnchor(), secondMarker = _displayMarkers[1]->getAnchor();
        double realY = 0.0, imagY = 0.0;
        int count = 0;

        if (firstMarker < secondMarker) {
            for (int i = 0; i < offsetX.size(); i++) {
                if ((firstMarker <= offsetX[i]) && (offsetX[i] <= secondMarker)) {
                    realY = pow(data[i].real() - measur.real(), 2);
                    imagY = pow(data[i].imag() - measur.imag(), 2);
                    count++;
                }
            }
        } else {
            for (int i = 0; i < offsetX.size(); i++) {
                if ((secondMarker <= offsetX[i]) && (offsetX[i] <= firstMarker)) {
                    realY = pow(data[i].real() - measur.real(), 2);
                    imagY = pow(data[i].imag() - measur.imag(), 2);
                    count++;
                }
            }
        }

        std::complex<double> result;
        result.real(sqrt((1 - (count - 1)) * realY));
        result.imag(sqrt((1 - (count - 1)) * imagY));
        return result;
    }

    // Мощность
    const std::complex<double> MarkerMeasurements::signalCapacity  (const QVector<double> offsetX,
                                                                             const QVector<std::complex<double>> &data,
                                                                             QList<Marker*> _displayMarkers) {
        double firstMarker = _displayMarkers[0]->getAnchor(), secondMarker = _displayMarkers[1]->getAnchor();
        double sumRealY = 0.0, sumImagY = 0.0;
        double begin = 0.0, end = 0.0;

        if (firstMarker < secondMarker) {
            for (int i = 0; i < offsetX.size(); i++) {
                if ((firstMarker <= offsetX[i]) && (offsetX[i] <= secondMarker)) {
                    if (begin == 0.0)
                        begin = offsetX[i];
                    sumRealY += pow(data[i].real(), 2);
                    sumImagY += pow(data[i].imag(), 2);
                    end++;
                }
            }
        } else {
            for (int i = 0; i < offsetX.size(); i++) {
                if ((secondMarker <= offsetX[i]) && (offsetX[i] <= firstMarker)) {
                    if (begin == 0.0)
                        begin = offsetX[i];
                    sumRealY += pow(data[i].real(), 2);
                    sumImagY += pow(data[i].imag(), 2);
                    end++;
                }
            }
        }

        std::complex<double> result;
        result.real((1 / (end - begin)) * sumRealY);
        result.imag((1 / (end - begin)) * sumImagY);
        return result;
    }

    // Амплитуда
    const std::complex<double> MarkerMeasurements::signalAmplitude (const QVector<double> offsetX,
                                                                             const QVector<std::complex<double>> &data,
                                                                             QList<Marker*> _displayMarkers) {
        QVector<std::complex<double>> minMaxValueY = minAndMax(offsetX, data, _displayMarkers);

        std::complex<double> result;
        result.real(abs(minMaxValueY[0].real() - minMaxValueY[1].real()) / 2);
        result.imag(abs(minMaxValueY[0].imag() - minMaxValueY[1].imag()) / 2);
        return result;
    }

    // Поиск экстремумов
    const QVector<QPointF*> MarkerMeasurements::minAndMax (const QVector<double> offsetX,
                                                                       const QVector<std::complex<double>> &data,
                                                                       QList<Marker*> _displayMarkers) {
        double firstMarker = _displayMarkers[0]->getAnchor(), secondMarker = _displayMarkers[1]->getAnchor();

        QVector<QPointF *> point(4);

        point.at(0)->setX(-1);
        point.at(1)->setX(-1);
        point.at(2)->setX(-1);
        point.at(3)->setX(-1);

        point.at(0)->setY(9223372036854775807.0);
        point.at(1)->setY(9223372036854775807.0);
        point.at(2)->setY(-9223372036854775808.0);
        point.at(3)->setY(-9223372036854775808.0);

        if (firstMarker < secondMarker) {
            for (int i = 0; i < offsetX.size(); i++) {
                if ((firstMarker <= offsetX[i]) && (offsetX[i] <= secondMarker)) {
                    if (point.at(0)->y() > data[i].real()) {
                        point.at(0)->setY(data[i].real());
                        point.at(0)->setX(offsetX[i]);
                    }
                    if (point.at(1)->y() > data[i].imag()) {
                        point.at(1)->setY(data[i].imag());
                        point.at(1)->setX(offsetX[i]);
                    }
                    if (point.at(2)->y() < data[i].real()) {
                        point.at(2)->setY(data[i].real());
                        point.at(2)->setX(offsetX[i]);
                    }
                    if (point.at(3)->y() < data[i].imag()) {
                        point.at(3)->setY(data[i].imag());
                        point.at(3)->setX(offsetX[i]);
                    }
                }
            }
        } else {
            for (int i = 0; i < offsetX.size(); i++) {
                if ((secondMarker <= offsetX[i]) && (offsetX[i] <= firstMarker)) {
                    if (point.at(0)->y() > data[i].real()) {
                        point.at(0)->setY(data[i].real());
                        point.at(0)->setX(offsetX[i]);
                    }
                    if (point.at(1)->y() > data[i].imag()) {
                        point.at(1)->setY(data[i].imag());
                        point.at(1)->setX(offsetX[i]);
                    }
                    if (point.at(2)->y() < data[i].real()) {
                        point.at(2)->setY(data[i].real());
                        point.at(2)->setX(offsetX[i]);
                    }
                    if (point.at(3)->y() < data[i].imag()) {
                        point.at(3)->setY(data[i].imag());
                        point.at(3)->setX(offsetX[i]);
                    }
                }
            }
        }

        return point;
    }
}
