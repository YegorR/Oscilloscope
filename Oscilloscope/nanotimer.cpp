#include "nanotimer.h"

#include <thread>
#include <QDebug>

namespace oscilloscope {

  NanoTimer::NanoTimer(QObject *parent) : QObject(parent)
  {
    _thread = new QThread(this);
    _timerThread.moveToThread(_thread);
    connect(_thread, SIGNAL(started()), &_timerThread, SLOT(process()));
    connect(&_timerThread, SIGNAL(stopped()), _thread, SLOT(quit()));
    connect(&_timerThread, SIGNAL(triggered()), this, SIGNAL(triggered()));
  }

  void NanoTimer::start() {
    _timerThread.init();
    _thread->start();
  }

  void NanoTimer::stop() {
    _timerThread.stop();
  }

  NanoTimer::~NanoTimer() {
    stop();
  }

  void NanoTimer::setMilliPeriod(unsigned long milliPeriod) {
    _timerThread.setMilliPeriod(milliPeriod);
  }

  void NanoTimer::setNanoPeriod(unsigned long nanoPeriod)
  {
    _timerThread.setNanoPeriod(nanoPeriod);
  }


  void TimerThread::process() {
    while(!_isInterrupted) {
        //qDebug() << "Tick";
        unsigned long samplingPeriod = _nanoPeriod + _milliPeriod * 1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(samplingPeriod));
        if (!_isInterrupted) {
          //  qDebug() << "Tuck";
            emit triggered();
          }
      }

    emit stopped();
  }
  void TimerThread::stop() {
    _isInterrupted = true;
    emit stopped();
  }

  void TimerThread::setMilliPeriod(unsigned long milliPeriod) {
    this->_milliPeriod = milliPeriod;
  }

  void TimerThread::setNanoPeriod(unsigned long nanoPeriod) {
    this->_nanoPeriod = nanoPeriod;
  }

  void TimerThread::init() {
    _isInterrupted = false;
  }

}
