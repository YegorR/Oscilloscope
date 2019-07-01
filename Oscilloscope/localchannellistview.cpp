#include <QDropEvent>
#include <QMimeData>
#include <QDrag>

#include <QCheckBox>
#include <QListWidgetItem>

#include <QDebug>

#include "localchannellistview.h"

namespace oscilloscope {
    localChannelListView::localChannelListView(QWidget* parent, channelList *globalList) : QListWidget(parent) {
        setFixedWidth(150);

        setSelectionMode(QAbstractItemView::SingleSelection);
        setDropIndicatorShown(true);
        setAcceptDrops(true);

        setStyleSheet("color: Black");

        _globalList = globalList;
    }

    /// DnD

    void localChannelListView::dragMoveEvent(QDragMoveEvent* event) {
        if (event->mimeData()->hasFormat("application/x-item") && event->source() != this) event->accept();
            else event->ignore();
    }

    void localChannelListView::dropEvent(QDropEvent* event) {
        if (event->mimeData()->hasFormat("application/x-item")) {
            event->accept();

            QString name = event->mimeData()->data("application/x-item");

            /*QWidget *widget;
            QLayout *layout;
            QLayoutItem *item;
            QLabel *label;

            for (int i = 0; i < count(); i++) {
                widget = this->itemWidget(this->item(i));
                layout = itm->layout();
                item = _layout->itemAt(1);
                label = dynamic_cast<QLabel *>(_item->widget());

                if (label->text() == name) {
                    exists = true;
                    break;
                }
            }*/

            if (_names.indexOf(name) < 0) {
                _names.append(name);

                QCheckBox *channel = new QCheckBox(name);
                QListWidgetItem *item = new QListWidgetItem(this);

                setItemWidget(item, channel);
            }
        } else event->ignore();
    }

    void localChannelListView::dragEnterEvent(QDragEnterEvent* event) {
        if (event->mimeData()->hasFormat("application/x-item")) event->accept();
            else event->ignore();
    }

    /// Удаление канала

    void localChannelListView::deleteChannel(const QString name) {
        int index = _names.indexOf(name);

        delete this->takeItem(index);
        _names.removeAt(index);

    }

    localChannelListView::~localChannelListView() {}
}
