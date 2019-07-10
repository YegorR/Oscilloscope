#include "display.h"

#include <QDebug>

namespace oscilloscope {
    Display::Display() : QChartView() {
        _graph = new QChart();
        _graph->legend()->hide();

        this->setChart(_graph);
        this->setRenderHint(QPainter::Antialiasing);

        QValueAxis *xAxis = new QValueAxis();
        xAxis->setRange(0, 100);

        QValueAxis *yAxis = new QValueAxis();
        yAxis->setRange(-10, 10);

        _graph->addAxis(xAxis, Qt::AlignBottom);
        _graph->addAxis(yAxis, Qt::AlignLeft);

        _mouseGrab = false;

        _maxX = 100;

        _minY = -10;
        _maxY = 10;

        this->setStyleSheet("background-color: rgb(64, 64, 64)");
    }

    void Display::mousePressEvent(QMouseEvent *event) {
        _startX = event->globalX();
        _startY = event->globalY();

        _mouseGrab = true;

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

    Display::~Display() {}
}

