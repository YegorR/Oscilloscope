///     ГЛАВНОЕ ОКНО, СОЗДАЮЩЕЕ SIMPLESCOP`ы, МЕНЕДЖЕР КАНАЛОВ И СПИСОК ОРИГИНАЛОВ КАНАЛОВ

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QtGui>

#include "simplescope.h"
#include "globalchannellist.h"
#include "channelcontroller.h"
#include "recorder.h"
#include "recordframeparser.h"

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
        void channelUpdate(QString name);

        void changeServerSettings();

        void startRecord();
        void stopRecord();
        void loadRecord();
        void playRecord();
        void stopPlayingRecord();
        void changeRecordSpeedSettings();

        void showErrorMessage(QString errorMessage);

    private:
        Ui::MainWindow *ui;

        QList<SimpleScope *> _scopes;
        GlobalChannelList *_channels;
        ChannelController *_channelController;

        QVector<RecordFrameParser *> _recordFrameParsers;
        QMenu *_menu;
        QAction *_serverAct;

        QMenu *_recordMenu;
        QAction *_startRecordAct;
        QAction *_stopRecordAct;
        QAction *_loadAct;
        QAction *_playAct;
        QAction *_stopAct;

        QAction *_speedRecordMenu;

        Recorder* _recorder;
        int countScopes;

    protected:
        bool eventFilter(QObject *object, QEvent *event);

    };
}

#endif
