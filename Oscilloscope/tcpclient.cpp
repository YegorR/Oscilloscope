#include "tcpclient.h"

#include <QDebug>
#include <QDataStream>
#include <QByteArray>

namespace oscilloscope {
    TcpClient::TcpClient(QTcpSocket* socket, QObject* parent) : QObject (parent) {
        _socket = socket;

        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnect()));
    }

    Frame *TcpClient::read() {
        static quint32 frameSize = 0;
        if (frameSize == 0) {
            if (_socket->bytesAvailable() < 4) {
                return nullptr;
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
                return nullptr;
              }
            else {
                QByteArray data = _socket->read(frameSize - 4);
                frameSize = 0;
                qDebug() << "Read to parse";
                return _parser.parse(data);
              }
          }
        if (frameSize <= 4) {
            frameSize = 0;
          }
        return nullptr;
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
