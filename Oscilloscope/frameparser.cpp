#include "frameparser.h"

#include <QDataStream>
#include <QIODevice>
#include <complex>

#include <QDebug>

namespace oscilloscope {
    QString readString(QDataStream&);

    template<typename T> void readSimplePoint(QDataStream&, uint, QVector<double>&);
    template<typename T> void readComplexPoint(QDataStream&, uint, QVector<double>&);

    /// КОНСТРУКТОР

    FrameParser::FrameParser() {}

    /// ПАРСИНГ ПОЛУЧЕННЫХ ДАННЫХ

    Frame *FrameParser::parse(QByteArray &data) {
        Frame *frame = new Frame();

        QDataStream stream(&data, QIODevice::ReadOnly);
        stream.setByteOrder(QDataStream::LittleEndian);

        quint32 size;
        stream >> size;

        if (static_cast<quint32>(data.size()) != size) {
            // Error
        }

        stream.skipRawData(4);                  // Версия протокола
        stream.skipRawData(2);                  // Reserv

        stream >> frame->_frameNumber;

        stream.skipRawData(1);

        frame->_channelName = readString(stream);

        frame->_xMeasure = readString(stream);
        frame->_yMeasure = readString(stream);

        stream >> frame->_divXValue;
        stream >> frame->_divYValue;

        quint32 N;
        stream >> N;

        quint32 offsetX;
        stream >> offsetX;
        frame->_offsetX.push_back(offsetX);

        stream >> frame->_time;

        qint8 isBigEndian;
        stream >> isBigEndian;

        if (static_cast<bool>(isBigEndian)) {
            stream.setByteOrder(QDataStream::BigEndian);
        } else {
            stream.setByteOrder(QDataStream::LittleEndian);
        }

        quint8 isComplex;
        stream >> isComplex;
        frame->_isComplex = static_cast<bool>(isComplex);

        quint8 isFloat;
        stream >> isFloat;
        frame->_isFloat = static_cast<bool>(isFloat);

        quint8 pointSize;
        stream >> pointSize;
        frame->_pointSize = pointSize;

        if (frame->_isComplex) {
            if (frame->_isFloat) {
                if (pointSize == 4) {
                    readComplexPoint<float>(stream, N, frame->_points);
                } else if (pointSize == 8) {
                    readComplexPoint<double>(stream, N, frame->_points);
                }
            } else {
                if (pointSize == 1) {
                    readComplexPoint<qint8>(stream, N, frame->_points);
                } else if (pointSize == 2) {
                    readComplexPoint<qint16>(stream, N, frame->_points);
                } else if (pointSize == 4) {
                    readComplexPoint<qint32>(stream, N, frame->_points);
                } else if (pointSize == 8) {
                    readComplexPoint<qint64>(stream, N, frame->_points);
                }
            }
        } else {
            if (frame->_isFloat) {
                if (pointSize == 4) {
                    readSimplePoint<float>(stream, N, frame->_points);
                } else if (pointSize == 8) {
                    readSimplePoint<double>(stream, N, frame->_points);
                }
            } else {
                if (pointSize == 1) {
                    readSimplePoint<qint8>(stream, N, frame->_points);
                } else if (pointSize == 2) {
                    readSimplePoint<qint16>(stream, N, frame->_points);
                } else if (pointSize == 4) {
                    readSimplePoint<qint32>(stream, N, frame->_points);
                } else if (pointSize == 8) {
                    readSimplePoint<qint64>(stream, N, frame->_points);
                }
            }

            for (int i = 1; i < (int)N; i++) {
                int x = frame->_offsetX.at(i - 1) + frame->_divXValue;
                frame->_offsetX.push_back(x);
            }
        }

        return frame;
    }

    /// СЧИТЫВАНИЕ ФОРМАТА STRING ИЗ ПОТОКА

    QString readString(QDataStream &stream) {
        quint8 strSize;
        stream >> strSize;

        if (strSize != 0) {
            QString result;

            for (int i = 0; i < strSize; i++) {
                quint8 character;
                stream >> character;
                result.append(QChar(character));
            }

            if ((strSize + 1) % 4 != 0) {
                stream.skipRawData(4 - ((strSize + 1) % 4));
            }

            return result;
        } else {
            stream.skipRawData(3);

            return QString();
        }
    }

    /// СЧИТЫВАНИЕ ОБЫЧНЫХ ТОЧЕК

    template<typename T>
    void readSimplePoint(QDataStream& stream, uint N, QVector<double>& points) {
        for (uint i = 0; i < N; ++i) {
            T point;
            stream >> point;
            qDebug() << point;
            points.push_back(point);
        }
    }

    /// СЧИТЫВАНИЕ КОМПЛЕКСНЫХ ТОЧЕК

    template<typename T>
    void readComplexPoint(QDataStream& stream, uint N, QVector<double>& points) {
        for (uint i = 0; i < N; ++i) {
            T realPoint;
            stream >> realPoint;

            T imagPoint;
            stream >> imagPoint;

            points.push_back(realPoint);
            points.push_back(imagPoint);
        }
    }
}
