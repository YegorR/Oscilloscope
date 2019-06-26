#include <QMainWindow>
#include <QList>
#include "simplescope.h"

namespace Ui {
    class MainWindow;
}

namespace oscilloscope {
    class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);     

        ~MainWindow();

    private slots:
        void on_createSimpleScope_pressed();
        void updateScopes();

    private:
        Ui::MainWindow *ui;
        QList<simplescope *> _scopes;

        int countScopes;
    };
}


