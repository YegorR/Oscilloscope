#include "attributes.h"

namespace oscilloscope {
    /// Конструктор атрибутов

    Attributes::Attributes(QColor color, int lineType, int lineWidth) {
        _color = color;
        _lineType = lineType;
        _lineWidth = lineWidth;
    }
}
