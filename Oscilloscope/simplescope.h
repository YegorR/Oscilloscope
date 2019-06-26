#include <QWidget>

namespace Ui {
    class simplescope;
}

namespace oscilloscope {
    class simplescope : public QWidget {
        Q_OBJECT

    public:
        explicit simplescope(QWidget *parent = 0, const QString &name = "Неопределенный дисплей");

        ~simplescope();

    private:
        Ui::simplescope *ui;

        void closeEvent(QCloseEvent *event);
    };
}
