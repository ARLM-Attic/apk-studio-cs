#include "projects.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

Projects::Projects(QWidget *parent) :
    QWidget(parent)
{
    /*
     * @Initialize
     */
    // Toolbar
    this->_toolbar = new QToolBar(this);
    // Tree
    this->_tree = new QTree(this);
    // Menu
    this->_menu = new QMenu(this->_tree);
    // Action
    this->_build = new QAction(icon("build"), text("label_build"), this->_menu);
    this->_close = new QAction(icon("close"), text("label_close"), this->_menu);
    this->_delete = new QAction(icon("delete"), text("label_delete"), this->_toolbar);
    this->_delete_ = new QAction(icon("delete"), text("label_delete"), this->_menu);
    this->_edit = new QAction(icon("edit"), text("label_edit"), this->_menu);
    this->_properties = new QAction(icon("properties"), text("label_properties"), this->_menu);
    this->_properties_ = new QAction(icon("properties"), text("label_properties"), this->_toolbar);
    this->_refresh = new QAction(icon("refresh"), text("label_refresh"), this->_menu);
    this->_refresh_ = new QAction(icon("refresh"), text("label_refresh"), this->_toolbar);
    this->_rename = new QAction(icon("rename"), text("label_rename"), this->_menu);
    this->_rename_ = new QAction(icon("rename"), text("label_rename"), this->_toolbar);
#ifdef Q_OS_WIN
    this->_show = new QAction(icon("show"), text("label_show_windows"), this->_menu);
#else
    this->_show = new QAction(icon("show"), text("label_show_linux"), this->_menu);
#endif
    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    // Model
    this->_model = new QStandardItemModel(this);
    // Title
    QLabel *title = new QLabel(this->_toolbar);
    /*
     * @Prepare
     */
    // Action
    this->_delete->setEnabled(false);
    this->_properties->setEnabled(false);
    this->_refresh->setEnabled(false);
    this->_rename->setEnabled(false);
    // Layout
    layout->setContentsMargins(QMargins(2, 2, 2, 2));
    layout->setSpacing(0);
    // List
    this->_tree->header()->hide();
    this->_tree->setContextMenuPolicy(Qt::CustomContextMenu);
    this->_tree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->_tree->setModel(this->_model);
    this->_tree->setSelectionBehavior(QAbstractItemView::SelectItems);
    this->_tree->setSelectionMode(QAbstractItemView::SingleSelection);
    this->_tree->setSortingEnabled(false);
    // Title
    title->setStyleSheet("color: #333333;");
    title->setText(text("label_projects"));
    title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // Widget
    this->setMinimumSize(QSize(160, 160));
    /*
     * @Bind
     */
    // Action
    this->connect(this->_build, SIGNAL(triggered()), this, SLOT(__build()));
    this->connect(this->_close, SIGNAL(triggered()), this, SLOT(__close()));
    this->connect(this->_delete, SIGNAL(triggered()), this, SLOT(__delete()));
    this->connect(this->_edit, SIGNAL(triggered()), this, SLOT(__edit()));
    this->connect(this->_delete_, SIGNAL(triggered()), this, SLOT(__delete()));
    this->connect(this->_properties, SIGNAL(triggered()), this, SLOT(__properties()));
    this->connect(this->_properties_, SIGNAL(triggered()), this, SLOT(__properties()));
    this->connect(this->_refresh, SIGNAL(triggered()), this, SLOT(__refresh()));
    this->connect(this->_refresh_, SIGNAL(triggered()), this, SLOT(__refresh()));
    this->connect(this->_rename, SIGNAL(triggered()), this, SLOT(__rename()));
    this->connect(this->_rename_, SIGNAL(triggered()), this, SLOT(__rename()));
    this->connect(this->_show, SIGNAL(triggered()), this, SLOT(__show()));
    // Tree
    this->connect(this->_tree, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(__menu(const QPoint &)));
    this->connect(this->_tree, SIGNAL(doubleClick(const QModelIndex &)), this, SLOT(__click(const QModelIndex &)));
    this->connect(this->_tree->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(__select(const QItemSelection &, const QItemSelection &)));
    /*
     * @Inflate
     */
    // Layout
    layout->addWidget(this->_toolbar);
    layout->addWidget(this->_tree);
    // Menu
    this->_menu->addAction(this->_edit);
    this->_menu->addAction(this->_build);
    this->_menu->addSeparator();
    this->_menu->addAction(this->_close);
    this->_menu->addSeparator();
    this->_menu->addAction(this->_show);
    this->_menu->addSeparator();
    this->_menu->addAction(this->_rename_);
    this->_menu->addAction(this->_delete_);
    this->_menu->addSeparator();
    this->_menu->addAction(this->_refresh_);
    this->_menu->addSeparator();
    this->_menu->addAction(this->_properties_);
    // Toolbar
    this->_toolbar->addWidget(title);
    this->_toolbar->addAction(this->_refresh);
    this->_toolbar->addSeparator();
    this->_toolbar->addAction(this->_properties);
    this->_toolbar->addSeparator();
    this->_toolbar->addAction(this->_rename);
    this->_toolbar->addAction(this->_delete);
    // Widget
    this->setLayout(layout);
}

