#include "channel.h"

Channel::Channel(DataStream *data) : iChannel(data){
    _alive = true;
    _channelType = "Original";
    _invalidTimer = new QTimer();
    _invalidTimer->setInterval(3600);
    connect(_invalidTimer, SIGNAL(timeout()), this, SLOT(updateStatus()));
    _invalidTimer->start();
}

void Channel::channelDublicate(){
    _dublicates.append(new DublicateChannel(this->_data));
}

void Channel::updateStatus(){
    _alive = false;
}
