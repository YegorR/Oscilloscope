#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

#include "frame.h"
#include "frameparser.h"

namespace oscilloscope {
    class TcpClient : public QObject {
        Q_OBJECT

    private:
        QTcpSocket* _socket;
    public:
        TcpClient(QTcpSocket* client, QObject* parent = nullptr);
        ~TcpClient();

    signals:
        void frameIsRead(Frame*);

    private slots:
        void read();
        void disconnect();

    };
}

#endif // TCPCLIENT_H
