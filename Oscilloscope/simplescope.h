///     SIMPLESCOPE, СОЗДАЕТ ДИСПЛЕЙ ДЛЯ ОТРИСОВКИ ГРАФИКОВ И СПИСОК СВОИХ КАНАЛОВ

#ifndef SIMPLESCOPE_H
#define SIMPLESCOPE_H

#include <QWidget>
#include <QMetaEnum>

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
    protected:
        void paintEvent(QPaintEvent *);

    private slots:
        void on_createDublicate_pressed();

    public slots:
        void displayUpdate();
    };
}

#endif
