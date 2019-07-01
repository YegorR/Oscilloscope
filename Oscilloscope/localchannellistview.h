///     ВИДЖЕТ СПИСКА КАНАЛОВ ОДНОГО SIMPLESCOP`а С ДУБЛИКАТАМИ

#ifndef LOCALCHANNELLISTVIEW_H
#define LOCALCHANNELLISTVIEW_H

#include <QWidget>
#include <QListWidget>
#include <QList>

#include "channellist.h"

namespace Ui {
    class localChannelListView;
}

namespace oscilloscope {
    class localChannelListView : public QListWidget {
        Q_OBJECT

    public:
        QList<QString> _names;

        explicit localChannelListView(QWidget *parent = 0, channelList *globalList = 0);

        void deleteChannel(const QString name);

        ~localChannelListView();

    protected:
        void dragMoveEvent(QDragMoveEvent* event);
        void dropEvent(QDropEvent* event);
        void dragEnterEvent(QDragEnterEvent* event);

    private:
        channelList *_globalList;

    };
}

#endif
