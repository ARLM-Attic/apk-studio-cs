#include "project.h"

namespace VPZ {
namespace APKStudio {
namespace Dialog {

Project::Project(QWidget *parent) :
    QDialog(parent)
{
    /*
     * @Initialize
     */
    // Buttons
    this->_buttons = new QDialogButtonBox(this);
    // Button
    this->_cancel = new QPushButton(text("label_cancel"), this->_buttons);
    this->_create = new QPushButton(text("label_create"), this->_buttons);
    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    /*
     * @Prepare
     */
    // Button
    this->_create->setEnabled(false);
    // Window
    this->resize(QSize(550, 390));
    this->setMinimumSize(QSize(480, 320));
    this->setMaximumSize(QSize(640, 480));
#ifdef Q_OS_WIN
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
#endif
    this->setWindowIcon(icon("window"));
    this->setWindowTitle(text("title_window"));
    /*
     * @Bind
     */
    // Button
    this->connect(this->_cancel, SIGNAL(clicked()), SLOT(reject()));
    this->connect(this->_create, SIGNAL(clicked()), SLOT(accept()));
    /*
     * @Inflate
     */
    // Button
    this->_buttons->addButton(this->_cancel, QDialogButtonBox::RejectRole);
    this->_buttons->addButton(this->_create, QDialogButtonBox::AcceptRole);
    // Layout
    layout->addWidget(this->page());
    layout->addWidget(this->_buttons);
    /*
     * @Assign
     */
    this->setLayout(layout);
    // Tree
    this->refresh();
}

void Project::browse(int type)
{
    QString file;
    QString title;
    switch (type)
    {
    case APK_:
        title.append(text("title_apk"));
        file.append("Android Binary (*.apk)");
        break;
    case LOCATION:
        title.append(text("title_location"));
        break;
    default:
        break;
    }
    QString path;
    if (file.isNull() || file.isEmpty())
        path = QFileDialog::getExistingDirectory(this, title, Project::path());
    else
        path = QFileDialog::getOpenFileName(this, title, Project::path(), file, 0, 0);
    if (path.isNull() || path.isEmpty())
        return;
    switch (type)
    {
    case APK_:
        this->_apk->setText(path);
        break;
    case LOCATION:
        this->_location->setText(path);
        break;
    default:
        break;
    }
}

QString Project::framework()
{
    QString framework;
    QModelIndexList selection = this->_tree->selectionModel()->selectedRows(0);
    if (selection.count() == 1) {
        QModelIndex selected = selection.first();
        QString tag = selected.data(ROLE_STRUCT).toString();
        if (!tag.isEmpty())
            framework = tag;
    }
    return framework;
}

QWidget *Project::page()
{
    /*
     * @Initialize
     */
    QWidget *page = new QWidget(this);
    // Scoped
    QFormLayout *layout = new QFormLayout(page);
    /*
     * @Initialize
     */
    // Scoped
    QPushButton *apk = new QPushButton(text("label_browse"), page);
    QPushButton *location = new QPushButton(text("label_browse"), page);
    // Tree
    this->_tree = new QTreeView(page);
    // Model
    this->_model = new QStandardItemModel(page);
    // Private
    this->_apk = new QLineEdit(page);
    this->_name = new QLineEdit(page);
    this->_location = new QLineEdit(page);
    /*
     * @Prepare
     */
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
    // Button
    Utility::UI::button(apk);
    Utility::UI::button(location);
    /*
     * @Bind
     */
    this->connect(apk, SIGNAL(clicked()), this, SLOT(__apk()));
    this->connect(this->_apk, SIGNAL(textChanged(const QString &)), this, SLOT(__changed()));
    this->connect(location, SIGNAL(clicked()), this, SLOT(__location()));
    this->connect(this->_location, SIGNAL(textChanged(const QString &)), this, SLOT(__changed()));
    this->connect(this->_name, SIGNAL(textChanged(const QString &)), this, SLOT(__changed()));
    /*
     * @Inflate
     */
    layout->addRow(text("label_name"), this->_name);
    layout->addRow(text("label_apk"), this->_apk);
    layout->addRow("", apk);
    layout->addRow(text("label_location"), this->_location);
    layout->addRow("", location);
    layout->addRow(text("label_framework"), this->_tree);
    /*
     * @Assign
     */
    page->setLayout(layout);
    /*
     * @Return
     */
    return page;
}

void Project::refresh()
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

void Project::__changed()
{
    this->_create->setEnabled(false);
    // Name
    QRegularExpression name(QString(REGEX_PROJECT));
    if (!name.match(this->_name->text()).hasMatch())
        return;
    // APK
    QFileInfo apk(this->_apk->text());
    if (!apk.exists() || !apk.isFile() || (apk.suffix() != QString("apk")))
        return;
    // Location
    QFileInfo location(this->_location->text());
    if (!location.exists() || !location.isDir())
        return;
    this->_create->setEnabled(true);
}

} // namespace Wizard
} // namespace APKStudio
} // namespace VPZ
