#include "attributes.h"

namespace oscilloscope
{
    attributes::attributes()
    {
        _color = Qt::black;
        _lineType = 0;
        _lineWidth = 0;
    }

    attributes::~attributes() {}

    QColor attributes::getColor()
    {
        return _color;
    }

    int attributes::getLineType()
    {
        return _lineType;
    }

    int attributes::intgetLineWidht()
    {
        return _lineWidth;
    }

    void attributes::setColor(QColor color)
    {
        _color = color;
    }

    void attributes::setLineType(int type)
    {
        _lineType = type;
    }

    void attributes::setLineWydht(int widht)
    {
        _lineWidth = widht;
    }
}
