#include "tcpserver.h"
#include <QDataStream>

#include "tcpclient.h"

TCPServer::TCPServer(quint16 port, QObject* parent) : Server(port, parent)
{
  _server = new QTcpServer(this);
  connect(_server, SIGNAL(newConnection()), this, SLOT(receiveConnection()));
}

TCPServer::~TCPServer()
{
  stop();
}

bool TCPServer::start()
{
  return _server->listen(QHostAddress::LocalHost, port());
}

void TCPServer::stop()
{
  _server->close();
}

void TCPServer::receiveConnection() {
  QTcpSocket* socket = _server->nextPendingConnection();
  TcpClient* client = new TcpClient(socket, this);
  connect(client, SIGNAL(readyRead(TcpClient*)), this, SLOT(receiveData(TcpClient*)));
}

void TCPServer::receiveData(TcpClient* client) {
  QByteArray data = client->read();
}
