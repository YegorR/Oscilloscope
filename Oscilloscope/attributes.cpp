#include "attributes.h"

namespace oscilloscope {
    /// Конструктор атрибутов

    Attributes::Attributes() {
        _colorReal = Qt::black;
        _colorImg = Qt::black;

        _lineType = 0;
        _lineWidth = 1;

        _expSmthCoef = 0.0;
        _moveAvgCoef = 0;

        _transformateType = Enums::TransformateType::None;
    }
}
