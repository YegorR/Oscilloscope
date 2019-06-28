#ifndef DUBLICATECHANNEL_H
#define DUBLICATECHANNEL_H

#pragma once
#include <Channel/ichannel.h>

class DublicateChannel : public iChannel {
public:
    DublicateChannel(double x, double y, QString channelName);
};

#endif // DUBLICATECHANNEL_H
