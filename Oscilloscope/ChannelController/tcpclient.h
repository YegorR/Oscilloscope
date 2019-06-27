#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

class TcpClient : public QObject
{
private:
  QTcpSocket* _socket;
public:
  TcpClient(QTcpSocket* client, QObject* parent = nullptr);
  QByteArray read();
  ~TcpClient();
signals:
  void readyRead(TcpClient*);
private slots:
  void readyRead();
};


#endif // TCPCLIENT_H
