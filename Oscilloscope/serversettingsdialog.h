#ifndef SERVERSETTINGSDIALOG_H
#define SERVERSETTINGSDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>
#include <QPushButton>


namespace oscilloscope {
  class ServerSettingsDialog : public QDialog
  {
    Q_OBJECT
    public:
      ServerSettingsDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    private:
      QGridLayout *_layout;
      QHBoxLayout *_buttonLayout;
      QLineEdit *_udpLine;
      QLineEdit *_tcpLine;
      QLabel *_udpLabel;
      QLabel *_tcpLabel;
      QPushButton *_okButton;
      QPushButton *_cancelButton;
      QIntValidator *_portValidator;
    private slots:
      void clickOk();
      void clickCancel();
  };
}
#endif // SERVERSETTINGSDIALOG_H
