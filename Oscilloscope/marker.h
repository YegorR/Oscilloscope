#ifndef MARKER_H
#define MARKER_H

#include <QtCharts/QtCharts>

namespace oscilloscope {
    class Marker
    {
    public:
        explicit Marker(QChart *graph, const double &x);
        ~Marker();

        double getAnchor();
        void setAnchor(const double &x);

    private:
        void paintMarker(const int &lambda);

        QChart *_graph;
        QLineSeries *_series;
        double _markerCoordinatesX;
    };
}

#endif // MARKER_H
