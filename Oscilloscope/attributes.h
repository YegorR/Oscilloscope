#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <QColor>

namespace oscilloscope
{
    struct Attributes
    {
        QColor _collor = QColor(0,0,0,0);
        int _lineType = 0;
        int _lineWidth = 0;
    };
}

#endif // ATTRIBUTES_H
