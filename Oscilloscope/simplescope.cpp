#include "simplescope.h"
#include "ui_simplescope.h"

namespace oscilloscope {
    simplescope::simplescope(QWidget *parent, const QString &name) : QWidget(parent) {
        ui = new Ui::simplescope;
        ui->setupUi(this);

        ui->DisplayName->setText(name);
        setAttribute(Qt::WA_DeleteOnClose, true);
    }

    void simplescope::closeEvent(QCloseEvent *event) {
        event->accept();
    }

    simplescope::~simplescope() {
        delete ui;
    }
}
