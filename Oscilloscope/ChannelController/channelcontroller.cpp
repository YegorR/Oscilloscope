#include "channelcontroller.h"
#include "tcpserver.h"
#include "Channel/channel.h"
#include "frame.h"
#include "datastream.h"

ChannelController::ChannelController(QObject *parent) : QObject(parent)
{

}

bool ChannelController::createTcpServer(quint16 port) {
  if (_tcpServer != nullptr) {
      _tcpServer->stop();
      _tcpServer->disconnect();
      delete _tcpServer;
    }
  _tcpServer = new TcpServer(port, this);
  connect(_tcpServer, SIGNAL(frame(Frame*)), this, SLOT(receiveFrame(Frame*)));
  return _tcpServer->start();
}

void ChannelController::receiveFrame(Frame* frame) {
    Channel* channel;// = _globalChannelList.getByName(frame->channelName);
    if (channel == nullptr) {
        channel = new Channel();
        DataStream* dataStream = new DataStream(frame->channelName);
        //Как-то скрепляются они
        //В globalchannellist добавляются новый channel
      }
    else  {
        //Передать frame в соотвутствущий канал - dataStream
      }
}
