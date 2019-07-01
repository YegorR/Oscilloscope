///     ВИДЖЕТ ОТРИСОВКИ СПИСКА ОРИГИНАЛОВ КАНАЛОВ

#ifndef GLOBALCHANNELLISTVIEW_H
#define GLOBALCHANNELLISTVIEW_H

#include <QWidget>
#include <QListWidget>

namespace Ui {
    class globalChannelListView;
}

namespace oscilloscope {
    class globalChannelListView : public QListWidget {
        Q_OBJECT

    public:
        explicit globalChannelListView(QWidget *parent = 0);

        ~globalChannelListView();

    protected:
        void startDrag(Qt::DropActions supportedActions);
        virtual void keyPressEvent(QKeyEvent *event);

    signals:
        void channelDeleted(const QString name);
    };
}

#endif
