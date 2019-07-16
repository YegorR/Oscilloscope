#ifndef DISPLAY_H
#define DISPLAY_H

#include <QtCharts/QtCharts>
QT_CHARTS_USE_NAMESPACE

namespace oscilloscope {
    class Display : public QChartView {
        Q_OBJECT

    private:
        QChart *_graph;
        QAreaSeries *_zoomArea;

        QLabel *_mouseCord;

        QLineSeries *_target;

        bool _mouseGrab;
        bool _targetMove;
        bool _zoomRect;

        bool _keyShift, _keyCtrl, _keyAlt;

        double _startX, _startY, _endX, _endY;
        double _minX, _maxX, _minY, _maxY;

        void verticalZoom(bool up);
        void horizontalZoom(bool up);
        void zoomRect(double minX, double maxX, double minY, double maxY);

    protected:
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);

        void wheelEvent(QWheelEvent *event);

        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);

    public:
        explicit Display();

        void clear();
        void keysReset();

        void addGraph(QLineSeries *series);
        void deleteGraph(QString name);
        void deleteDublicatesGraph(QString name);

       ~Display();

    };
}

#endif // DISPLAY_H
