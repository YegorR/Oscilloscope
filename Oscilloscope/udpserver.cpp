#include "udpserver.h"

#include <QNetworkDatagram>
#include <QDataStream>

#include <QDebug>

#include "frameparser.h"

namespace oscilloscope {
    UdpServer::UdpServer(quint16 port, QObject *parent) : Server(port, parent) {}

    bool UdpServer::start() {
        if (_socket.bind(QHostAddress::Any, port())) {
            connect(&_socket, SIGNAL(readyRead()), this, SLOT(read()));
            return true;
        }

        return false;
    }

    void UdpServer::stop() {
        _socket.disconnectFromHost();
        disconnect(&_socket);
    }

    void UdpServer::read() {
        while (_socket.hasPendingDatagrams()) {
            QNetworkDatagram datagram = _socket.receiveDatagram();

            QByteArray data = datagram.data();
            if (data.size() < 4) {
                qDebug() << "Udp datagram has small size";
                continue;
            }

            QDataStream stream(data);
            stream.setByteOrder(QDataStream::LittleEndian);
            quint32 frameSize;
            stream >> frameSize;

            if (data.size() < static_cast<int>(frameSize))
                continue;

            data = data.right(data.size() - 4);
            Frame *newFrame = FrameParser::parse(data);

            emit frame(newFrame);
        }
    }
}
