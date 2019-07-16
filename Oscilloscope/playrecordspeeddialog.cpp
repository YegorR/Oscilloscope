#include "playrecordspeeddialog.h"

namespace oscilloscope {

  PlayRecordSpeedDialog::PlayRecordSpeedDialog(RecordFrameParser* parser, QWidget* parent, Qt::WindowFlags f) :
    QDialog(parent, f), _parser(parser)
  {
    setWindowTitle("Скорость воспроизведения");

    _milliPeriodLabel = new QLabel("Миллисекунды", this);
    _nanoPeriodLabel = new QLabel("Наносекунды", this);

    _validator = new QIntValidator(this);
    _validator->setBottom(0);
    _milliPeriodEdit = new QLineEdit(QString::number(_parser->milliPeriod()), this);
    _milliPeriodEdit->setValidator(_validator);
    _nanoPeriodEdit = new QLineEdit(QString::number(_parser->nanoPeriod()), this);
    _nanoPeriodEdit->setValidator(_validator);

    _okButton = new QPushButton("Ок", this);
    connect(_okButton, SIGNAL(clicked()), this, SLOT(clickOk()));
    _cancelButton = new QPushButton("Отмена", this);
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(clickCancel()));

    _layout = new QGridLayout(this);
    setLayout(_layout);
    _layout->addWidget(_milliPeriodLabel, 0, 0);
    _layout->addWidget(_milliPeriodEdit, 0, 1);
    _layout->addWidget(_nanoPeriodLabel, 1, 0);
    _layout->addWidget(_nanoPeriodEdit, 1, 1);
    _buttonLayout = new QHBoxLayout();
    _layout->addLayout(_buttonLayout, 2, 0, 1, 2);
    _buttonLayout->addWidget(_okButton);
    _buttonLayout->addWidget(_cancelButton);

    _milliPeriodLabel->setAlignment(Qt::AlignHCenter);
    _nanoPeriodLabel->setAlignment(Qt::AlignHCenter);

    this->setStyleSheet("background-color: rgb(64, 64, 64);"
                        "color: white;");

    setWindowFlags(Qt::Dialog | Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
  }

  void PlayRecordSpeedDialog::clickOk() {
     quint64 milli = _milliPeriodEdit->text().toUInt();
     quint64 nano = _nanoPeriodEdit->text().toUInt();
     _parser->setMilliPeriod(milli);
     _parser->setNanoPeriod(nano);
     this->close();
  }

  void PlayRecordSpeedDialog::clickCancel() {
    this->close();
  }

}
