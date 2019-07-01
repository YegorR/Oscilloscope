#include <QDropEvent>
#include <QMimeData>
#include <QDrag>

#include "globalchannellistview.h"
#include "channellist.h"

namespace oscilloscope {
    globalChannelListView::globalChannelListView(QWidget* parent) : QListWidget(parent) {
        this->setSelectionMode(QAbstractItemView::SingleSelection);
        this->setDragEnabled(true);
        this->setDropIndicatorShown(true);
    }

    /// DnD

    void globalChannelListView::startDrag(Qt::DropActions) {
        QListWidgetItem *item = currentItem();
        QMimeData *mimeData = new QMimeData;

        QByteArray channel = item->text().toUtf8();
        mimeData->setText(channel);
        mimeData->setData("application/x-item", channel);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);

        drag->exec(Qt::CopyAction);
    }

    /// Обработка нажатий клаввиш

    void globalChannelListView::keyPressEvent(QKeyEvent *event) {
        if (event->key() == Qt::Key_Backspace) {
            if (this->currentRow() >= 0) {
                if (this->item(currentRow())->foreground() == CH_DEAD) {
                    emit channelDeleted(this->item(currentRow())->text());
                    delete this->takeItem(currentRow());
                }
            }
        }
    }

    globalChannelListView::~globalChannelListView() {}
}
