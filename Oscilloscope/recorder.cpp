#include "recorder.h"
#include <QDebug>
#include <QDataStream>
#include <QFile>

namespace oscilloscope {

  void writeString(QDataStream&, QString&);
  void writeValues(QDataStream& stream, Frame* frame);

  Recorder::Recorder(DataStream *dataStream, QObject *parent) : QObject(parent) {
    _thread = new QThread(this);
    _recorderThread = new RecorderThread(dataStream);
    connect(_thread, SIGNAL(started()), _recorderThread, SLOT(process()));
    connect(_recorderThread, SIGNAL(stopped()), _thread, SLOT(quit()));
    connect(_recorderThread, SIGNAL(error(QString)), this, SIGNAL(error(QString)));
  }

  void Recorder::startRecord() {
    _thread->start();
  }

  void Recorder::stopRecord() {
    _recorderThread->stop();
  }

  void Recorder::saveRecord(QString filename) {
    _recorderThread->save(filename);
  }

  bool Recorder::isRecorded() const {
    return _recorderThread->isRecorded();
  }

  Recorder::~Recorder() {
    _recorderThread->stop();
    delete _recorderThread;
  }


  Recorder::RecorderThread::RecorderThread(DataStream *dataStream) : _dataStream(dataStream) {
    _buffer = new QBuffer(this);
  }

  void Recorder::RecorderThread::process() {
    QDataStream stream(_buffer);
    stream.setByteOrder(QDataStream::LittleEndian);
    writeString(stream, _dataStream->frame()->_channelName);
    connect(_dataStream, SIGNAL(receivedFrame(Frame*)), this, SLOT(receiveFrame(Frame*)));
  }

  void Recorder::RecorderThread::receiveFrame(Frame *frame) {
    if (!_isInterrupted) {
        QDataStream stream(_buffer);
        stream.setByteOrder(QDataStream::LittleEndian);
        writeString(stream, frame->_xMeasure);
        writeString(stream, frame->_yMeasure);

        stream.setFloatingPointPrecision(QDataStream::FloatingPointPrecision::SinglePrecision);
        stream << frame->_divXValue;
        stream << frame->_divYValue;
        stream << static_cast<quint32>(frame->_points.size());
        stream << static_cast<quint32>(frame->_offsetX.at(0));
        stream << frame->_time;
        frame->_isComplex ? stream << static_cast<quint8>(1) : stream << static_cast<quint8>(0);

        writeValues(stream, frame);
      }
  }

  void Recorder::RecorderThread::stop() {
    _isInterrupted = true;
    disconnect(_dataStream, SIGNAL(receivedFrame(Frame*)), this, SLOT(receiveFrame(Frame*)));
    emit(stopped());
  }

  bool Recorder::RecorderThread::isRecorded() const {
    return (_isInterrupted) && (!_buffer->buffer().isEmpty());
  }

  void Recorder::RecorderThread::save(QString filename) {
    if (!isRecorded()) {
        return;
      }
    QFile file(filename, this);
    if (!file.open(QIODevice::WriteOnly)) {
        emit error(QString("Ошибка: ") + file.error());
        return;
      }
    if (file.write(_buffer->buffer()) == -1) {
        emit error(QString("Ошибка: ") + QString::number(file.error()));
        file.close();
        return;
      };
    file.close();
  }

  void writeString(QDataStream& stream, QString& string) {
    int size = string.size();
    QByteArray byteArray = string.toUtf8();
    stream << static_cast<quint8>(size);
    for (int i = 0; i < byteArray.size(); ++i) {
        stream << static_cast<quint8>(byteArray.at(i));
      }
  }

  void writeValues(QDataStream& stream, Frame* frame) {
    stream.setFloatingPointPrecision(QDataStream::DoublePrecision);
    for(int i = 0; i < frame->_points.size();i++) {
        stream << (frame->_points.at(i).real());
        stream << (frame->_points.at(i).imag());
      }
  }
}
