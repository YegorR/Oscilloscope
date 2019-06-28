#ifndef CHANNELCONTROLLER_H
#define CHANNELCONTROLLER_H

#include <QObject>
#include <QVector>
#include "frame.h"
#include "server.h"
#include "Channel/ChannelList/globalchannellist.h"

class ChannelController : public QObject
{
  Q_OBJECT

private:
  Server* _tcpServer = nullptr;
  //Server& _udpServer;
  GlobalChannelList _globalChannelList;
public:
  explicit ChannelController(QObject *parent = nullptr);
  bool createTcpServer(quint16 port);
signals:

private slots:
  void receiveFrame(Frame*);
};

#endif // CHANNELCONTROLLER_H
