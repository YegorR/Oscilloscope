#include "simplescope.h"
#include "ui_simplescope.h"

namespace oscilloscope {
    simplescope::simplescope(QWidget *parent, const QString &name, channelList *globalList) : QWidget(parent) {
        ui = new Ui::simplescope;
        ui->setupUi(this);

        _globalList = globalList;

        _localListView = new localChannelListView(0, _globalList);
        ui->channelsLayout->addWidget(_localListView);

        ui->DisplayName->setText(name);
        setAttribute(Qt::WA_DeleteOnClose, true);
    }

    void simplescope::closeEvent(QCloseEvent *event) {
        event->accept();
    }

    localChannelListView *simplescope::localListView() {
        return _localListView;
    }

    simplescope::~simplescope() {
        delete ui;
    }
}

/// Дублирование канала

void oscilloscope::simplescope::on_DublicateChannel_pressed() {
    //QListWidgetItem item = _localListView->currentItem();
}
