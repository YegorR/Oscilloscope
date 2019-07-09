#ifndef FRAMEPARSER_H
#define FRAMEPARSER_H

#include "frame.h"
#include <QAbstractSocket>

namespace oscilloscope {
    class FrameParser {
    private:
      const quint32 _MAX_FRAME_SIZE = 4096;
    public:
        FrameParser();
        Frame *parse(QAbstractSocket* socket);
    };
}

#endif // FRAMEPARSER_H
