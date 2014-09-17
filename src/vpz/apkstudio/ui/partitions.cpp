#include "partitions.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

void Partitions::initialize()
{
    // Initialize
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setRootIsDecorated(false);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setSortingEnabled(true);
    this->setUniformRowHeights(true);
    // Headers
    QStringList labels;
    labels << text("header_partition");
    labels << text("header_device");
    labels << text("header_fs");
    labels << text("header_flags");
    this->setHeaderLabels(labels);
    this->setColumnWidth(0, 128);
    this->setColumnWidth(1, 160);
    this->setColumnWidth(2, 96);
    // Bind
    this->connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)), this, SLOT(__select(QTreeWidgetItem *, QTreeWidgetItem *)));
    // Assign
    qRegisterMetaType<Bridge::Partition >("Bridge::Partition");
    qRegisterMetaType<QList<Bridge::Partition> >("QList<Bridge::Partition>");
}

void Partitions::refresh()
{
    // Disable
    this->setEnabled(false);
    // Initialize
    Runtime::Partition *partition = new Runtime::Partition(this->_device);
    // Bind
    this->connect(partition, SIGNAL(partition(const QList<Bridge::Partition> &)), this, SLOT(__partition(const QList<Bridge::Partition> &)));
    // Start
    partition->start();
    // Broadcast
    emit progress(-1);
    emit message(text("start_refresh"));
}

void Partitions::remount()
{
    if (!this->selected())
        return;
    QTreeWidgetItem *row = this->selectedItems().first();
    Bridge::Partition partition = qvariant_cast<Bridge::Partition>(row->data(0, ROLE_STRUCT));
    bool rw = partition.flags.contains(QString("rw"));
    // Ask
    QString detail = text("message_remount").arg(partition.mount).arg(rw ? text("text_ro") : text("text_rw"));
    int result = QMessageBox::question(this, text("title_remount"), detail, QMessageBox::Yes, QMessageBox::Cancel);
    if (result == QMessageBox::Cancel)
        return;
    // Disable
    this->setEnabled(false);
    // Initialize
    Runtime::Remount *remount = new Runtime::Remount(this->_device, partition);
    // Bind
    this->connect(remount, SIGNAL(remount(const bool, const bool, const Bridge::Partition &)), this, SLOT(__remount(const bool, const bool, const Bridge::Partition &)));
    // Start
    remount->start();
    // Broadcast
    emit progress(-1);
    QString mode = (rw ? text("text_ro") : text("text_rw"));
    emit message(text("start_remount").arg(partition.mount).arg(mode));
}

bool Partitions::selected()
{
    return (this->selectedItems().count() > 0);
}

void Partitions::__partition(const QList<Bridge::Partition> &partitions)
{
    // Broadcast
    emit progress(0);
    // Disable
    this->setEnabled(true);
    // Clear
    if (this->model()->hasChildren())
        this->model()->removeRows(0, this->model()->rowCount());
    if (partitions.count() < 1)
        return;
    foreach (const Bridge::Partition &partition, partitions) {
        // Initialize
        QTreeWidgetItem *row = new QTreeWidgetItem();
        // Append
        if (partition.flags.contains(QString("rw")))
            row->setIcon(0, icon("rw"));
        else
            row->setIcon(0, icon("ro"));
        QString flags = partition.flags.join(',');
        row->setText(0, partition.mount);
        row->setText(1, partition.device);
        row->setText(2, partition.fs);
        row->setText(3, flags);
        row->setToolTip(0, partition.flags.contains(QString("rw")) ? text("text_rw") : text("text_ro"));
        row->setToolTip(3, flags);
        // Assign
        row->setData(0, ROLE_STRUCT, QVariant::fromValue(partition));
        // Insert
        this->addTopLevelItem(row);
    }
    this->sortByColumn(0, Qt::AscendingOrder);
    this->scrollToTop();
    // Broadcast
    emit message(text("stop_refresh").arg(partitions.count()));
}

void Partitions::__remount(const bool success, const bool rw, const Bridge::Partition &partition)
{
    // Broadcast
    emit progress(0);
    // Enable
    this->setEnabled(true);
    // Check
    if (success) {
        this->refresh();
        // Broadcast
        QString mode = (rw ? text("text_ro") : text("text_rw"));
        emit message(text("stop_success").arg(partition.mount).arg(mode));
    } else {
        // Broadcast
        QString mode = (rw ? text("text_ro") : text("text_rw"));
        emit message(text("stop_failure").arg(partition.mount).arg(mode));
    }
}

void Partitions::__select(QTreeWidgetItem *current, QTreeWidgetItem */*previous*/)
{
    if (!current)
        emit partitions(false);
    else
        emit partitions(true);
}

} // namespace UI
} // namespace APKStudio
} // namespace VPZ
