///     SIMPLESCOPE, СОЗДАЕТ ДИСПЛЕЙ ДЛЯ ОТРИСОВКИ ГРАФИКОВ И СПИСОК СВОИХ КАНАЛОВ

#ifndef SIMPLESCOPE_H
#define SIMPLESCOPE_H

#include <QWidget>
#include <QMetaEnum>
#include <tuple>

#include <QtCharts/QtCharts>
QT_CHARTS_USE_NAMESPACE

#include "localchannellist.h"
#include "globalchannellist.h"
#include "display.h"

#define SIMPLESCOPE_NAME_DEF "Неопределенный дисплей"

namespace Ui {
    class SimpleScope;
}

namespace oscilloscope {
    class SimpleScope : public QWidget {
        Q_OBJECT

    public:
        explicit SimpleScope(QWidget *parent = 0, const QString &name = SIMPLESCOPE_NAME_DEF, GlobalChannelList *globalList = 0);

        LocalChannelList *localList() const;

        int colorIndex(QColor color) const;
        QColor colorByIndex(int index) const;

        ~SimpleScope();

    private:
        Ui::SimpleScope *ui;

        GlobalChannelList *_globalList;
        LocalChannelList *_channels;

        Display *_display;

        std::tuple<iChannel *, Attributes *, bool> findChannel(QString name);

    protected:
        void paintEvent(QPaintEvent *);
        bool eventFilter(QObject *object, QEvent *event);

    private slots:
        void on_createDublicate_pressed();

    public slots:
        void channelUpdate(std::tuple<iChannel *, Attributes *, bool> _tuple, QString name);

        void itemChecked(QObject *);

        void recount(QString name);
        void recountDublicates(QString name);

        void deleteChannel(QString name);
        void deleteDublicates(QString name);

    };
}

#endif
