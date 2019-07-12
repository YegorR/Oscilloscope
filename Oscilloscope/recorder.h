#ifndef RECORDER_H
#define RECORDER_H

#include <QObject>
#include <QThread>
#include <QBuffer>
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
        void destroy();

      signals:
        void stopped();
        void error(QString errorMessage);
    };


    QThread *_thread;
    RecorderThread *_recorderThread;
  private slots:
    void receiveError(QString errorMessage);

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
