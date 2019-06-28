#ifndef ICHANNEL_H
#define ICHANNEL_H

#pragma once
// #include <channellist.h>
#include <QVector>
#include <QString>
#include <QObject>

class iChannel : public QObject{
    Q_OBJECT
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
    template<typename T>
    QVector <QVector<double>> transformType(QVector <QVector<T>> *points);    
protected:
    QString _channelType; //В конструкторах channel и dublicateChannel будут определяться разные значения для _channelType
    double x, y;        //временная замена для Data
    QString _channelName;
    //QVector<Data> _data;
};

#endif // ICHANNEL_H
