#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QVector>
#include <QTcpServer>
#include <QTcpSocket>

#include "server.h"
#include "tcpclient.h"

class TcpServer : public Server
{
private:
  QTcpServer* _server;
public:
  TcpServer(quint16 port, QObject* parent = nullptr);
  bool start();
  void stop();
  ~TcpServer();
private slots:
  void receiveConnection();
  void receiveData(TcpClient* client);
};

#endif // TCPSERVER_H
