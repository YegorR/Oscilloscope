#include "tcpclient.h"

#include <QDebug>
#include <QDataStream>
#include <QByteArray>

namespace oscilloscope {
    TcpClient::TcpClient(QTcpSocket* socket, QObject* parent) : QObject (parent) {
        _socket = socket;

        connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnect()));
    }

    void TcpClient::read() {
        static quint32 frameSize = 0;
        if (frameSize == 0) {
            if (_socket->bytesAvailable() < 4) {
                return;
              } else {
                QDataStream stream(_socket->read(4));
                stream.setByteOrder(QDataStream::LittleEndian);
                stream >> frameSize;
                qDebug() << "FrameSize: " << frameSize;
              }
          }
        if (frameSize > 4) {
            if (_socket->bytesAvailable() < frameSize - 4) {
                qDebug() << "_socket->bytesAvailable() < frameSize - 4";
                return;
              }
            else {
                QByteArray data = _socket->read(frameSize - 4);
                frameSize = 0;
                qDebug() << "Read to parse";
                emit frameIsRead(FrameParser::parse(data));
                read();
              }
          }
        if (frameSize <= 4) {
            frameSize = 0;
          }
    }

    void TcpClient::disconnect() {
        delete this;
    }

    TcpClient::~TcpClient() {
        if (_socket->isOpen()) _socket->close();
    }
}