QString Projects::selected()
{
    QModelIndexList selection = this->_tree->selectionModel()->selectedRows(0);
    if (selection.count() != 1)
        return QString();
    QModelIndex selected = selection.last();
    if (!selected.isValid())
        return QString();
    int type = FILE;
    while ((type = qvariant_cast<int>(selected.data(ROLE_TYPE))) != PROJECT)
        selected = selected.parent();
    return qvariant_cast<QString>(selected.data(ROLE_PATH));
}

bool Projects::load(const QString &path)
{
    QFileInfo root(path);
    if (root.exists() && root.isFile() && (root.suffix() == QString("yml"))) {
        QDir directory = root.dir();
        QStandardItem *node = new QStandardItem(icon("project"), directory.dirName());
        node->setData(QVariant(directory.absolutePath()), ROLE_PATH);
        node->setData(QVariant(PROJECT), ROLE_TYPE);
        this->_model->appendRow(node);
        this->refresh(node);
        this->_tree->expand(node->index());
        return true;
    } else
        return false;
}

void Projects::refresh(const QString &path, bool build)
{
    for (int i = 0; i < this->_model->rowCount(); i++) {
        // Refresh
        QModelIndex index = this->_model->index(i, 0, this->_tree->rootIndex());
        if (index.data(ROLE_TYPE).toInt() != PROJECT)
            continue;
        if (index.data(ROLE_PATH).toString() != path)
            continue;
        QStandardItem *node = this->_model->itemFromIndex(index);
        if (!node)
            continue;
        if (build) {
            // Select
            QModelIndexList items = this->_model->match(node->index(), ROLE_PATH, QVariant(QString(path).append("/build")), 1, Qt::MatchRecursive);
            if (items.empty())
                break;
            QStandardItem *item = this->_model->itemFromIndex(items.first());
            if (!item)
                break;
            this->refresh(item);
            break;
        }
        this->refresh(node);
        // Select
        QModelIndexList items = this->_model->match(node->index(), ROLE_PATH, QVariant(QString(path).append("/build/rebuilt.apk")), 1, Qt::MatchRecursive);
        if (items.empty())
            break;
        QStandardItem *item = this->_model->itemFromIndex(items.first());
        if (!item)
            break;
        this->_tree->selectionModel()->select(item->index(), QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
        this->_tree->expand(item->parent()->index());
        break;
    }
}

void Projects::refresh(QStandardItem *node)
{
    while (node->rowCount()) {
        QList<QStandardItem* > children = node->takeRow(0);
        qDeleteAll(children);
    }
    QString path = qvariant_cast<QString>(node->data(ROLE_PATH));
    if (path.isNull() || path.isEmpty())
        return;
    QDir directory(path);
    if (!directory.exists())
        return;
    QFileInfoList list = directory.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::DirsFirst);
    if (list.empty() || (list.count() < 1))
        return;
    QStringList files;
    files << QString("apk");
    files << QString("db");
    files << QString("java");
    files << QString("png");
    files << QString("smali");
    files << QString("txt");
    files << QString("wav");
    files << QString("xml");
    files << QString("yml");
    QStringList directories;
    directories << QString("res");
    foreach (QFileInfo info, list) {
        QStandardItem *child = new QStandardItem();
        if (info.isFile()) {
            child->setData(QVariant(FILE), ROLE_TYPE);
            QString extension = info.suffix();
            if (files.contains(extension))
                child->setIcon(icon(extension.toStdString().c_str()));
            else
                child->setIcon(icon("file"));
            child->setText(info.fileName());
        } else {
            child->setData(QVariant(DIRECTORY), ROLE_TYPE);
            QString directory = info.baseName();
            if (directories.contains(directory))
                child->setIcon(icon(directory.toStdString().c_str()));
            else
                child->setIcon(icon("directory"));
            child->setText(info.baseName());
        }
        child->setData(QVariant(info.absoluteFilePath()), ROLE_PATH);
        node->appendRow(child);
        if (info.isDir())
            this->refresh(child);
    }
}

void Projects::__click(const QModelIndex &index)
{
    if (!index.isValid())
        return;
    QString path = qvariant_cast<QString>(index.data(ROLE_PATH));
    if (path.isNull() || path.isEmpty())
        return;
    QFileInfo file(path);
    if (file.exists() && file.isFile())
        emit edit(file.absoluteFilePath());
}

