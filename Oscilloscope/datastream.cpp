#include "datastream.h"

namespace oscilloscope {
    /// КОНСТРУКТОР СОЗДАНИЯ ДАННЫХ НА ОСНОВЕ ПОЛУЧЕННОГО КАДРА

    DataStream::DataStream(Frame *frame) {
        _frame = frame;
    }

    /// ОБНОВЛЕНИЕ КАДРА

    void DataStream::update(Frame *frame) {
        _mutex.lock();

        if (_frame != nullptr)
            delete _frame;

        _frame = frame;

        _mutex.unlock();

        emit update();
    }

    /// ПОЛУЧЕНИЕ КАДРА

    Frame *DataStream::frame() const {
        return _frame;
    }

    /// ДЕСТРУКТОР

    DataStream::~DataStream() {
        if (_frame) delete _frame;
    }
}

