#include "ichannel.h"
#include "fft.h"

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

QVector <double> iChannel::transformType(QVector <QVariant> points, int transNum){
    switch (transNum) {
    case 0:
        for (int i = 0;i < points.size();i++) {
            _points.push_front(points.value(i).toDouble());
        }
        break;
    case 1:
        _points = FFT::goFFT(points);
    }
    return _points;
}

QString iChannel::channelName(){
    return _data->channelName();
}
