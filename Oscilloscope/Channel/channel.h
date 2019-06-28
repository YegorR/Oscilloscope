#ifndef CHANNEL_H
#define CHANNEL_H

#include <QTimer>
#include <QList>

#include <Channel/dublicatechannel.h>
#include <Channel/ichannel.h>

class Channel : public iChannel{
private:
    QTimer *_invalidTimer;
    QList<DublicateChannel*> _dublicates;
    bool _alive;

public:   
    Channel(double x, double y, QString channelName);
    void channelDublicate();
    void updateStatus(); //функция используется как слот для изменения состояния _alive при сигнале таймера
};

#endif // CHANNEL_H
