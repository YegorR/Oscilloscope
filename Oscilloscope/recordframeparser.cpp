#include "recordframeparser.h"
#include <QDataStream>

namespace oscilloscope {

RecordFrameParser::RecordFrameParser(QString filename, QObject *parent) : QObject(parent)
{
  _timer = new NanoTimer(this);
  _file = new QFile(filename);
}

quint64 RecordFrameParser::milliPeriod() const {
  return _milliPeriod;
}

quint64 RecordFrameParser::nanoPeriod() const {
  return _nanoPeriod;
}

QString RecordFrameParser::channelName() const {
  return _channelName;
}

bool RecordFrameParser::init() {
  if (!_file->open(QIODevice::ReadOnly)) {
      emit error("Ошибка: " + QString::number(_file->error()));
      return false;
    }
  QDataStream stream(_file); stream.setByteOrder(QDataStream::LittleEndian);
   _channelName = "Запись: " + FrameParser::readString(stream);
   _file->close();
   return true;
}

void RecordFrameParser::start() {
  if (!_file->open(QIODevice::ReadOnly)) {
      emit error("Ошибка: " + QString::number(_file->error()));
      return;
    }
  QDataStream stream(_file); stream.setByteOrder(QDataStream::LittleEndian);
   _channelName = "Запись: " + FrameParser::readString(stream);

  _timer->setMilliPeriod(_milliPeriod);
  _timer->setNanoPeriod(_nanoPeriod);
  connect(_timer, SIGNAL(triggered()), this, SLOT(trigger()));
  _timer->start();
}

void RecordFrameParser::trigger() {
  if (_file->atEnd()) {
      stop();
      return;
    }
  Frame* newFrame = new Frame();
  newFrame->_channelName = _channelName;
  QDataStream stream(_file); stream.setByteOrder(QDataStream::LittleEndian);
  newFrame->_xMeasure = FrameParser::readString(stream);
  newFrame->_yMeasure = FrameParser::readString(stream);

  stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
  stream >> newFrame->_divXValue;
  stream >> newFrame->_divYValue;

  quint32 N; stream >> N;
  qint32 offsetX; stream >> offsetX;
  newFrame->_offsetX.push_back(offsetX * static_cast<double>(newFrame->_divXValue));

  stream >> newFrame->_time;

  quint32 isComplex;
  stream >> isComplex;
  newFrame->_isComplex = (!(isComplex==0));
  stream.setFloatingPointPrecision(QDataStream::DoublePrecision);

  FrameParser::readPoints<double>(stream, N, newFrame->_points, newFrame->_isComplex);

  for (int i = 1; i < static_cast<int>(N); i++)
      newFrame->_offsetX.push_back(newFrame->_offsetX.at(i - 1) +
                                   static_cast<double>(newFrame->_divXValue));

  emit frame(newFrame);
}

void RecordFrameParser::stop() {
  disconnect(_timer, SIGNAL(triggered()), this, SLOT(trigger()));
  _timer->stop();
  if (_file->isOpen())
    _file->close();
}

void RecordFrameParser::setMilliPeriod(quint64 milliPeriod) {
  _milliPeriod = milliPeriod;
  _timer->setMilliPeriod(_milliPeriod);
}

void RecordFrameParser::setNanoPeriod(quint64 nanoPeriod) {
  _nanoPeriod = nanoPeriod;
  _timer->setNanoPeriod(_nanoPeriod);
}

}
