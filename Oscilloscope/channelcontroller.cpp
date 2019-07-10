#include "channelcontroller.h"

#include "channel.h"
#include "datastream.h"
#include "tcpserver.h"

#include <QDebug>

namespace oscilloscope {
    /// СОЗДАНИЕ КОНТРОЛЛЕРА КАНАЛОВ, ОТСЛЕЖИВАЮЩЕГО ПОЛУЧЕНИЕ НОВЫХ ДАННЫХ

    ChannelController::ChannelController(GlobalChannelList *channels) {
        _tcpServer = nullptr;
        _globalChannelList = channels;

        createTcpServer(8080);   
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

