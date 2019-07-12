#include "recorder.h"


namespace oscilloscope {
  Recorder::Recorder(DataStream *dataStream, QObject *parent) : QObject(parent) {
    _thread = new QThread(this);
    _recorderThread = new RecorderThread(dataStream);
    connect(_thread, SIGNAL(started()), _recorderThread, SLOT(process()));
    connect(_recorderThread, SIGNAL(stopped()), _thread, SLOT(quit()));
  }

  Recorder::RecorderThread::RecorderThread(DataStream *dataStream) : _dataStream(dataStream) {
    _tempFile = new QTemporaryFile(this);
  }

  void Recorder::RecorderThread::process() {

  }

  void Recorder::startRecord() {
    _thread->start();
  }

  void Recorder::stopRecord() {
    _recorderThread->stop();
  }

  void Recorder::saveRecord(QString filename) {

  }

  void Recorder::RecorderThread::start() {
    while (!_isInterrupted) {
      _dataStream
      }
  }
}
