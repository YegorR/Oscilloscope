#include "server.h"

Server::Server(quint16 port, QObject* parent) : QObject(parent), _port(port)
{

}

quint16 Server::port() {
  return _port;
}

