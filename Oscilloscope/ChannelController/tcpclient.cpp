#include "tcpclient.h"

TcpClient::TcpClient(QTcpSocket* socket, QObject* parent) : QObject (parent), _socket(socket)
{
  connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

QByteArray TcpClient::read()
{
  return _socket->readAll();
}

void TcpClient::readyRead()
{
  readyRead(this);
}

TcpClient::~TcpClient() {
  _socket->close();
  delete _socket;
}
