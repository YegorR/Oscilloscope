#include "tcpclient.h"

#include <QDebug>

namespace oscilloscope {
    TcpClient::TcpClient(QTcpSocket* socket, QObject* parent) : QObject (parent) {
        _socket = socket;

        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnect()));
    }

    Frame *TcpClient::read() {
        QByteArray data = _socket->readAll();
        return _parser.parse(data);
    }

    void TcpClient::readyRead() {
        emit readyRead(this);
    }

    void TcpClient::disconnect() {
        delete this;
    }

    TcpClient::~TcpClient() {
        if (_socket->isOpen()) _socket->close();
    }
}
