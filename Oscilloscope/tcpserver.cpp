#include "tcpserver.h"
#include <QDataStream>

#include "tcpclient.h"

TcpServer::TcpServer(quint16 port, QObject* parent) : Server(port, parent)
{
  _server = new QTcpServer(this);
  connect(_server, SIGNAL(newConnection()), this, SLOT(receiveConnection()));
}

TcpServer::~TcpServer()
{
  stop();
}

bool TcpServer::start()
{
  return _server->listen(QHostAddress::LocalHost, port());
}

void TcpServer::stop()
{
  _server->close();
}

void TcpServer::receiveConnection() {
  QTcpSocket* socket = _server->nextPendingConnection();
  TcpClient* client = new TcpClient(socket, this);
  connect(client, SIGNAL(readyRead(TcpClient*)), this, SLOT(receiveData(TcpClient*)));
}

void TcpServer::receiveData(TcpClient* client) {
  Frame* newFrame = client->read();
  frame(*newFrame);
}
