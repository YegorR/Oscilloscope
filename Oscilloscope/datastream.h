///     ПОТОК СТРУКТУРИРОВАННЫХ ДАННЫХ

#ifndef DATASTREAM_H
#define DATASTREAM_H

#include <QObject>

#include "frame.h"

namespace oscilloscope {
    class DataStream : QObject {
        Q_OBJECT

        private:
            Frame *_frame;

        public:
            DataStream(Frame *frame);

            Frame *frame() const;
            void update(Frame *);
            void insert(Frame *);

            ~DataStream();

        signals:
            void update();
    };
}

#endif
