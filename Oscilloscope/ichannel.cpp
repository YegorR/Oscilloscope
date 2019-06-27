#include "ichannel.h"

iChannel::iChannel(double x1, double y1, QString channelName1)
{
    x = x1;
    y = y1;
    _channelName = channelName1;
}

QString iChannel::nickname(){
    return _nickname;
}

QString iChannel::channelType(){
    return _channelType;
}

QVector <QVector<double>> iChannel::transformType(QVector <QVector<double>> *points){
    //какие-то преобразования
    return _points;
}
