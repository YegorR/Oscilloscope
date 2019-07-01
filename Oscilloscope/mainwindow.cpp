#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "localchannellistview.h"

namespace oscilloscope {
    MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
        ui = new Ui::MainWindow;
        ui->setupUi(this);

        _channels = new globalChannelList(ui->verticalLayout);

        connect(_channels, SIGNAL(channelDeleted(QString)), this, SLOT(channelDelete(QString)));

        this->show();
        this->move(this->x() - this->x() / 2, this->y());

        countScopes = 1;

        on_createSimpleScope_pressed();

        setAttribute(Qt::WA_DeleteOnClose, true);
    }

    /// Обновление списка, при закрытии одного из дисплеев

    void MainWindow::deleteScope() {
        QObject *scope = sender();

        for (int i = 0; i < _scopes.length(); i++)
            if (_scopes.at(i) == scope) {
                _scopes.removeAt(i);
                break;
            }
    }

    MainWindow::~MainWindow() {
        delete ui;
        delete[] _channels;

        for (int i = 0; i < _scopes.length(); i++)
            delete[] _scopes.at(i);

        _scopes.clear();
    }
}

/// Кнопка создания нового дисплея

void oscilloscope::MainWindow::on_createSimpleScope_pressed() {
    simplescope *scope = new simplescope(0, "Дисплей " + QString::number(countScopes), _channels);
    scope->show();
    scope->move(this->x() + this->width() + (30 + 10 * _scopes.length()), this->y() + (30 + 10 * _scopes.length()));

    QObject::connect(scope, SIGNAL(destroyed()), this, SLOT(deleteScope()));

    _scopes.append(scope);
    countScopes++;
}

/// Удаление канала

void oscilloscope::MainWindow::channelDelete(const QString name) {
    for (int i = 0; i < _scopes.length(); i++)
        _scopes.at(i)->localListView()->deleteChannel(name);
}
