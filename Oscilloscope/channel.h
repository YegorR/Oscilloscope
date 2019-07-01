#ifndef CHANNEL_H
#define CHANNEL_H

#pragma once
#include <dublicatechannel.h>
#include <QTimer>
#include <QList>

class Channel : public iChannel {

private:
    QTimer _invalidTimer;
    QList<DublicateChannel*> _dublicates;
    bool _alive;

public:
    Channel();
    void channelDublicate();
};

#endif // CHANNEL_H
