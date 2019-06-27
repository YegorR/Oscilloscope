#include "datastream.h"

DataStream::DataStream(QString channelName) : _channelName(channelName)
{

}

QString DataStream::channelName() const {
  return _channelName;
}

void DataStream::update(Frame* frame) {
  _mutex.lock();
  if (_frame != nullptr) {
      delete _frame;
    }
  _frame = frame;
  _mutex.unlock();
  update();
}

Frame* DataStream::frame() {
  _mutex.lock();
  Frame* result = _frame;
  _frame = nullptr;
  _mutex.unlock();
  return result;
}
