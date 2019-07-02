#ifndef ICHANNEL_H
#define ICHANNEL_H

#pragma once
#include "channellist.h"
#include "datastream.h"
#include <QVector>
#include <QString>
#include <QObject>

class iChannel : public QObject{
    Q_OBJECT
public:
    iChannel(DataStream *data);
    ~iChannel();
    QString nickname();
    QString channelType();
    QString channelName();
private:
    QVector <double> _points;
    QString _nickname;
    QVector <double> transformType(QVector <QVariant> points, int transNum);
protected:
    QString _channelType; //В конструкторах channel и dublicateChannel будут определяться разные значения для _channelType
    DataStream *_data;
};

#endif // ICHANNEL_H
