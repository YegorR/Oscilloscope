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
        Server *_tcpServer;

        GlobalChannelList *_globalChannelList;

    public:
        explicit ChannelController(GlobalChannelList *channels);
        bool createTcpServer(quint16 port);

    private slots:
        void receiveFrame(Frame *);

    signals:
        void channelUpdated();
    };
}

#endif
