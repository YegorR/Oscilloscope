#include "udpserver.h"

namespace oscilloscope {

  UdpServer::UdpServer(quint16 port, QObject *parent) : Server(port, parent) {

  }

  bool UdpServer::start() {
    _socket.bind(QHostAddress::Any, port());
  }

  void UdpServer::stop() {
    _socket.disconnectFromHost();
  }

  UdpServer::~UdpServer() {
  }
}
