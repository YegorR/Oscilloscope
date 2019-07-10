#include "simplescope.h"
#include "ui_simplescope.h"

#include "dublicatechannel.h"
#include "ichannel.h"
#include "enums.h"

namespace oscilloscope {
    /// СОЗДАНИЕ ДИСПЛЕЯ

    SimpleScope::SimpleScope(QWidget *parent, const QString &name, GlobalChannelList *globalList) : QWidget(parent) {
        ui = new Ui::SimpleScope;
        ui->setupUi(this);

        _globalList = globalList;

        _channels = new LocalChannelList(ui->channelsLayout);

        connect(_channels, SIGNAL(itemChecked()), this, SLOT(displayUpdate()));

        connect(ui->ShowImg, SIGNAL(stateChanged(int)), this, SLOT(displayUpdate()));
        connect(ui->ShowReal, SIGNAL(stateChanged(int)), this, SLOT(displayUpdate()));

        ui->DisplayName->setText(name);
        setAttribute(Qt::WA_DeleteOnClose, true);

        ui->channelController->hide();

        QMetaEnum metaEnum = QMetaEnum::fromType<Enums::Colors>();

        for (int i = 0; i < COLORS_COUNT; i++) {
            ui->ColorReal->addItem(metaEnum.key(i));
            ui->ColorImg->addItem(metaEnum.key(i));
        }

        metaEnum = QMetaEnum::fromType<Enums::TransformateType>();

        for (int i = 0; i < TRANSORM_COUNT; i++)
            ui->transormateType->addItem(metaEnum.key(i));

        _display = new Display();
        ui->DisplayLayout->insertWidget(0, _display);

        ui->TransformLabel->setEnabled(false);
        ui->TransformSpins->setEnabled(false);

        ui->TransformSpinInt->setStyleSheet("color: black");
        ui->TransformSpinDouble->setStyleSheet("color: black");

        ui->TransformSpinDouble->hide();
    }

    /// ОТРИСОВКА

