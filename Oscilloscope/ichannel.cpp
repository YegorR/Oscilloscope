#include "ichannel.h"

namespace oscilloscope {
    /// СОЗДАНИЕ КАНАЛА НА ОСНОВЕ ПОЛУЧЕННЫХ СТРУКТУРИРОВАННЫХ ДАННЫХ

    iChannel::iChannel(DataStream *data) {
        _data = data;

        _transformFunc = bpf;

        transform();
    }

    /// СОЗДАНИЕ КАНАЛА (ДУБЛИКАТА) НА ОСНОВЕ УЖЕ СУЩЕСТВУЮЩЕГО КАНАЛА

    iChannel::iChannel(const iChannel *channel) : iChannel(channel->data()) {}

    /// ПОЛУЧЕНИЕ ТИПА КАНАЛА (ДУБЛИКАТ ИЛИ ОРИГИНАЛ)

    int iChannel::channelType() const {
        return _channelType;
    }

    /// ПОЛУЧЕНИЕ ДАННЫХ КАНАЛА

    DataStream *iChannel::data() const {
        return _data;
    }

    /// ПРЕОБРАЗОВАНИЕ ДАННЫХ В НУЖНЫЙ НАМ ВИД

    void iChannel::transform() {
        _points = _transformFunc(_data);
    }

    /// ДЕСТРУКТОР

    iChannel::~iChannel() {}

    /// ВНЕШНЯЯ ФУНКЦИЯ ПРЕОБРАЗОВАНИЯ БПФ

    QVector<QVector<double>> bpf(const DataStream *data) {
        if (!data) return QVector<QVector<double>>();

        return QVector<QVector<double>>();
    }
}