void Projects::__close()
{
    QModelIndexList selection = this->_tree->selectionModel()->selectedRows(0);
    if (selection.count() != 1)
        return;
    QModelIndex selected = selection.last();
    if (!selected.isValid())
        return;
    int type = qvariant_cast<int>(selected.data(ROLE_TYPE));
    if (type != PROJECT)
        return;
    QString path = qvariant_cast<QString>(selected.data(ROLE_PATH));
    if (path.isNull() || path.isEmpty())
        return;
    QStandardItem *node = this->_model->itemFromIndex(selected);
    if (!node)
        return;
    int result = QMessageBox::question(this, text("title_close"), text("message_close").arg(node->text()), QMessageBox::Yes, QMessageBox::No);
    if (result != QMessageBox::Yes)
        return;
    while (node->rowCount()) {
        QList<QStandardItem* > children = node->takeRow(0);
        qDeleteAll(children);
    }
    this->_model->removeRow(node->row(), this->_tree->rootIndex());
    emit closed(path);
}

void Projects::__edit()
{
    QModelIndexList selection = this->_tree->selectionModel()->selectedRows(0);
    if (selection.count() != 1)
        return;
    QModelIndex selected = selection.last();
    if (!selected.isValid())
        return;
    int type = qvariant_cast<int>(selected.data(ROLE_TYPE));
    if (type != FILE)
        return;
    QString path = qvariant_cast<QString>(selected.data(ROLE_PATH));
    if (path.isNull() || path.isEmpty())
        return;
    if (path.isNull() || path.isEmpty())
        return;
    QFileInfo file(path);
    if (file.exists() && file.isFile())
        emit edit(file.absoluteFilePath());
}

void Projects::__delete()
{
    QModelIndexList selection = this->_tree->selectionModel()->selectedRows(0);
    if (selection.count() != 1)
        return;
    QModelIndex selected = selection.last();
    if (!selected.isValid())
        return;
    int type = qvariant_cast<int>(selected.data(ROLE_TYPE));
    if (type != FILE)
        return;
    QString path = qvariant_cast<QString>(selected.data(ROLE_PATH));
    if (path.isNull() || path.isEmpty())
        return;
    QFileInfo file(path);
    if (!file.exists() || !file.isFile()) {
        emit message(text("not_exists").arg(path));
        return;
    }
    QString detail(file.absoluteFilePath());
    if (detail.length() > 32)
        detail = detail.right(32).prepend("...");
    int result = QMessageBox::question(this, text("title_delete"), text("message_delete").arg(detail), QMessageBox::Yes, QMessageBox::No);
    if (result != QMessageBox::Yes)
        return;
    if (QFile(file.absoluteFilePath()).remove()) {
        QStandardItem *item = this->_model->itemFromIndex(selected);
        QStandardItem *parent = item->parent();
        if (item && parent) {
            this->_model->removeRow(item->row(), parent->index());
            emit deleted(file.absoluteFilePath());
        } else
            emit message(text("failure_delete").arg(path));
    } else
        emit message(text("failure_delete").arg(path));
}

void Projects::__menu(const QPoint &point)
{
    QModelIndex index = this->_tree->indexAt(point);
    if (index.isValid()) {
        this->_build->setEnabled(false);
        this->_close->setEnabled(false);
        this->_delete_->setEnabled(false);
        this->_edit->setEnabled(false);
        this->_properties_->setEnabled(false);
        this->_refresh_->setEnabled(false);
        this->_rename_->setEnabled(false);
        this->_show->setEnabled(false);
        int type = qvariant_cast<int>(index.data(ROLE_TYPE));
        switch (type)
        {
        case DIRECTORY:
            this->_properties_->setEnabled(true);
            this->_refresh_->setEnabled(true);
            this->_show->setEnabled(true);
            break;
        case FILE:
            this->_delete_->setEnabled(true);
            this->_edit->setEnabled(true);
            this->_properties_->setEnabled(true);
            this->_rename_->setEnabled(true);
            this->_show->setEnabled(true);
            break;
        case PROJECT:
            this->_build->setEnabled(true);
            this->_close->setEnabled(true);
            this->_properties_->setEnabled(true);
            this->_refresh_->setEnabled(true);
            break;
        default:
            break;
        }
        this->_menu->exec(this->_tree->mapToGlobal(point));
    }
}

