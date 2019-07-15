#ifndef DISPLAY_H
#define DISPLAY_H

#include <QtCharts/QtCharts>
QT_CHARTS_USE_NAMESPACE

#include "marker.h"

namespace oscilloscope {
    class Display : public QChartView {
        Q_OBJECT

    private:
        QChart *_graph;

        bool _mouseGrab;
        double _startX, _startY;
        double _minX, _maxX, _minY, _maxY;
        QList <Marker*> _dispalyMarkers;

        void createMarker(const double &x);
        void moveMarker(QMouseEvent *event);

    protected:
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);

        void wheelEvent(QWheelEvent *event);

    public:
        explicit Display();

        void clear();
        void addGraph(QLineSeries *series);

        void setMaxX(double max);
        void setMinMaxY(double min, double max);

       ~Display();

    signals:
        void mousePress(QMouseEvent *event);
    };
}

#endif // DISPLAY_H
