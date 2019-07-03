QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport network

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
    attributes.cpp \
    fft.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    signalsmoothing.cpp \
    simplescope.cpp \
    globalchannellistview.cpp \
    localchannellistview.cpp \
    channellist.cpp \
    globalchannellist.cpp \
    datastream.cpp \
    channelcontroller.cpp \
    frameparser.cpp \
    server.cpp \
    tcpclient.cpp \
    tcpserver.cpp \
	channel.cpp \
	dublicatechannel.cpp \
	ichannel.cpp 

HEADERS += \
    fft.h \
    mainwindow.h \
    qcustomplot.h \
    signalsmoothing.h \
    simplescope.h \
    globalchannellistview.h \
    localchannellistview.h \
    globalchannellist.h \
    channellist.h \
    channelcontroller.h \
    frame.h \
    frameparser.h \
    server.h \
    tcpclient.h \
    tcpserver.h \
	channel.h \
	dublicatechannel.h \
	ichannel.h \
	attributes.h

HEADERS += \
    mainwindow.h \
    datastream.h

FORMS += \
    mainwindow.ui \
    simplescope.ui

RESOURCES += \
    icons.qrc
