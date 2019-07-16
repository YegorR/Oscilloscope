#ifndef RECORDFRAMEPARSER_H
#define RECORDFRAMEPARSER_H

#include <QObject>
#include <QFile>

#include "frame.h"
#include "nanotimer.h"
#include "frameparser.h"

namespace oscilloscope {

  class RecordFrameParser : public QObject
  {
    Q_OBJECT
  private:
    QFile* _file;
    quint64 _milliPeriod = 1;
    quint64 _nanoPeriod = 0;
    NanoTimer* _timer;
    QString _channelName;

  public:
    explicit RecordFrameParser(QString filename, QObject *parent = nullptr);

    quint64 milliPeriod() const;
    quint64 nanoPeriod() const;
    QString channelName() const;
    bool init();
  signals:
    void error(QString errorString);
    void frame(Frame *frame);
  public slots:
    void start();
    void stop();
    void setMilliPeriod(quint64 milliPeriod);
    void setNanoPeriod(quint64 nanoPeriod);
  private slots:
    void trigger();
  };
}
#endif // RECORDFRAMEPARSER_H
