#ifndef FRAMEPARSER_H
#define FRAMEPARSER_H

#include "frame.h"

class FrameParser
{
public:
  FrameParser();
  Frame* parse(QByteArray& data);
};

#endif // FRAMEPARSER_H
