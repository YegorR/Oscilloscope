#include "dublicatechannel.h"

namespace oscilloscope {
    /// СОЗДАНИЕ ДУБЛИКАТА НА ОСНОВЕ ОРИГИНАЛЬНОГО КАНАЛА

    DublicateChannel::DublicateChannel(const Channel *channel) : iChannel(channel) {
        _channelType = CH_DUBLICATE;
        _name = DEF_DUBLICATE_NAME;
    }

    /// ПОЛУЧЕНИЕ ИМЕНИ ДУБЛИКАТА

    QString DublicateChannel::name() const {
        return _name;
    }

    /// ИЗМЕНЕНИЕ ИМЕНИ ДУБЛИКАТА

    QString DublicateChannel::setName(QString name) {
        return (_name = name);
    }
}
