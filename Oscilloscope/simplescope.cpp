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

        connect(_channels, SIGNAL(itemChecked(QObject*)), this, SLOT(itemChecked(QObject *)));
        connect(_channels, SIGNAL(channelDeleted(QString)), this, SLOT(deleteChannel(QString)));

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

        metaEnum = QMetaEnum::fromType<Enums::TriggersType>();

        for (int i = 0; i < TRIGGERS_COUNT; i++)
            ui->TriggerType->addItem(metaEnum.key(i));

        _display = new Display();
        ui->DisplayLayout->insertWidget(0, _display);

        ui->TriggerLevel->setEnabled(false);
        ui->TransformSpins->setEnabled(false);
        ui->TransformSpinDouble->hide();

        this->installEventFilter(this);
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

                metaEnum = QMetaEnum::fromType<Enums::TriggersType>();
                ui->TriggerType->setCurrentIndex(metaEnum.value(atr->_triggerType));

                ui->createDublicate->setEnabled(_globalList->indexByName(channel->text()) != -1);

                ui->TransformSpinInt->setValue(atr->_moveAvgCoef);
                ui->TransformSpinDouble->setValue(atr->_expSmthCoef);
                ui->TriggerLevel->setValue(atr->_triggerLevel);

                ui->ShowReal->setChecked(atr->_showReal);
                ui->ShowImg->setChecked(atr->_showImag);
            } else {
                /// ИЗМЕНЕНИЕ АТРИБУТОВ

                QColor colorReal = colorByIndex(ui->ColorReal->currentIndex());
                QColor colorImg = colorByIndex(ui->ColorImg->currentIndex());

                QString metaName = ui->transormateType->currentText();
                QByteArray ba = metaName.toLocal8Bit();
                const char *metaKey = ba.data();

                int transformateType = metaEnum.keyToValue(metaKey);

                metaName = ui->TriggerType->currentText();
                ba = metaName.toLocal8Bit();
                metaKey = ba.data();

                metaEnum = QMetaEnum::fromType<Enums::TriggersType>();
                int triggerType = metaEnum.keyToValue(metaKey);

                if (colorReal != atr->_colorReal) {
                    atr->_colorReal = colorReal;
                    channelUpdate(findChannel(channel->text()), channel->text());
                }
                if (colorImg != atr->_colorImg) {
                    atr->_colorImg = colorImg;
                    channelUpdate(findChannel(channel->text()), channel->text());
                }

                if (transformateType != atr->_transformateType) {
                    atr->_transformateType =  static_cast<Enums::TransformateType>(transformateType);
                    recount(channel->text());
                }

                if (triggerType != atr->_triggerType) {
                    atr->_triggerType =  static_cast<Enums::TriggersType>(triggerType);
                    recount(channel->text());
                }

                if (ui->TriggerLevel->isEnabled() && atr->_triggerLevel != ui->TriggerLevel->value()) {
                    atr->_triggerLevel = ui->TriggerLevel->value();
                    recount(channel->text());
                }

                if (ui->TransformSpinInt->isEnabled() && !ui->TransformSpinInt->isHidden() && atr->_moveAvgCoef != ui->TransformSpinInt->value()) {
                    atr->_moveAvgCoef = ui->TransformSpinInt->value();
                    recount(channel->text());
                }

                if (ui->TransformSpinDouble->isEnabled() && !ui->TransformSpinDouble->isHidden() && atr->_expSmthCoef != ui->TransformSpinDouble->value()) {
                    atr->_expSmthCoef = ui->TransformSpinDouble->value();
                    recount(channel->text());
                }

                if (ui->ShowReal->isChecked() != atr->_showReal) {
                    atr->_showReal = ui->ShowReal->isChecked();
                    channelUpdate(findChannel(channel->text()), channel->text());
                }

                if (ui->ShowImg->isChecked() != atr->_showImag) {
                    atr->_showImag = ui->ShowImg->isChecked();
                    channelUpdate(findChannel(channel->text()), channel->text());
                }
            }

            /// ПРОВЕРКА НА КОМПЛЕКСНОЕ ЧИСЛО

            if (ch->dataStream()->frame()->_isComplex) {
                ui->ImgLayout->setEnabled(true);
                ui->ShowReal->setEnabled(true);;
            } else {
                ui->ImgLayout->setEnabled(false);

                ui->ShowReal->setEnabled(false);
                ui->ShowReal->setChecked(true);
            }

            /// ПРОВЕРКА МЕТОДА ПРЕОБРАЗОВАНИЯ

            if (atr->_transformateType == Enums::TransformateType::ExponentialSmoothing) {
                ui->TransformSpins->setEnabled(true);

                ui->TransformSpinInt->hide();
                ui->TransformSpinDouble->show();    
            } else if (atr->_transformateType == Enums::TransformateType::MovingAverage) {
                ui->TransformSpins->setEnabled(true);

                ui->TransformSpinDouble->hide();
                ui->TransformSpinInt->show();
            } else ui->TransformSpins->setEnabled(false);

            ui->TriggerLevel->setEnabled(atr->_triggerType != Enums::TriggersType::WithoutTriggers);
        } else {
            ui->channelName->setText("Канал не выбран");
            ui->channelController->hide();
        }
    }

    void SimpleScope::itemChecked(QObject *object) {
        QCheckBox *channel = dynamic_cast<QCheckBox *>(object);
        if (channel->isChecked()) recount(channel->text());
            else deleteChannel(channel->text());
    }

    std::tuple<iChannel *, Attributes *, bool> SimpleScope::findChannel(QString name) {
        LocalChannelListView * channelsView = _channels->channelsView();
        QCheckBox *channel;

        for (int i = 0; i < channelsView->count(); i++) {
            channel = dynamic_cast<QCheckBox *>(channelsView->itemWidget(channelsView->item(i)));

            if (channel->text() == name) {
                if (channel->isChecked()) {
                    Attributes *atr = localList()->channelsView()->attribute(i);

                    iChannel *ch;
                    bool alive = true;

                    int index = _globalList->indexByName(channel->text());
                    if (index == -1) {
                        index = _channels->indexByName(channel->text());
                        ch = _channels->channels()->at(index);

                        name = ch->dataStream()->frame()->_channelName;
                        index = _globalList->indexByName(name);
                        Channel *temp = dynamic_cast<Channel *>(_globalList->channels()->at(index));

                        alive = temp->status();
                    } else {
                        ch = _globalList->channels()->at(index);

                        Channel *temp = dynamic_cast<Channel *>(ch);
                        alive = temp->status();
                    }

                    return std::tuple<iChannel *, Attributes *, bool>(ch, atr, alive);
                }

                return std::tuple<iChannel *, Attributes *, bool>(nullptr, nullptr, false);
            }
        }

        return std::tuple<iChannel *, Attributes *, bool>(nullptr, nullptr, false);
    }

    void SimpleScope::channelUpdate(std::tuple<iChannel *, Attributes *, bool> _tuple, QString name) {
        iChannel *channel = std::get<0>(_tuple);

        if (channel) {
            Attributes *atr = std::get<1>(_tuple);
            bool alive = std::get<2>(_tuple);

            QVector<std::complex<double>> points = channel->points();
            QVector<double> offsetX = channel->dataStream()->frame()->_offsetX;

            if (points.count() > 0) {
                /// ОТРИСОВКА ДЕЙСТВИТЕЛЬНОЙ ЧАСТИ

                if (atr->_showReal) {
                    QLineSeries *series = new QLineSeries();
                    series->setName(name);

                    for (int j = 0; j < points.size(); j++)
                        series->append(offsetX.at(j), points.at(j).real());

                    series->setUseOpenGL(false);

                    QColor color = atr->_colorReal;
                    if (!alive) color.setAlphaF(0.2);
                        else color.setAlphaF(1);

                    series->setPen(QPen(color, 1));

                    _display->addGraph(series);
                } else _display->deleteGraph(name);

                /// ОТРИСОВКА МНИМОЙ ЧАСТИ

                if (atr->_showImag && channel->dataStream()->frame()->_isComplex) {
                    QLineSeries *series = new QLineSeries();
                    series->setName(name + "IMAG");

                    for (int j = 0; j < points.size(); j++)
                        series->append(offsetX.at(j), points.at(j).imag());

                    series->setUseOpenGL(false);

                    QColor color = atr->_colorImg;
                    if (!alive) color.setAlphaF(0.2);
                        else color.setAlphaF(1);

                    series->setPen(QPen(color, 1));

                    _display->addGraph(series);
                } else _display->deleteGraph(name + "IMAG");
            }
        }
    }

    void SimpleScope::recount(QString name) {
        std::tuple<iChannel *, Attributes *, bool> _tuple = findChannel(name);

        iChannel *channel = std::get<0>(_tuple);

        if (channel) {
            Attributes *atr = std::get<1>(_tuple);

            channel->trigger(atr->_triggerType, atr->_triggerLevel);
            channel->transform(atr->_transformateType, atr->_expSmthCoef, atr->_moveAvgCoef);

            channelUpdate(_tuple, name);
        }
    }

    void SimpleScope::recountDublicates(QString name) {
        LocalChannelListView * channelsView = _channels->channelsView();
        QCheckBox *channel;

        for (int i = 0; i < channelsView->count(); i++) {
            channel = dynamic_cast<QCheckBox *>(channelsView->itemWidget(channelsView->item(i)));

            if (channel->text().contains(DUBLICATE_NAME_BY_PARENT(name), Qt::CaseInsensitive) && channel->isChecked()) {
                Attributes *atr = localList()->channelsView()->attribute(i);

                iChannel *ch;
                bool alive = true;

                int index = _channels->indexByName(channel->text());
                ch = _channels->channels()->at(index);

                name = ch->dataStream()->frame()->_channelName;
                index = _globalList->indexByName(name);

                Channel *temp = dynamic_cast<Channel *>(_globalList->channels()->at(index));
                alive = temp->status();

                ch->trigger(atr->_triggerType, atr->_triggerLevel);
                ch->transform(atr->_transformateType, atr->_expSmthCoef, atr->_moveAvgCoef);

                channelUpdate(std::tuple<iChannel *, Attributes *, bool>(ch, atr, alive), channel->text());
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

    /// УДАЛЕНИЕ ГРАФИКА С ДИСПЛЕЯ

    void SimpleScope::deleteChannel(QString name) {
        _display->deleteGraph(name);
        _display->deleteGraph(name + "IMAG");
    }

    void SimpleScope::deleteDublicates(QString name) {
        _display->deleteDublicatesGraph(name);
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

    bool SimpleScope::eventFilter(QObject *object, QEvent *event) {
        if (event->type() == QEvent::WindowDeactivate) {
            if (object == this) {
                _display->keysReset();
            }
        }

        return false;
    }

    /// ДЕСТРУКТОР

    SimpleScope::~SimpleScope() {
        delete _channels;
        delete ui;
    }
}
