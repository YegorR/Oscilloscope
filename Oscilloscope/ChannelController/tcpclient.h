#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

#include "frame.h"
#include "frameparser.h"

class TcpClient : public QObject
{
private:
  QTcpSocket* _socket;
  FrameParser _parser;
public:
  TcpClient(QTcpSocket* client, QObject* parent = nullptr);
  Frame* read();
  ~TcpClient();
signals:
  void readyRead(TcpClient*);
private slots:
  void readyRead();
};


#endif // TCPCLIENT_H
