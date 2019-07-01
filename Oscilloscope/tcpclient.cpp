#include "tcpclient.h"

TcpClient::TcpClient(QTcpSocket* socket, QObject* parent) : QObject (parent), _socket(socket)
{
  connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

Frame* TcpClient::read()
{
  QByteArray data =  _socket->readAll();
  return _parser.parse(data);
}

void TcpClient::readyRead()
{
  readyRead(this);
}

TcpClient::~TcpClient() {
  _socket->close();
  delete _socket;
}

