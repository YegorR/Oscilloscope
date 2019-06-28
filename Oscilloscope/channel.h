#ifndef CHANNEL_H
#define CHANNEL_H

#pragma once
#include <dublicatechannel.h>
#include <ichannel.h>
#include <QTimer>
#include <QList>

class Channel : public iChannel{
private:
    QTimer *_invalidTimer;
    QList<DublicateChannel*> _dublicates;
    bool _alive;

public:   
    Channel(DataStream *data);
    void channelDublicate();
    void updateStatus(); //функция используется как слот для изменения состояния _alive при сигнале таймера
};

#endif // CHANNEL_H
