#ifndef RECORDER_H
#define RECORDER_H

#include <QObject>
#include <QTemporaryFile>
#include <QThread>
#include "datastream.h"

namespace oscilloscope {

  class Recorder : public QObject
  {
    Q_OBJECT
  private:


    class RecorderThread : public QObject {
      Q_OBJECT
      private:
        bool _isInterrupted = false;
        QTemporaryFile *_tempFile;
        DataStream *_dataStream;

      public:
        RecorderThread(DataStream *dataStream);
        void stop();

      public slots:
        void process();

      signals:
        void stopped();
    };


    QThread *_thread;
    RecorderThread *_recorderThread;


  public:
    explicit Recorder(DataStream *dataStream, QObject *parent = nullptr);
    bool isRecorded() const;
    ~Recorder();
  signals:

  public slots:
    void startRecord();
    void stopRecord();
    void saveRecord(QString filename);
  };
}
#endif // RECORDER_H
