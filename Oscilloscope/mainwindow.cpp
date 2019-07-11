#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "localchannellistview.h"

namespace oscilloscope {
    /// СОЗДАНИЕ ГЛАВНОГО ОКНА И ПОРАЖДЕНИЕ ДРУГИХ

    MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
        initSettings();
        createMenus();

        ui = new Ui::MainWindow;
        ui->setupUi(this);

        _channels = new GlobalChannelList(ui->verticalLayout);
        _channelController = new ChannelController(_channels);

        connect(_channels, SIGNAL(channelDeleted(QString)), this, SLOT(channelDelete(QString)));
        connect(_channels, SIGNAL(channelUpdated()), this, SLOT(channelUpdate()));
        connect(_channelController, SIGNAL(channelUpdated()), this, SLOT(channelUpdate()));

        this->show();
        this->move(this->x() - this->x() / 2, this->y());

        countScopes = 1;

        on_createSimpleScope_pressed();

        setAttribute(Qt::WA_DeleteOnClose, true);
    }

    /// ОБНОВЛЕНИЕ СПИСКА ДИСПЛЕЕВ ПРИ ЗАКРЫТИЕ ОДНОГО ИЗ НИХ

    void MainWindow::deleteScope() {
        QObject *scope = sender();

        for (int i = 0; i < _scopes.length(); i++)
            if (_scopes.at(i) == scope) {
                _scopes.removeAt(i);
                break;
            }
    }

    /// НАЖАТИЕ КНОПКИ - СОЗДАНИЕ НОВОГО ДИСПЛЕЯ

    void MainWindow::on_createSimpleScope_pressed() {
        SimpleScope *scope = new SimpleScope(0, "Дисплей " + QString::number(countScopes), _channels);
        scope->show();
        scope->move(this->x() + this->width() + (30 + 10 * _scopes.length()), this->y() - (10 * _scopes.length()));

        QObject::connect(scope, SIGNAL(destroyed()), this, SLOT(deleteScope()));

        _scopes.append(scope);
        countScopes++;
    }

    /// ОБРАБОТКА ОБНОВЛЕНИЯ КАНААЛОВ

    void MainWindow::channelUpdate() {
        for (int i = 0; i < _scopes.length(); i++) {
            _scopes.at(i)->repaint();
            _scopes.at(i)->displayUpdate();
        }
    }

    /// ОБРАБОТКА УДАЛЕНИЯ ОРИГИНАЛЬНОГО КАНАЛА

    void MainWindow::channelDelete(const QString name) {
        for (int i = 0; i < _scopes.length(); i++) {
            SimpleScope *scope = _scopes.at(i);

            scope->localList()->channelsView()->deleteChannel(name);
            scope->repaint();

            scope->localList()->channelsView()->deleteDublicates(DUBLICATE_NAME_BY_PARENT(name));
            scope->localList()->dublicatesDelete(name);

            scope->displayUpdate();
        }
    }

    /// ИНИЦИАЛИЗАЦИЯ НАСТРОЕК

    void MainWindow::initSettings() {
      QCoreApplication::setApplicationName("Oscilloscope");
      QCoreApplication::setOrganizationDomain("tomsk.lemz.ru");
      QCoreApplication::setOrganizationName("LEMZ-T");
    }

    /// СОЗДАНИЕ МЕНЮ

    void MainWindow::createMenus() {
      _menu = menuBar()->addMenu("Осциллограф");

      _serverAct = new QAction("Параметры сервера", this);
      connect(_serverAct, SIGNAL(triggered()), this, SLOT(changeServerSettings()));
      _menu->addAction(_serverAct);
    }

    void MainWindow::changeServerSettings() {
      ServerSettingsDialog dialog(this);
      dialog.exec();
    }

    /// ДЕСТРУКТОР

    MainWindow::~MainWindow() {
        delete ui;
        delete _channels;
        delete _channelController;

        for (int i = 0; i < _scopes.length(); i++)
            delete _scopes.at(i);

        _scopes.clear();
    }
}
