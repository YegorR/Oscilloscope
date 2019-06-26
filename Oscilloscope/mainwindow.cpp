#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace oscilloscope {
    MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
        ui = new Ui::MainWindow;
        ui->setupUi(this);
        this->show();
        this->move(this->x() - this->x() / 2, this->y());

        countScopes = 1;

        on_createSimpleScope_pressed();

        setAttribute(Qt::WA_DeleteOnClose, true);
    }

    void MainWindow::updateScopes() {
        QObject *scope = sender();

        for (int i = 0; i < _scopes.length(); i++)
            if (_scopes.at(i) == scope) {
                _scopes.removeAt(i);
                break;
            }
    }

    MainWindow::~MainWindow() {
        delete ui;

        for (int i = 0; i < _scopes.length(); i++)
            delete[] _scopes.at(i);

        _scopes.clear();
    }
}

void oscilloscope::MainWindow::on_createSimpleScope_pressed() {
    simplescope *scope = new simplescope(0, "Дисплей " + QString::number(countScopes));
    scope->show();
    scope->move(this->x() + this->width() + 30, this->y() + this->height() / 10);

    QObject::connect(scope, SIGNAL(destroyed()), this, SLOT(updateScopes()));

    _scopes << scope;
    countScopes++;
}
