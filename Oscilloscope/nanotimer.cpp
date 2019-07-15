#include "nanotimer.h"

#include <thread>

NanoTimer::NanoTimer(QObject *parent) : QObject(parent)
{
  _thread = new QThread(this);
  _timerThread.moveToThread(_thread);
  connect(_thread, SIGNAL(started()), &_timerThread, SLOT(process()));
  connect(_thread, SIGNAL(finished()), &_timerThread, SLOT(stop()));
  connect(&_timerThread, SIGNAL(triggered()), this, SIGNAL(triggered()));
}

void NanoTimer::start() {
  _thread->start();
}

void NanoTimer::stop() {
  _thread->quit();
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


void NanoTimer::TimerThread::process() {
  while(!_isInterrupted) {
      unsigned long samplingPeriod = _nanoPeriod * 1000000 + _milliPeriod;
      std::this_thread::sleep_for(std::chrono::nanoseconds(samplingPeriod));
      if (!_isInterrupted) {
          emit triggered();
        }
    }
}
void NanoTimer::TimerThread::stop() {
  _isInterrupted = true;
}

void NanoTimer::TimerThread::setMilliPeriod(unsigned long milliPeriod) {
  this->_milliPeriod = milliPeriod;
}

void NanoTimer::TimerThread::setNanoPeriod(unsigned long nanoPeriod) {
  this->_nanoPeriod = nanoPeriod;
}