    void SimpleScope::paintEvent(QPaintEvent *) {
        LocalChannelListView * channelsView = _channels->channelsView();
        QCheckBox *channel = dynamic_cast<QCheckBox *>(channelsView->itemWidget(channelsView->currentItem()));

        /// Получение и изменение атрибутов отрисовки

        if (channel) {
            iChannel *ch;

            int index = _globalList->indexByName(channel->text());
            if (index == -1) {
                index = _channels->indexByName(channel->text());
                ch = _channels->channels()->at(index);
            } else ch = _globalList->channels()->at(index);

            Attributes *atr = channelsView->attribute(channelsView->currentRow());
            QMetaEnum metaEnum = QMetaEnum::fromType<Enums::TransformateType>();

            /// ОБНОВЛЕНИЕ ВЫВОДА ТЕКУЩИХ АТРИБУТОВ

            if (ui->channelName->text() != channel->text()) {
                ui->channelName->setText(channel->text());
                ui->channelController->show();

                ui->ColorReal->setCurrentIndex(colorIndex(atr->_colorReal));
                ui->ColorImg->setCurrentIndex(colorIndex(atr->_colorImg));

                ui->transormateType->setCurrentIndex(metaEnum.value(atr->_transformateType));

                ui->createDublicate->setEnabled(_globalList->indexByName(channel->text()) != -1);

                if (ui->TransformSpinInt->isEnabled() && !ui->TransformSpinInt->isHidden())
                    ui->TransformSpinInt->setValue(atr->_moveAvgCoef);

                if (ui->TransformSpinDouble->isEnabled() && !ui->TransformSpinDouble->isHidden())
                    ui->TransformSpinDouble->setValue(atr->_expSmthCoef);
            } else {
                /// ИЗМЕНЕНИЕ АТРИБУТОВ

                QColor colorReal = colorByIndex(ui->ColorReal->currentIndex());
                QColor colorImg = colorByIndex(ui->ColorImg->currentIndex());

                QString transName = ui->transormateType->currentText();
                QByteArray ba = transName.toLocal8Bit();
                const char *transKey = ba.data();

                int transformateType = metaEnum.keyToValue(transKey);

                if (colorReal != atr->_colorReal) {
                    atr->_colorReal = colorReal;
                    displayUpdate();
                }
                if (colorImg != atr->_colorImg) {
                    atr->_colorImg = colorImg;
                    displayUpdate();
                }

                if (transformateType != atr->_transformateType) {
                    atr->_transformateType =  static_cast<Enums::TransformateType>(transformateType);
                    displayUpdate();
                }

                if (ui->TransformSpinInt->isEnabled() && !ui->TransformSpinInt->isHidden()) {
                    atr->_moveAvgCoef = ui->TransformSpinInt->value();
                    displayUpdate();
                }

                if (ui->TransformSpinDouble->isEnabled() && !ui->TransformSpinDouble->isHidden()) {
                    atr->_expSmthCoef = ui->TransformSpinDouble->value();
                    displayUpdate();
                }
            }

            /// ПРОВЕРКА НА КОМПЛЕКСНОЕ ЧИСЛО

            if (ch->data()->frame()->_isComplex) {
                ui->ImgLayout->setEnabled(true);
                ui->ShowReal->setEnabled(true);;
            } else {
                ui->ImgLayout->setEnabled(false);

                ui->ShowReal->setEnabled(false);
                ui->ShowReal->setChecked(true);
            }

            /// ПРОВЕРКА МЕТОДА ПРЕОБРАЗОВАНИЯ

            if (atr->_transformateType == Enums::TransformateType::ExponentialSmoothing) {
                ui->TransformLabel->setEnabled(true);
                ui->TransformSpins->setEnabled(true);

                ui->TransformSpinDouble->show();
                ui->TransformSpinInt->hide();
            } else if (atr->_transformateType == Enums::TransformateType::MovingAverage) {
                ui->TransformLabel->setEnabled(true);
                ui->TransformSpins->setEnabled(true);

                ui->TransformSpinDouble->hide();
                ui->TransformSpinInt->show();
            } else {
                ui->TransformLabel->setEnabled(false);
                ui->TransformSpins->setEnabled(false);
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

        _display->clear();

        /// ПЕРЕМЕЩЕНИЕ И СКЕЙЛИНГ ГРАФИКА

        double maxX = 100, minY = -10, maxY = 10;

        for (int i = 0; i < channelsView->count(); i++) {
            Attributes *atr = localList()->channelsView()->attribute(i);
            channel = dynamic_cast<QCheckBox *>(channelsView->itemWidget(channelsView->item(i)));

            if (channel->isChecked()) {
                iChannel *ch;

                int index = _globalList->indexByName(channel->text());
                if (index == -1) {
                    index = _channels->indexByName(channel->text());
                    ch = _channels->channels()->at(index);

                    QString name = ch->data()->frame()->_channelName;
                    index = _globalList->indexByName(name);
                } else ch = _globalList->channels()->at(index);

                ch->transform(atr->_transformateType, atr->_expSmthCoef, atr->_moveAvgCoef);

                if (ch->points().size() > 0) {
                    int maxX_temp = ceil(ch->data()->frame()->_offsetX.last());
                    if (maxX_temp > maxX) maxX = maxX_temp;

                    QVector<std::complex<double>> points = ch->points();

                    for (int i = 0; i < points.length(); i++) {
                        if (points.at(i).real() > maxY) maxY = points.at(i).real();
                        if (points.at(i).real() < minY) minY = points.at(i).real();
                    }
                }
            }
        }

        _display->setMaxX(maxX);
        _display->setMinMaxY(minY, maxY);

        /// ВЫВОД ГРАФИКОВ

        for (int i = 0; i < channelsView->count(); i++) {
            Attributes *atr = localList()->channelsView()->attribute(i);
            channel = dynamic_cast<QCheckBox *>(channelsView->itemWidget(channelsView->item(i)));

            if (channel->isChecked()) {
                iChannel *ch;
                bool alive = true;

                int index = _globalList->indexByName(channel->text());
                if (index == -1) {
                    index = _channels->indexByName(channel->text());
                    ch = _channels->channels()->at(index);

                    QString name = ch->data()->frame()->_channelName;
                    index = _globalList->indexByName(name);
                    Channel *temp = dynamic_cast<Channel *>(_globalList->channels()->at(index));

                    alive = temp->status();
                } else {
                    ch = _globalList->channels()->at(index);

                    Channel *temp = dynamic_cast<Channel *>(ch);
                    alive = temp->status();
                }

                QVector<std::complex<double>> points = ch->points();
                QVector<double> offsetX = ch->data()->frame()->_offsetX;

                if (points.count() > 0) {
                    /// ОТРИСОВКА ДЕЙСТВИТЕЛЬНОЙ ЧАСТИ

                    if (ui->ShowReal->isChecked()) {
                        QLineSeries *series = new QLineSeries();

                        for (int j = 0; j < points.size(); j++)
                            series->append(offsetX.at(j), points.at(j).real());

                        series->setUseOpenGL(false);

                        QColor color = atr->_colorReal;
                        if (!alive) color.setAlphaF(0.2);
                            else color.setAlphaF(1);

                        series->setPen(QPen(color, 1));

                        _display->addGraph(series);
                    }

                    /// ОТРИСОВКА МНИМОЙ ЧАСТИ

                    if (ui->ShowImg->isChecked()) {
                        QLineSeries *series = new QLineSeries();

                        for (int j = 0; j < points.size(); j++)
                            series->append(offsetX.at(j), points.at(j).imag());

                        series->setUseOpenGL(false);

                        QColor color = atr->_colorImg;
                        if (!alive) color.setAlphaF(0.2);
                            else color.setAlphaF(1);

                        series->setPen(QPen(color, 1));

                        _display->addGraph(series);
                    }
                }
            }
        }
    }

    /// ПОЛУЧЕНИЕ ЛОКАЛЬНОГО СПИСКА КАНАЛОВ ДИСПЛЕЯ

    LocalChannelList *SimpleScope::localList() const {
        return _channels;
    }

    /// ИНДЕКС ЦВЕТА В СООТВЕТСТВИИ С ТАБЛИЦЕЙ

    int SimpleScope::colorIndex(QColor color) const {
        if (color == Qt::black) return Enums::Colors::Black;
        else if (color == Qt::red) return Enums::Colors::Red;
        else if (color == Qt::blue) return Enums::Colors::Blue;
        else if (color == Qt::green) return Enums::Colors::Green;
        else return Enums::Colors::Yellow;
    }

    /// ОПРЕДЕЛЕНИЕ ЦВЕТА ПО ИНДЕКСУ В СООТВЕТСТВИИ С ТАБЛИЦЕЙ

    QColor SimpleScope::colorByIndex(int index) const {
        if (index == Enums::Colors::Black) return Qt::black;
        else if (index == Enums::Colors::Red) return Qt::red;
        else if (index == Enums::Colors::Blue) return Qt::blue;
        else if (index == Enums::Colors::Green) return Qt::green;
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
        delete _display;
        delete _channels;

        delete ui;
    }
}
