#include "display.h"

#include <QDebug>

namespace oscilloscope {
    Display::Display() : QChartView() {
        _graph = new QChart();
        _graph->legend()->hide();

        this->setChart(_graph);
        this->setRenderHint(QPainter::Antialiasing);

        QValueAxis *xAxis = new QValueAxis();
        xAxis->setRange(-50, 50);
        _minX = xAxis->min();
        _maxX = xAxis->max();

        QValueAxis *yAxis = new QValueAxis();
        yAxis->setRange(0, 20);
        _minY = yAxis->min();
        _maxY = yAxis->max();

        _graph->addAxis(xAxis, Qt::AlignBottom);
        _graph->addAxis(yAxis, Qt::AlignLeft);

        createMarker(_minX);
        createMarker(_maxX);

        _mouseGrab = false;
    }

    void Display::mousePressEvent(QMouseEvent *event) {
        _startX = event->x() - _graph->plotArea().x();
        _startY = event->y() - _graph->plotArea().y();

        _mouseGrab = true;
        QPointF mousePoint;
        mousePoint.setX(((_startX * (_maxX - _minX)) / _graph->plotArea().width()) + _minX);
        mousePoint.setY(_maxY - (((_startY * (_maxY - _minY)) / _graph->plotArea().height()) + _minY) - ((_maxY - _minY) / 2) + ((_maxY + _minY) / 2));
        if ((_minY <= mousePoint.y()) && (_maxY >= mousePoint.y()) && (_minX <= mousePoint.x()) && (_maxX >= mousePoint.x())) {
            event->setLocalPos(mousePoint);
            moveMarker(event);
        }
        event->accept();
        QChartView::mousePressEvent(event);
    }

    void Display::mouseReleaseEvent(QMouseEvent *event) {
        _mouseGrab = false;

        event->accept();
        QChartView::mouseReleaseEvent(event);
    }

    void Display::mouseMoveEvent(QMouseEvent *event) {
        if (_mouseGrab) {
            double divX = (_startX - event->globalX());
            double divY = (event->globalY() - _startY);

            QLogValueAxis *rangeX = static_cast<QLogValueAxis *>(_graph->axisX());
            QLogValueAxis *rangeY = static_cast<QLogValueAxis *>(_graph->axisY());

            double x1 = rangeX->min();
            double x2 = rangeX->max();
            double x3 = x2 - x1;

            double stepX = (x2 + abs(x1)) / 1000;

            double y1 = rangeY->min();
            double y2 = rangeY->max();
            double y3 = y2 - y1;

            double stepY = (y2 + abs(y1)) / 1000;

            x1 += divX * stepX;
            x2 += divX * stepX;

            if (x1 <= 0) {
                x1 = 0;
                x2 = x1 + x3;
            } else if (x2 >= _maxX) {
                x2 = _maxX;
                x1 = x2 - x3;
            }

            y1 = y1 + divY * stepY;
            y2 = y2 + divY * stepY;

            if (y1 <= (_minY * 2)) {
                y1 = _minY * 2;
                y2 = y1 + y3;
            } else if (y2 >= (_maxY * 2)) {
                y2 = _maxY * 2;
                y1 = y2 + y3;
            }

            _graph->axisX()->setRange(x1, x2);
            _graph->axisY()->setRange(y1, y2);

            _startX = event->globalX();
            _startY = event->globalY();
        }

        event->accept();
        QChartView::mouseMoveEvent(event);
    }

    void Display::wheelEvent(QWheelEvent *event) {
        _mouseGrab = false;

        if (event->angleDelta().y() > 0.5) {
            QLogValueAxis *rangeY = static_cast<QLogValueAxis *>(_graph->axisY());

            double maxY = rangeY->max();
            double minY = rangeY->min();

            double step = (maxY + abs(minY)) / 100;

            if (maxY + step <= (_maxY * 2)) {
                if (minY - step >= (_minY * 2)) {
                    _graph->axisY()->setMin(minY - step);
                    _graph->axisY()->setMax(maxY + step);
                } else if (maxY + (step * 2) <= (_maxY * 2)) _graph->axisY()->setMax(maxY + (step * 2));
                    else _graph->axisY()->setMax(_maxY * 2);

                return;
            } else {
                _graph->axisY()->setMax(_maxY * 2);

                if (minY - (step * 2) >= (_minY * 2)) _graph->axisY()->setMin(minY - (step * 2));
                    else _graph->axisY()->setMin(_minY * 2);
            }
        } else  if (event->angleDelta().y() < -0.5) {
            QLogValueAxis *rangeY = static_cast<QLogValueAxis *>(_graph->axisY());

            double maxY = rangeY->max();
            double minY = rangeY->min();

            double step = (maxY + abs(minY)) / 100;

            if (maxY - step >= minY) {
                if (minY + step <= maxY) {
                    _graph->axisY()->setMin(minY + step);
                    _graph->axisY()->setMax(maxY - step);
                } else {
                    _graph->axisY()->setMin((minY + maxY) / 2);
                    _graph->axisY()->setMax((minY + maxY) / 2);
                }

                return;
            }
        }
    } 

    void Display::clear() {
        _graph->removeAllSeries();
    }

    void Display::addGraph(QLineSeries *series) {
        _graph->addSeries(series);

        series->attachAxis(_graph->axisX());
        series->attachAxis(_graph->axisY());
    }

    void Display::createMarker(const double &x) {
        Marker *marker = new Marker(_graph, x);
        _dispalyMarkers << marker;
    }

    void Display::moveMarker(QMouseEvent *event) {
        _dispalyMarkers[0]->setAnchor(event->localPos().x());
        _dispalyMarkers.swapItemsAt(0,1);
    }

    void Display::setMaxX(double max) {
        if (_maxX > max) _graph->axisX()->setMax(max);

        _maxX = max;
    }

    void Display::setMinMaxY(double min, double max) {
        if ((_minY * 2) < min) _graph->axisY()->setMin(min * 2);
        if ((_maxY * 2) > max) _graph->axisY()->setMax(max * 2);

        _minY = min;
        _maxY = max;
    }

    Display::~Display() {
        if (_dispalyMarkers.empty()) {
            for (int i = 0; i < _dispalyMarkers.size(); i++) {
                delete[] _dispalyMarkers[i];
            }
            _dispalyMarkers.clear();
        }
    }
}

