///     ВИДЖЕТ СПИСКА КАНАЛОВ ОДНОГО SIMPLESCOP`а С ДУБЛИКАТАМИ

#ifndef LOCALCHANNELLISTVIEW_H
#define LOCALCHANNELLISTVIEW_H

#include <QWidget>
#include <QListWidget>
#include <QList>

#include "channellist.h"
#include "attributes.h"

namespace Ui {
    class localChannelListView;
}

namespace oscilloscope {
    class localChannelListView : public QListWidget {
        Q_OBJECT

    public:
        explicit localChannelListView(QWidget *parent = nullptr);
        ~localChannelListView();

        void setAttributes(const int index, attributes &atr);
        attributes* getAttributes(const int index) const;
        void deleteChannel(const int index);

    protected:
        void dragMoveEvent(QDragMoveEvent* event);
        void dropEvent(QDropEvent* event);
        void dragEnterEvent(QDragEnterEvent* event);

    private:
        QList<attributes*> _attributesList;
        QList<QString> _names;

    };
}

#endif
