#ifndef ENUMS_H
#define ENUMS_H

#define COLORS_COUNT 5
#define TRANSORM_COUNT 5

#include <QObject>

namespace oscilloscope {
    class Enums {
    public:
        enum TransformateType {
            None,
            BPF,
            ThreePointFilter,
            ExponentialSmoothing,
            MovingAverage
        };
        Q_ENUM(TransformateType)

        enum Colors {
            Black,
            Red,
            Blue,
            Green,
            Yellow
        };
        Q_ENUM(Colors)
        Q_GADGET

        Enums() = delete;
    };

}

#endif // ENUMS_H