void Projects::__properties()
{
    QModelIndexList selection = this->_tree->selectionModel()->selectedRows(0);
    if (selection.count() != 1)
        return;
    QModelIndex selected = selection.last();
    if (!selected.isValid())
        return;
    QString path = qvariant_cast<QString>(selected.data(ROLE_PATH));
    if (path.isNull() || path.isEmpty())
        return;
#ifdef Q_OS_WIN
    const char *path_ = path.toStdString().c_str();
    const char *verb_ = "properties";
    wchar_t file[4096] = {0};
    wchar_t verb[4096] = {0};
    MultiByteToWideChar(0, 0, path_, strlen(path_), file, strlen(path_));
    MultiByteToWideChar(0, 0, verb_, strlen(verb_), verb, strlen(verb_));
    SHELLEXECUTEINFO ShellExecuteInfo;
    ShellExecuteInfo.cbSize = sizeof(ShellExecuteInfo);
    ShellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_INVOKEIDLIST | SEE_MASK_FLAG_NO_UI;
    ShellExecuteInfo.hwnd = (HWND) this->winId();
    ShellExecuteInfo.lpVerb = verb;
    ShellExecuteInfo.lpFile = file;
    ShellExecuteInfo.lpParameters = NULL;
    ShellExecuteInfo.lpDirectory = NULL;
    ShellExecuteInfo.nShow = SW_SHOW;
    ShellExecuteInfo.hInstApp = 0;
    ShellExecuteInfo.lpIDList = 0;
    ShellExecuteEx(&ShellExecuteInfo);
    Sleep(5);
#else
#endif
}

void Projects::__refresh()
{
    QModelIndexList selection = this->_tree->selectionModel()->selectedRows(0);
    if (selection.count() != 1)
        return;
    QModelIndex selected = selection.last();
    if (!selected.isValid())
        return;
    int type = qvariant_cast<int>(selected.data(ROLE_TYPE));
    if (type == FILE)
        return;
    QStandardItem *item = this->_model->itemFromIndex(selected);
    if (item)
        this->refresh(item);
    else
        emit message(text("failure_refresh"));
}

void Projects::__rename()
{
    QModelIndexList selection = this->_tree->selectionModel()->selectedRows(0);
    if (selection.count() != 1)
        return;
    QModelIndex selected = selection.last();
    if (!selected.isValid())
        return;
    int type = qvariant_cast<int>(selected.data(ROLE_TYPE));
    if (type != FILE)
        return;
    QString path = qvariant_cast<QString>(selected.data(ROLE_PATH));
    if (path.isNull() || path.isEmpty())
        return;
    QFileInfo previous(path);
    if (!previous.exists() || !previous.isFile()) {
        emit message(text("not_exists").arg(path));
        return;
    }
    QString detail(previous.absoluteFilePath());
    if (detail.length() > 32)
        detail = detail.right(32).prepend("...");
    bool ok;
    QString name = QInputDialog::getText(this, text("title_rename"), text("message_rename").arg(detail), QLineEdit::Normal, previous.fileName(), &ok);
    if (ok && !name.isEmpty()) {
        QFileInfo current(previous.absoluteDir().absolutePath().append('/').append(name));
        QFile file(previous.absoluteFilePath());
        if (file.rename(current.absoluteFilePath())) {
            QStandardItem *item = this->_model->itemFromIndex(selected);
            if (item) {
                item->setData(QVariant(current.absoluteFilePath()), ROLE_PATH);
                item->setText(current.fileName());
                emit renamed(current.absoluteFilePath(), previous.absoluteFilePath());
            } else
                emit message(text("failure_rename").arg(path));
        } else
            emit message(text("failure_rename").arg(path));
    }
}

void Projects::__select(const QItemSelection &current, const QItemSelection &/*previous*/)
{
    this->_delete->setEnabled(false);
    this->_properties->setEnabled(false);
    this->_refresh->setEnabled(false);
    this->_rename->setEnabled(false);
    if (current.count() != 1) {
        emit selected(false);
        return;
    }
    int type = qvariant_cast<int>(current.indexes().first().data(ROLE_TYPE));
    switch (type)
    {
    case DIRECTORY:
        this->_refresh->setEnabled(true);
        break;
    case FILE:
        this->_delete->setEnabled(true);
        this->_properties->setEnabled(true);
        this->_rename->setEnabled(true);
        break;
    case PROJECT:
        this->_properties->setEnabled(true);
        this->_refresh->setEnabled(true);
        break;
    default:
        break;
    }
    emit selected(true);
}

void Projects::__show()
{
    QModelIndexList selection = this->_tree->selectionModel()->selectedRows(0);
    if (selection.count() != 1)
        return;
    QModelIndex selected = selection.last();
    if (!selected.isValid())
        return;
    QString path = qvariant_cast<QString>(selected.data(ROLE_PATH));
    if (path.isNull() || path.isEmpty())
        return;
#ifdef Q_OS_WIN
    int type = qvariant_cast<int>(selected.data(ROLE_TYPE));
    QString param;
    if (type == FILE)
        param = QString("/select,");
    param += QDir::toNativeSeparators(path);
    QProcess::startDetached("explorer", QStringList(param));
#else
    QProcess::startDetached("nautilus", QStringList(path));
#endif

}

} // namespace UI
} // namespace APKStudio
} // namespace VPZ
