#ifndef FRAME_H
#define FRAME_H

#include <QString>
#include <QVector>
#include <QVariant>


struct Frame {
  quint8 frameNumber;
  QString channelName;
  QString xMeasure;
  QString yMeasure;
  float divisionXValue;
  float divisionYValue;
  qint32 offsetX;
  qint32 time;

  bool isComplex;
  bool isFloat;
  quint8 pointSize;

  QVector <QVariant> points;
};

#endif // FRAME_H
