#include "simplescope.h"
#include "ui_simplescope.h"
#include "dublicatechannel.h"

#include <QDebug>

namespace oscilloscope {
    /// СОЗДАНИЕ ДИСПЛЕЯ

    SimpleScope::SimpleScope(QWidget *parent, const QString &name, GlobalChannelList *globalList) : QWidget(parent) {
        ui = new Ui::SimpleScope;
        ui->setupUi(this);

        _globalList = globalList;

        _channels = new LocalChannelList(ui->channelsLayout);

        connect(_channels, SIGNAL(itemChecked()), this, SLOT(displayUpdate()));

        ui->DisplayName->setText(name);
        setAttribute(Qt::WA_DeleteOnClose, true);

        ui->channelController->hide();

        QMetaEnum metaEnum = QMetaEnum::fromType<Colors>();

        for (int i = 0; i < COLORS_COUNT; i++)
            ui->color->addItem(metaEnum.key(i));

        ui->Display->xAxis->setRange(0, 100);
        ui->Display->yAxis->setRange(-100, 100);
        ui->Display->xAxis->setLabel("x");
        ui->Display->yAxis->setLabel("y");

        ui->Display->setInteraction(QCP::iRangeDrag, true);
        ui->Display->setInteraction(QCP::iRangeZoom, true);
        ui->Display->axisRect()->setRangeDrag(Qt::Vertical);
        ui->Display->axisRect()->setRangeZoom(Qt::Vertical);

        ui->Display->xAxis->setBasePen(QPen(Qt::white, 0));
        ui->Display->yAxis->setBasePen(QPen(Qt::white, 0));
    }

    /// ОТРИСОВКА

    void SimpleScope::paintEvent(QPaintEvent *) {
        LocalChannelListView * channelsView = _channels->channelsView();
        QCheckBox *channel = dynamic_cast<QCheckBox *>(channelsView->itemWidget(channelsView->currentItem()));

        /// Получение и изменение атрибутов отрисовки

        if (channel) {
            if (ui->channelName->text() != channel->text()) {
                ui->channelName->setText(channel->text());
                ui->channelController->show();

                Attributes *atr = channelsView->attribute(channelsView->currentRow());
                ui->color->setCurrentIndex(colorIndex(atr->_color));

                if (_globalList->indexByName(channel->text()) == -1) ui->createDublicate->hide();
                    else ui->createDublicate->show();
            } else {
                QColor color = colorByIndex(ui->color->currentIndex());
                Attributes *atr = channelsView->attribute(channelsView->currentRow());

                if (color != atr->_color) {
                    atr->_color = color;
                    displayUpdate();
                }
            }
        } else {
            ui->channelName->setText("Канал не выбран");
            ui->channelController->hide();
        }
    }

    /// ОБНОВЛЕНИЕ ДИСПЛЕЯ

    void SimpleScope::displayUpdate() {
        LocalChannelListView * channelsView = _channels->channelsView();
        QCheckBox *channel = dynamic_cast<QCheckBox *>(channelsView->itemWidget(channelsView->currentItem()));

        ui->Display->clearGraphs();

        for (int i = 0; i < channelsView->count(); i++) {
            channel = dynamic_cast<QCheckBox *>(channelsView->itemWidget(channelsView->item(i)));

            if (channel->isChecked()) {
                iChannel *ch;

                int index = _globalList->indexByName(channel->text());
                if (index == -1) {
                    index = _channels->indexByName(channel->text());
                    ch = _channels->channels()->at(index);
                } else ch = _globalList->channels()->at(index);

                QVector<double> points = ch->data()->frame()->_points;
                QVector<double> offsetX = ch->data()->frame()->_offsetX;

                if (points.count() > 0) {
                    ui->Display->addGraph()->setData(offsetX, points);

                    int attributeIndex = _channels->channelsView()->row(_channels->channelsView()->itemByName(channel->text()));
                    ui->Display->graph(i)->setPen(QPen(_channels->channelsView()->attribute(attributeIndex)->_color, 1));

                    //for (int j = 0; j < offsetX.size(); j++) {
                        //qDebug() << QString::number(points.at(j)) + " : " + QString::number(offsetX.at(j));
                    //}

                }
            }
        }

        ui->Display->replot(QCustomPlot::rpQueuedRefresh);
    }

    /// ПОЛУЧЕНИЕ ЛОКАЛЬНОГО СПИСКА КАНАЛОВ ДИСПЛЕЯ

    LocalChannelList *SimpleScope::localList() const {
        return _channels;
    }

    /// ИНДЕКС ЦВЕТА В СООТВЕТСТВИИ С ТАБЛИЦЕЙ

    int SimpleScope::colorIndex(QColor color) const {
        if (color == Qt::black) return Colors::Black;
        else if (color == Qt::red) return Colors::Red;
        else if (color == Qt::blue) return Colors::Blue;
        else if (color == Qt::green) return Colors::Green;
        else return Colors::Yellow;
    }

    /// ОПРЕДЕЛЕНИЕ ЦВЕТА ПО ИНДЕКСУ В СООТВЕТСТВИИ С ТАБЛИЦЕЙ

    QColor SimpleScope::colorByIndex(int index) const {
        if (index == Colors::Black) return Qt::black;
        else if (index == Colors::Red) return Qt::red;
        else if (index == Colors::Blue) return Qt::blue;
        else if (index == Colors::Green) return Qt::green;
        else return Qt::yellow;
    }

    /// НАЖАТИЕ КНОПКИ - СОЗДАНИЕ ДУБЛИКАТА КАНАЛА

    void SimpleScope::on_createDublicate_pressed() {
        LocalChannelListView * channelsView = _channels->channelsView();
        QCheckBox *item = dynamic_cast<QCheckBox *>(channelsView->itemWidget(channelsView->currentItem()));

        if (item) {
            int index = _globalList->indexByName(item->text());

            Channel *channel = static_cast<Channel *>(_globalList->channels()->at(index));
            DublicateChannel *dublicate = new DublicateChannel(channel);

            _channels->add(dublicate);
        }

    }

    /// ДЕСТРУКТОР

    SimpleScope::~SimpleScope() {
        delete ui;
        delete _channels;
    }
}
