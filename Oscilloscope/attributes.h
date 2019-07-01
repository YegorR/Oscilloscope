#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <QColor>

namespace oscilloscope
{
    class attributes
    {
    public:
        attributes();
        ~attributes();

        QColor getColor();
        int getLineType();
        int intgetLineWidht();
        void setColor(QColor color);
        void setLineType(int type);
        void setLineWydht(int widht);

    private:
        QColor _color;
        int _lineType;
        int _lineWidth;
    };
}

#endif // ATTRIBUTES_H

