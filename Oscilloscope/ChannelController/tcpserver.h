#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QVector>
#include <QTcpServer>
#include <QTcpSocket>

#include "server.h"
#include "tcpclient.h"

class TCPServer : public Server
{
private:
  QTcpServer* _server;
public:
  TCPServer(quint16 port, QObject* parent = nullptr);
  bool start();
  void stop();
  ~TCPServer();
private slots:
  void receiveConnection();
  void receiveData(TcpClient* client);
};

#endif // TCPSERVER_H
