#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QUdpSocket>
#include "server.h"

namespace oscilloscope {
  class UdpServer : public Server
  {
    Q_OBJECT
  private:
    QUdpSocket _socket;
  public:
    UdpServer(quint16 port, QObject *parent = nullptr);
    bool start();
    void stop();
  };
}

#endif // UDPSERVER_H
