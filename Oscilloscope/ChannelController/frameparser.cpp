#include "frameparser.h"
#include <QDataStream>
#include <QIODevice>
#include <complex>


QString readString(QDataStream&);
template<typename T> void readSimplePoint(QDataStream&, uint, QVector<QVariant>&);
template<typename T> void readComplexPoint(QDataStream&, uint, QVector<QVariant>&);

FrameParser::FrameParser()
{

}

Frame* FrameParser::parse(QByteArray& data) {
  Frame* frame = new Frame();

  QDataStream stream(&data, QIODevice::ReadOnly);

  quint32 size; stream >> size;
  if (static_cast<quint32>(data.size()) != size) {
      //error
    }
  stream.skipRawData(4);  //protocol version
  stream.skipRawData(2);  //reserv
  stream >> frame->frameNumber;

  frame->channelName = readString(stream);
  frame->xMeasure = readString(stream);
  frame->yMeasure = readString(stream);

  float divXValue; stream >> divXValue; //float - 32 bit?
  frame->divisionXValue = divXValue;

  float divYValue; stream >> divYValue; //float - 32 bit?
  frame->divisionYValue = divYValue;

  quint32 N; stream >> N;
  qint32 offsetX; stream >> offsetX;
  frame->offsetX = offsetX;

  qint32 time; stream >> time;
  frame->time = time;

  qint8 isBigEndian; stream >> isBigEndian;
  if (static_cast<bool>(isBigEndian)) {
      stream.setByteOrder(QDataStream::BigEndian);
    } else {
      stream.setByteOrder(QDataStream::LittleEndian);
    }

  quint8 isComplex; stream >> isComplex;
  frame->isComplex = static_cast<bool>(isComplex);

  quint8 isFloat; stream >> isFloat;
  frame->isFloat = static_cast<bool>(isFloat);

  quint8 pointSize; stream >> pointSize;
  frame->pointSize = pointSize;

  if (frame->isComplex) {
      if (frame->isFloat) {
          if (pointSize == 4) {
              readComplexPoint<float>(stream, N, frame->points);
            }
          else if (pointSize == 8) {
              readComplexPoint<double>(stream, N, frame->points);
            }
        } else {
          if (pointSize == 1) {
              readComplexPoint<qint8>(stream, N, frame->points);
            } else if (pointSize == 2) {
              readComplexPoint<quint16>(stream, N, frame->points);
            } else if (pointSize == 4) {
              readComplexPoint<quint32>(stream, N, frame->points);
            } else if (pointSize == 8) {
              readComplexPoint<quint64>(stream, N, frame->points);
            }
        }
    } else {
      if (frame->isFloat) {
          if (pointSize == 4) {
              readSimplePoint<float>(stream, N, frame->points);
            }
          else if (pointSize == 8) {
              readSimplePoint<double>(stream, N, frame->points);
            }
        } else {
          if (pointSize == 1) {
              readSimplePoint<qint8>(stream, N, frame->points);
            } else if (pointSize == 2) {
              readSimplePoint<quint16>(stream, N, frame->points);
            } else if (pointSize == 4) {
              readSimplePoint<quint32>(stream, N, frame->points);
            } else if (pointSize == 8) {
              readSimplePoint<quint64>(stream, N, frame->points);
            }
        }
    }
  return frame;
}

QString readString(QDataStream& stream) {
  quint8 strSize;
  stream >> strSize;
  if (strSize != 0) {
      char* charString = new char[strSize];
      uint realSize;
      stream.readBytes(charString, realSize);
      QString result = QString::fromLocal8Bit(charString);
      delete [] charString;
      return result;
    } else {
      return QString();
    }
}

template<typename T>
void readSimplePoint(QDataStream& stream, uint N, QVector<QVariant>& points) {
  for (uint i = 0; i < N; ++i) {
      T point; stream >> point;
      points.push_front(QVariant(point));
    }
}

template<typename T>
void readComplexPoint(QDataStream& stream, uint N, QVector<QVariant>& points) {
  for (uint i = 0; i < N; ++i) {
      T realPoint; stream >> realPoint;
      T imagPoint; stream >> imagPoint;
      points.push_front(QVariant(realPoint));
      points.push_front(QVariant(imagPoint));
    }
}
