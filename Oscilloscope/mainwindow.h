///     ГЛАВНОЕ ОКНО, СОЗДАЮЩЕЕ SIMPLESCOP`ы, МЕНЕДЖЕР КАНАЛОВ И СПИСОК ОРИГИНАЛОВ КАНАЛОВ

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QtGui>

#include "simplescope.h"
#include "globalchannellist.h"

namespace Ui {
    class MainWindow;
}

namespace oscilloscope {
    class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);     

        ~MainWindow();

    private slots:
        void on_createSimpleScope_pressed();
        void deleteScope();
        void channelDelete(const QString name);

    private:
        Ui::MainWindow *ui;

        QList<simplescope *> _scopes;
        globalChannelList *_channels;

        int countScopes;
    };
}

#endif
