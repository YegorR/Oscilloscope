#include "marker.h"

namespace oscilloscope {
    Marker::Marker(QChart *graph, const double &x){
        _graph = graph;
        _x = x;

        QLogValueAxis *rangeY = static_cast<QLogValueAxis*>(_graph->axisY());
        _series = new QLineSeries();
        _series->append(x, rangeY->min());
        _series->append(x, rangeY->max());

        paintMarker(0);

        _graph->addSeries(_series);
        _series->attachAxis(_graph->axisX());
        _series->attachAxis(_graph->axisY());
    }

    double Marker::anchor() {
        return _x;
    }

    void Marker::setAnchor(const double &x) {
        _x = x;
        QLogValueAxis *rangeY = static_cast<QLogValueAxis*>(_graph->axisY());
        _series->replace(0, x, rangeY->min());
        _series->replace(1, x, rangeY->max());

        paintMarker(100);
    }

    void Marker::paintMarker(const int &lambda) {
        QPen pen;
        pen.setColor(QColor(255, 0, 0, lambda));
        pen.setWidth(2);
        pen.setStyle(Qt::DashLine);

        _series->setPointsVisible(true);
        _series->setPen(pen);
    }

    void Marker::hide() {
        _series->hide();
    }

    Marker::~Marker() {
        _series->clear();
        delete _series;
    }
}
