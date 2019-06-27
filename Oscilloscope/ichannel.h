#ifndef ICHANNEL_H
#define ICHANNEL_H

#pragma once
#include <channellist.h>
#include <QVector>
#include <QString>

class iChannel
{
public:
    iChannel(double x, double y, QString channelName);
    ~iChannel();
    /*QVector<Data> data()*/
    QString nickname();
    QString channelType();
private:
    QVector<ChannelList*> _list;
    QVector <QVector<double>> _points;
    QString _nickname;
    QVector <QVector<double>> transformType(QVector <QVector<double>> *points);
    //QVector<Data> _data;
    double x, y;        //временная замена для Data
    QString channelName;
protected:
    QString _channelType; //В конструкторах channel и dublicateChannel будут определяться разные значения для _channelType
};

#endif // ICHANNEL_H
