#include "channel.h"

Channel::Channel(double x, double y, QString channelName) : iChannel(x, y, channelName){
    _channelType = "Original";
    _invalidTimer = new QTimer();
    _invalidTimer->setInterval(3600);
    connect(_invalidTimer, SIGNAL(timeout()), this, SLOT(updateStatus()));
    _invalidTimer->start();
}

void Channel::channelDublicate(){
    _dublicates.append(new DublicateChannel(this->x,this->y,this->_channelName));
}

void Channel::updateStatus(){
    _alive = false;
}
