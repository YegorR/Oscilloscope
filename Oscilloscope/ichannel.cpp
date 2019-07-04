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

QString iChannel::channelName(){
    return _data->channelName();
}
