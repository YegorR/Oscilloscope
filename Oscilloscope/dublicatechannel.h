#ifndef DUBLICATECHANNEL_H
#define DUBLICATECHANNEL_H

#pragma once
#include <ichannel.h>

class DublicateChannel : public iChannel {
public:
    DublicateChannel(DataStream *data);
};

#endif // DUBLICATECHANNEL_H
