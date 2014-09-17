#include "settings.h"

namespace VPZ {
namespace APKStudio {
namespace Dialog {

Settings::Settings(QWidget *parent, Qt::WindowFlags flags) :
    QDialog(parent, flags)
{
    /*
     * @Initialize
     */
    this->_buttons = new QDialogButtonBox(this);
    this->_cancel = new QPushButton(text("label_cancel"), this->_buttons);
    this->_save = new QPushButton(text("label_save"), this->_buttons);
    QVBoxLayout *layout = new QVBoxLayout(this);
    /*
     * @Prepare
     */
    this->resize(QSize(480, 320));
    this->setMinimumSize(QSize(480, 320));
    this->setMaximumSize(QSize(640, 480));
#ifdef Q_OS_WIN
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
#endif
    this->setWindowIcon(icon("window"));
    this->setWindowTitle(text("title_window"));
    // Variant
    layout->setContentsMargins(QMargins(4, 4, 4, 4));
    layout->setSpacing(0);
    /*
     * @Bind
     */
    this->connect(this->_cancel, SIGNAL(clicked()), SLOT(__cancel()));
    this->connect(this->_save, SIGNAL(clicked()), SLOT(__save()));
    /*
     * @Inflate
     */
    this->_buttons->addButton(this->_cancel, QDialogButtonBox::RejectRole);
    this->_buttons->addButton(this->_save, QDialogButtonBox::AcceptRole);
    layout->addWidget(this->page());
    layout->addWidget(this->_buttons);
    /*
     * @Assign
     */
    // Button
    QFileInfo binaries(this->_binaries->text());
    this->_save->setEnabled(false);
    if (binaries.exists() && binaries.isDir())
        this->_save->setEnabled(true);
    // Layout
    this->setLayout(layout);
}

QWidget *Settings::page()
{
    /*
     * @Initialize
     */
    // Scoped
    QWidget *widget = new QWidget(this);
    QHBoxLayout *buttons = new QHBoxLayout();
    QPushButton *binaries = new QPushButton(text("label_browse"), widget);
    QFormLayout *layout = new QFormLayout(widget);
    // Button
    this->_add = new QPushButton(text("label_add"), widget);
    this->_remove = new QPushButton(text("label_remove"), widget);
    // Tree
    this->_tree = new QTreeView(widget);
    // Model
    this->_model = new QStandardItemModel(widget);
    // Input
    this->_binaries = new QLineEdit(Utility::Configuration::apkstudio(), widget);
    this->_heap = new QSpinBox(widget);
    this->_root = new QCheckBox(widget);
    this->_text = new QLineEdit(Utility::Configuration::text(), widget);
    this->_verbose = new QCheckBox(widget);
    /*
     * @Prepare
     */
    // Button
    Utility::UI::button(binaries);
    Utility::UI::button(this->_add);
    Utility::UI::button(this->_remove);
    // Tree
    this->_tree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->_tree->setRootIsDecorated(false);
    this->_tree->setModel(this->_model);
    this->_tree->setMaximumHeight(160);
    this->_tree->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->_tree->setSelectionMode(QAbstractItemView::SingleSelection);
    this->_tree->setSortingEnabled(true);
    // Model
    this->_model->setHorizontalHeaderItem(0, new QStandardItem(text("header_id")));
    this->_model->setHorizontalHeaderItem(1, new QStandardItem(text("header_tag")));
    this->_model->setHorizontalHeaderItem(2, new QStandardItem(text("header_time")));
    this->_model->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
    this->_model->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignLeft);
    this->_model->horizontalHeaderItem(2)->setTextAlignment(Qt::AlignCenter);
    // Tree
    this->_tree->setColumnWidth(0, 48);
    this->_tree->setColumnWidth(1, 192);
    // Input
    this->_heap->setMaximum(2048);
    this->_heap->setMinimum(32);
    this->_heap->setValue(Utility::Configuration::heap());
    this->_root->setChecked(Utility::Configuration::root());
    this->_verbose->setChecked(Utility::Configuration::verbose());
    // Button
    this->_remove->setEnabled(false);
    /*
     * @Bind
     */
    // Button
    this->connect(this->_add, SIGNAL(clicked()), this, SLOT(__add()));
    this->connect(binaries, SIGNAL(clicked()), this, SLOT(__browse()));
    this->connect(this->_binaries, SIGNAL(textChanged(const QString &)), this, SLOT(__changed()));
    this->connect(this->_remove, SIGNAL(clicked()), this, SLOT(__remove()));
    // Tree
    this->connect(this->_tree->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(__select(const QItemSelection &, const QItemSelection &)));
    /*
     * @Inflate
     */
    // Button
    buttons->addWidget(this->_add);
    buttons->addWidget(this->_remove);
    // Layout
    layout->addRow(text("label_binaries"), this->_binaries);
    layout->addRow("", binaries);
    layout->addRow(text("label_heap"), this->_heap);
    layout->addRow(text("label_framework"), this->_tree);
    layout->addRow("", buttons);
    layout->addRow(text("label_text"), this->_text);
    layout->addRow(text("label_verbose"), this->_verbose);
    layout->addRow(text("label_root"), this->_root);
    // Widget
    widget->setLayout(layout);
    /*
     * @Assign
     */
    // Widget
    widget->setLayout(layout);
    // Framework
    this->refresh();
    /*
     * @Return
     */
    return widget;
}

void Settings::refresh()
{
    QFileInfo info(Utility::Configuration::framework());
    if (!info.exists() || !info.isDir())
        return;
    // Clear
    while (this->_model->rowCount() > 0)
        this->_model->removeRow(0);
    // Interate
    QDirIterator iterator(info.absoluteFilePath(), QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
        QFileInfo file(iterator.next());
        if (!file.exists() && !file.isFile())
            continue;
        QString name = file.baseName();
        QStringList parts = name.split(QChar('-')).mid(0, 2);
        if (parts.count() != 2)
            continue;
        /*
         * @Initialize
         */
        QStandardItem *id = new QStandardItem(parts.at(0));
        QStandardItem *tag = new QStandardItem(name.section('-', 1));
        QStandardItem *time = new QStandardItem(Utility::Format::time(file.lastModified()));
        /*
         * @Prepare
         */
        id->setData(QVariant(file.absoluteFilePath()), ROLE_PATH);
        id->setData(QVariant(name.section('-', 1)), ROLE_STRUCT);
        id->setData(Qt::AlignLeft, Qt::TextAlignmentRole);
        id->setToolTip(file.absoluteFilePath());
        tag->setData(Qt::AlignLeft, Qt::TextAlignmentRole);
        tag->setToolTip(file.absoluteFilePath());
        time->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
        time->setToolTip(file.absoluteFilePath());
        /*
         * @Inflate
         */
        QList <QStandardItem *> row;
        row << id;
        row << tag;
        row << time;
        this->_model->appendRow(row);
    }
    this->_tree->sortByColumn(2, Qt::DescendingOrder);
}

void Settings::__add()
{
    Add *add = new Add(this);
    add->exec();
    if (add->status())
        this->refresh();
}

void Settings::__browse()
{
    QString path = QFileDialog::getExistingDirectory(this, text("title_binaries"), Settings::path());
    if (path.isNull() || path.isEmpty())
        return;
    this->_binaries->setText(path);
}

void Settings::__cancel()
{
    this->close();
}

void Settings::__changed()
{
    this->_save->setEnabled(false);
    // Binaries
    QFileInfo binaries(this->_binaries->text());
    if (!binaries.exists() || !binaries.isDir())
        return;
    this->_save->setEnabled(true);
}

void Settings::__remove()
{
    QModelIndexList selection = this->_tree->selectionModel()->selectedRows(0);
    if (selection.count() != 1)
        return;
    QModelIndex selected = selection.first();
    QString path = qvariant_cast<QString>(selected.data(ROLE_PATH));
    if (path.isNull() || path.isEmpty())
        return;
    QFileInfo info(path);
    if (info.exists() && info.isFile()) {
        int result = QMessageBox::question(this, text("title_confirm"), text("message_delete").arg(info.absoluteFilePath()));
        if (result == QMessageBox::Yes) {
            QFile::remove(info.absoluteFilePath());
            this->_model->removeRow(selected.row());
        }
    }
}

void Settings::__save()
{
    Utility::Configuration::apkstudio(this->_binaries->text());
    Utility::Configuration::heap(this->_heap->text().toInt());
    Utility::Configuration::root(this->_root->isChecked());
    Utility::Configuration::text(this->_text->text());
    Utility::Configuration::verbose(this->_verbose->isChecked());
    Utility::Configuration::sync();
    this->close();
}

void Settings::__select(const QItemSelection &current, const QItemSelection &/* previous */)
{
    this->_remove->setEnabled(false);
    if (current.count() < 1)
        this->_remove->setEnabled(false);
    else
        this->_remove->setEnabled(true);
}

} // namespace Dialog
} // namespace APKStudio
} // namespace VPZ
