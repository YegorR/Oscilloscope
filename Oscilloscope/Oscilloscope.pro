QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Oscilloscope
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        channel.cpp \
        ChannelList\channellist.cpp \
        dublicatechannel.cpp \
        ChannelList\globalchannellistview.cpp \
        ichannel.cpp \
        ChannelList\localchannellistview.cpp \
        main.cpp \
        mainwindow.cpp \
        datastream.cpp \
        ChannelController\channelcontroller.cpp \
        ChannelController\frameparser.cpp \
        ChannelController\server.cpp \
        ChannelController\tcpclient.cpp \
        ChannelController\tcpserver.cpp

HEADERS += \
        ChannelList\ChannelAttributes\attributes.h \
        channel.h \
        ChannelList\channellist.h \
        dublicatechannel.h \
        ChannelList\dublicatechannellist.h \
        ChannelList\globalchannellist.h \
        ChannelList\globalchannellistview.h \
        ichannel.h \
        ChannelList\localchannellistview.h \
        mainwindow.h \
        datastream.h \
        ChannelController\channelcontroller.h \
        ChannelController\frameparser.h \
        ChannelController\server.h \
        ChannelController\tcpclient.h \
        ChannelController\tcpserver.h

FORMS += \
        mainwindow.ui
