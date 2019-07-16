#ifndef PLAYRECORDSPEEDDIALOG_H
#define PLAYRECORDSPEEDDIALOG_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "recordframeparser.h"

namespace oscilloscope {

  class PlayRecordSpeedDialog : public QDialog
  {
    Q_OBJECT
  private:
    RecordFrameParser* _parser;
    QLabel* _milliPeriodLabel;
    QLabel* _nanoPeriodLabel;
    QLineEdit* _milliPeriodEdit;
    QLineEdit* _nanoPeriodEdit;
    QIntValidator* _validator;
    QGridLayout* _layout;
    QHBoxLayout *_buttonLayout;
    QPushButton* _okButton;
    QPushButton* _cancelButton;
  private slots:
    void clickOk();
    void clickCancel();
  public:
    PlayRecordSpeedDialog(RecordFrameParser* parser, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  };
}
#endif // PLAYRECORDSPEEDDIALOG_H
