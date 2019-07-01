#include "ichannel.h"

iChannel::iChannel(DataStream *data)
{
    _data = data;
}

QString iChannel::nickname(){
    return _nickname;
}

QString iChannel::channelType(){
    return _channelType;
}

template <typename T>
QVector <QVector<double>> iChannel::transformType(QVector <QVector<T>> *points){
    //какие-то преобразования
    return _points;
}

QString iChannel::channelName(){
    return _data->channelName();
}
