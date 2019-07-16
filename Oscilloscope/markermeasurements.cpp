#include "markermeasurements.h"

namespace oscilloscope {
    // Математическое ожиание
    const std::complex<double> MarkerMeasurements::expectedValue(const QVector<double> offsetX,
                                                                          const QVector<std::complex<double>> &data,
                                                                          QList<Marker*> _displayMarkers) {
        double firstMarker = _displayMarkers[0]->anchor(), secondMarker = _displayMarkers[1]->anchor();
        double realY = 0.0, imagY = 0.0;
        double count = 0.0;

        if (firstMarker < secondMarker) {
            for (int i = 0; i < data.size(); i++) {
                if ((firstMarker <= offsetX[i]) && (offsetX[i] <= secondMarker)) {
                    realY += data[i].real();
                    imagY += data[i].imag();
                    count++;
                }
            }
        } else {
            for (int i = 0; i < data.size(); i++) {
                if ((secondMarker <= offsetX[i]) && (offsetX[i] <= firstMarker)) {
                    realY += data[i].real();
                    imagY += data[i].imag();
                    count++;
                }
            }
        }

        std::complex<double> result;

        if (count != 0.0) {
            result.real(realY / count);
            result.imag(imagY / count);
        } else {
            result.real(0);
            result.imag(0);
        }
        return result;
    }

    // Среднеквадратическое отклонение
    const std::complex<double> MarkerMeasurements::standardDeviation(const QVector<double> offsetX,
                                                                              const QVector<std::complex<double>> &data,
                                                                              QList<Marker*> _displayMarkers) {
        std::complex<double> measur = expectedValue(offsetX, data, _displayMarkers);
        double firstMarker = _displayMarkers[0]->anchor(), secondMarker = _displayMarkers[1]->anchor();
        double realY = 0.0, imagY = 0.0;
        double count = 0.0;

        if (firstMarker < secondMarker) {
            for (int i = 0; i < data.size(); i++) {
                if ((firstMarker <= offsetX[i]) && (offsetX[i] <= secondMarker)) {
                    realY = pow(data[i].real() - measur.real(), 2);
                    imagY = pow(data[i].imag() - measur.imag(), 2);
                    count++;
                }
            }
        } else {
            for (int i = 0; i < data.size(); i++) {
                if ((secondMarker <= offsetX[i]) && (offsetX[i] <= firstMarker)) {
                    realY = pow(data[i].real() - measur.real(), 2);
                    imagY = pow(data[i].imag() - measur.imag(), 2);
                    count++;
                }
            }
        }

        std::complex<double> result;

        if (count > 1) {
            result.real(sqrt((1.0 - (count - 1.0)) * realY));
            result.imag(sqrt((1.0 - (count - 1.0)) * imagY));
        } else {
            result.real(0);
            result.imag(0);
        }
        return result;
    }

    // Мощность
    const std::complex<double> MarkerMeasurements::signalCapacity  (const QVector<double> offsetX,
                                                                             const QVector<std::complex<double>> &data,
                                                                             QList<Marker*> _displayMarkers) {
        double firstMarker = _displayMarkers[0]->anchor(), secondMarker = _displayMarkers[1]->anchor();
        double sumRealY = 0.0, sumImagY = 0.0;
        double begin = 0.0, end = 0.0;

        if (firstMarker < secondMarker) {
            for (int i = 0; i < data.size(); i++) {
                if ((firstMarker <= offsetX[i]) && (offsetX[i] <= secondMarker)) {
                    if (begin == 0.0)
                        begin = offsetX[i];
                    sumRealY += pow(data[i].real(), 2);
                    sumImagY += pow(data[i].imag(), 2);
                    end++;
                }
            }
        } else {
            for (int i = 0; i < data.size(); i++) {
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
        if ((end-begin) != 0.0) {
            result.real((1.0 / (end - begin)) * sumRealY);
            result.imag((1.0 / (end - begin)) * sumImagY);
        } else {
            result.real(0);
            result.imag(0);
        }
        return result;
    }

    // Амплитуда
    const std::complex<double> MarkerMeasurements::signalAmplitude (const QVector<double> offsetX,
                                                                             const QVector<std::complex<double>> &data,
                                                                             QList<Marker*> _displayMarkers) {
        QVector<QPointF*> point = minAndMax(offsetX, data, _displayMarkers);

        std::complex<double> result;
        result.real(abs(point.at(0)->y() - point.at(2)->y()) / 2);
        result.imag(abs(point.at(1)->y() - point.at(3)->y()) / 2);
        return result;
    }

    // Комплексная амплитуда
    double complexAmplitude (const QVector<double> offsetX, const QVector<std::complex<double>> &data,
                                                 QList<Marker*> _displayMarkers) {
        double firstMarker = _displayMarkers[0]->anchor(), secondMarker = _displayMarkers[1]->anchor();
        double sum = 0.0;
        double count = 0.0;

        if (firstMarker < secondMarker) {
            for (int i = 0; i < data.size(); i++) {
                if ((firstMarker <= offsetX[i]) && (offsetX[i] <= secondMarker)) {
                    sum += sqrt(pow(data[i].real(), 2) + pow(data[i].imag(), 2));
                    count++;
                }
            }
        } else {
            for (int i = 0; i < data.size(); i++) {
                if ((secondMarker <= offsetX[i]) && (offsetX[i] <= firstMarker)) {
                    sum += sqrt(pow(data[i].real(), 2) + pow(data[i].imag(), 2));
                    count++;
                }
            }
        }

        if (count > 0.0) {
            return (sum / count);
        } else {
            return 0;
        }
    }

    // Поиск экстремумов
    const QVector<QPointF*> MarkerMeasurements::minAndMax (const QVector<double> offsetX,
                                                                       const QVector<std::complex<double>> &data,
                                                                       QList<Marker*> _displayMarkers) {
        double firstMarker = _displayMarkers[0]->anchor(), secondMarker = _displayMarkers[1]->anchor();

        QVector<QPointF *> point;

        for (int i = 0; i < 4; i++) {
            QPointF *p;
            point.append(p);
        }

        point.at(0)->setX(-1);
        point.at(1)->setX(-1);
        point.at(2)->setX(-1);
        point.at(3)->setX(-1);

        point.at(0)->setY(9223372036854775807.0);
        point.at(1)->setY(9223372036854775807.0);
        point.at(2)->setY(-9223372036854775808.0);
        point.at(3)->setY(-9223372036854775808.0);

        if (firstMarker < secondMarker) {
            for (int i = 0; i < data.size(); i++) {
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
            for (int i = 0; i < data.size(); i++) {
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
