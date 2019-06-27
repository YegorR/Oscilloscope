#ifndef CHANNELCONTROLLER_H
#define CHANNELCONTROLLER_H

#include <QObject>
#include <QVector>
#include "frame.h"
#include "server.h"

class ChannelController : public QObject
{
  Q_OBJECT

private:
  QVector<Server> _servers;
public:
  explicit ChannelController(QObject *parent = nullptr);

signals:

private slots:
  void receiveFrame(Frame&);
};

#endif // CHANNELCONTROLLER_H
