#include "ichannel.h"

iChannel::iChannel(double x1, double y1, QString channelName1)
{
    x = x1;
    y = y1;
    channelName = channelName1;
}

QString iChannel::nickname(){
    return _nickname;
}

QString iChannel::channelType(){
    return _channelType;
}
