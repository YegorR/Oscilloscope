#include "serversettingsdialog.h"

#include <QSettings>
#include <QMessageBox>

namespace oscilloscope {

  ServerSettingsDialog::ServerSettingsDialog(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f)
  {
    setWindowTitle("Параметры сервера");

    _udpLabel = new QLabel("UDP порт", this);
    _tcpLabel = new QLabel("TCP порт", this);

     QSettings settings;
     settings.beginGroup("server");
     _udpPort = static_cast<quint16>(settings.value("udp","8080").toUInt());
     _tcpPort = static_cast<quint16>(settings.value("tcp","8080").toUInt());
    _udpLine = new QLineEdit(QString::number(_udpPort), this);
    _tcpLine = new QLineEdit(QString::number(_tcpPort), this);
     settings.endGroup();

     _portValidator = new QIntValidator(this);
     _portValidator->setRange(0, 65536);
     _udpLine->setValidator(_portValidator);
     _tcpLine->setValidator(_portValidator);

     _okButton = new QPushButton("OK", this);
     connect(_okButton, SIGNAL(clicked()), this, SLOT(clickOk()));
     _cancelButton = new QPushButton("Отмена", this);
     connect(_cancelButton, SIGNAL(clicked()), this, SLOT(clickCancel()));

     _layout = new QGridLayout(this);
     setLayout(_layout);
     _layout->addWidget(_udpLabel, 0, 0);
     _layout->addWidget(_udpLine, 0, 1);
     _layout->addWidget(_tcpLabel, 1, 0);
     _layout->addWidget(_tcpLine, 1, 1);

     _buttonLayout = new QHBoxLayout();
     _layout->addLayout(_buttonLayout, 2, 0, 2, 1, Qt::AlignRight);
     _buttonLayout->addWidget(_okButton);
     _buttonLayout->addWidget(_cancelButton);
  }

  void ServerSettingsDialog::clickCancel() {
    this->close();
  }

  void ServerSettingsDialog::clickOk() {
    QSettings settings;
    settings.beginGroup("server");

    quint16 newUdpPort = static_cast<quint16>(_udpLine->text().toUInt());
    quint16 newTcpPort = static_cast<quint16>(_tcpLine->text().toUInt());
    if (_udpPort != newUdpPort) {
        settings.setValue("udp", newUdpPort);
        emit udpPortChanged();
      }
    if (_tcpPort != newTcpPort) {
        settings.setValue("tcp", newTcpPort);
        emit tcpPortChanged();
      }
    settings.endGroup();
    this->close();
  }

}