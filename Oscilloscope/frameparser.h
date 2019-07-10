#ifndef FRAMEPARSER_H
#define FRAMEPARSER_H

#include "frame.h"
#include <QByteArray>

namespace oscilloscope {
    class FrameParser {
    public:
        static Frame *parse(QByteArray& data);
    };
}

#endif // FRAMEPARSER_H
