#ifndef NANOTIMER_H
#define NANOTIMER_H

#include <QObject>
#include <QThread>

class NanoTimer : public QObject
{
  Q_OBJECT
private:
  class TimerThread : public QObject {
    Q_OBJECT
    private:
      unsigned long _milliPeriod = 1;
      unsigned long _nanoPeriod = 0;
      bool _isInterrupted = false;
    public:
      void setMilliPeriod(unsigned long milliPeriod);
      void setNanoPeriod(unsigned long nanoPeriod);
    signals:
      void triggered();
    public slots:
      void process();
      void stop();
  };

  QThread* _thread;
  TimerThread _timerThread;

public:
  explicit NanoTimer(QObject *parent = nullptr);
  void setMilliPeriod(unsigned long milliPeriod);
  void setNanoPeriod(unsigned long nanoPeriod);
  void start();
  void stop();
  ~NanoTimer();
signals:
  void triggered();
public slots:

};

#endif // NANOTIMER_H
