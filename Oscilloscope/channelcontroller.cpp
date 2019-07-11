#include "channelcontroller.h"

#include "channel.h"
#include "datastream.h"
#include "tcpserver.h"
#include "udpserver.h"

#include <QDebug>
#include <QSettings>

namespace oscilloscope {
    /// СОЗДАНИЕ КОНТРОЛЛЕРА КАНАЛОВ, ОТСЛЕЖИВАЮЩЕГО ПОЛУЧЕНИЕ НОВЫХ ДАННЫХ

    ChannelController::ChannelController(GlobalChannelList *channels) {
        _globalChannelList = channels;

        QSettings settings;
        settings.beginGroup("server");
        createTcpServer(static_cast<quint16>(settings.value("tcp", 8080).toUInt()));
        createUdpServer(static_cast<quint16>(settings.value("udp", 8080).toUInt()));
        settings.endGroup();
    }

    /// СОЗДАНИЕ ТСП СЕРВЕРА

    bool ChannelController::createTcpServer(quint16 port) {
        if (_tcpServer != nullptr) {
            _tcpServer->stop();
            _tcpServer->disconnect();

            delete _tcpServer;
        }

        _tcpServer = new TcpServer(port, this);
        connect(_tcpServer, SIGNAL(frame(Frame *)), this, SLOT(receiveFrame(Frame *)));

        return _tcpServer->start();
    }

    /// СОЗДАНИЕ УДП СЕРВЕРА

    bool ChannelController::createUdpServer(quint16 port) {
        if (_udpServer != nullptr) {
            _udpServer->stop();
            _udpServer->disconnect();

            delete _udpServer;
        }

        _udpServer = new UdpServer(port, this);
        connect(_udpServer, SIGNAL(frame(Frame *)), this, SLOT(receiveFrame(Frame *)));

        return _udpServer->start();
    }

    /// ПРИНЯТИЕ КАДРА ДАННЫХ

    void ChannelController::receiveFrame(Frame *frame) {
        int index = _globalChannelList->indexByName(frame->_channelName);
        Channel *channel;

        if (index == -1) {
            DataStream *dataStream = new DataStream(frame);

            channel = new Channel(dataStream);

            _globalChannelList->add(channel);

            connect(channel, SIGNAL(channelUpdated(Channel*)), _globalChannelList, SLOT(channelUpdate(Channel*)));
        } else {
            channel = static_cast<Channel *>(_globalChannelList->channels()->at(index));

            if (channel->data()->frame()->_time == frame->_time) {
                channel->data()->insert(frame);
            } else channel->data()->update(frame);

            channel->channelConnected();

            emit channelUpdated();
        }
    }
}

