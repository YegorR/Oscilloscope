///     АТРИБУТЫ ЛОКАЛЬНОГО КАНАЛА ДЛЯ ОТРИСОВКА НА ДИСПЛЕЕ

#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <QColor>

namespace oscilloscope {
    struct Attributes {
        QColor _color;

        int _lineType;
        int _lineWidth;

        Attributes(QColor color = Qt::black, int lineType = 0, int lineWidth = 0);
    };
}

#endif
