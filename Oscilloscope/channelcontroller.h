///     ОБРАБОТЧИК ПОЛУЧЕННЫХ ДАННЫХ

#ifndef CHANNELCONTROLLER_H
#define CHANNELCONTROLLER_H

#include <QObject>

#include "server.h"
#include "frame.h"
#include "globalchannellist.h"

namespace oscilloscope {
    class ChannelController : public QObject {
      Q_OBJECT

    private:
        Server *_tcpServer = nullptr;
        Server *_udpServer = nullptr;
        GlobalChannelList *_globalChannelList;
        bool createTcpServer(quint16 port);
        bool createUdpServer(quint16 port);

    public:
        explicit ChannelController(GlobalChannelList *channels);
    public slots:
        void reloadTcpServer();
        void reloadUdpServer();

    private slots:
        void receiveFrame(Frame *);

    signals:
        void channelUpdated();
    };
}

#endif
