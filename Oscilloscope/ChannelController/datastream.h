#ifndef DATASTREAM_H
#define DATASTREAM_H

#include <QMutex>
#include "frame.h"

class DataStream
{
private:
  QString const _channelName;
  Frame* _frame = nullptr;
  QMutex _mutex;
public:
  DataStream(QString);
  QString channelName() const;
  Frame* frame();
  void update(Frame*);
signals:
  void update();
};

#endif // DATASTREAM_H
