///     ПОТОК СТРУКТУРИРОВАННЫХ ДАННЫХ

#ifndef DATASTREAM_H
#define DATASTREAM_H

#include <QMutex>
#include <QObject>

#include "frame.h"

namespace oscilloscope {
    class DataStream : QObject {
        Q_OBJECT

        private:
            Frame *_frame;
            QMutex _mutex;

        public:
            DataStream(Frame *frame);

            Frame *frame() const;
            void update(Frame *);

            ~DataStream();

        signals:
            void update();
    };
}

#endif
