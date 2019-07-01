///     SIMPLESCOPE, СОЗДАЕТ ДИСПЛЕЙ ДЛЯ ОТРИСОВКИ ГРАФИКОВ И СПИСОК СВОИХ КАНАЛОВ

#ifndef SIMPLESCOPE_H
#define SIMPLESCOPE_H

#define SIMPLESCOPE_NAME_DEF "Неопределенный дисплей"

#include <QWidget>
#include <QListWidget>

#include "localchannellistview.h"
#include "channellist.h"

namespace Ui {
    class simplescope;
}

namespace oscilloscope {
    class simplescope : public QWidget {
        Q_OBJECT

    public:
        explicit simplescope(QWidget *parent = 0, const QString &name = SIMPLESCOPE_NAME_DEF, channelList *globalList = 0);

        localChannelListView *localListView();

        ~simplescope();

    private:
        Ui::simplescope *ui;

        channelList *_globalList;
        localChannelListView *_localListView;

    protected:
        void closeEvent(QCloseEvent *event);
    private slots:
        void on_DublicateChannel_pressed();
    };
}

#endif
