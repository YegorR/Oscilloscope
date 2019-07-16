#ifndef RECORDER_H
#define RECORDER_H

#include <QObject>
#include <QThread>
#include <QBuffer>
#include "datastream.h"

namespace oscilloscope {

  class RecorderThread : public QObject {
    Q_OBJECT
    private:
      bool _isInterrupted = false;
      QBuffer *_buffer;
      DataStream *_dataStream;

    private slots:
      void receiveFrame(Frame*);

    public:
      RecorderThread(DataStream *dataStream);
      void stop();
      bool isRecorded() const;
      void save(QString filename);

    public slots:
      void process();

    signals:
      void stopped();
      void error(QString errorMessage);
  };

  class Recorder : public QObject
  {
    Q_OBJECT
  private:
    QThread *_thread;
    RecorderThread *_recorderThread;
  public:
    explicit Recorder(DataStream *dataStream, QObject *parent = nullptr);
    bool isRecorded() const;
    ~Recorder();
  signals:
    void error(QString errorMessage);
  public slots:
    void startRecord();
    void stopRecord();
    void saveRecord(QString filename);
  };
}
#endif // RECORDER_H
