#ifndef MARKER_H
#define MARKER_H

#include <QtCharts/QtCharts>

namespace oscilloscope {
    class Marker
    {
    public:
        explicit Marker(QChart *graph, const double &x);
        ~Marker();

        double anchor();
        void setAnchor(const double &x);

        void hide();

    private:
        void paintMarker(const int &lambda);

        QChart *_graph;
        QLineSeries *_series;
        double _x;
    };
}

#endif // MARKER_H
