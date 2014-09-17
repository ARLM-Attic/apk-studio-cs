#include "files.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

void Files::initialize()
{
    // Initialize
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setRootIsDecorated(false);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setSelectionMode(QAbstractItemView::MultiSelection);
    this->setSortingEnabled(true);
    this->setUniformRowHeights(true);
    this->sortByColumn(1, Qt::DescendingOrder);
    // Headers
    QStringList labels;
    labels << text("header_name");
    labels << text("header_size");
    labels << text("header_permissions");
    labels << text("header_owner");
    labels << text("header_group");
    labels << text("header_time");
    this->setHeaderLabels(labels);
    this->setColumnWidth(0, 160);
    this->setColumnWidth(1, 96);
    this->setColumnWidth(2, 96);
    this->setColumnWidth(3, 96);
    this->setColumnWidth(4, 96);
    this->setColumnWidth(5, 128);
    // Bind
    this->connect(this->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(__select(const QItemSelection &, const QItemSelection &)));
    this->connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, const int)), this, SLOT(__click(QTreeWidgetItem *, const int)));
    // Assign
    qRegisterMetaType<QList<Bridge::File> >("QList<Bridge::File>");
    qRegisterMetaType<QMap<QString, bool> >("QMap<QString, bool>");
}

void Files::chmod()
{
    // Check
    if (!this->selected())
        return;
    QList<QTreeWidgetItem *> rows = this->selectedItems();
    if (rows.isEmpty())
        return;
    // List
    QStringList files;
    Bridge::File file;
    foreach (QTreeWidgetItem *row, rows) {
        file = qvariant_cast<Bridge::File>(row->data(0, ROLE_STRUCT));
        files.append(file.path);
    }
    // Dialog
    Dialog::Permissions *permissions = new Dialog::Permissions(file, this);
    permissions->exec();
    QString mode = permissions->mode();
    if (mode == QString("NNNN"))
        return;
    // Initialize
    Runtime::CHMOD *chmod = new Runtime::CHMOD(this->_device, files, mode, permissions->recursive());
    // Bind
    this->connect(chmod, SIGNAL(chmod(const QMap<QString, bool> &)), this, SLOT(__chmod(const QMap<QString, bool> &)));
    // Start
    chmod->start();
    // Broadcast
    emit progress(-1);
    emit message(text("start_chmod").arg(files.count()).arg(mode));
}

void Files::delete_()
{
    // Check
    if (!this->selected())
        return;
    QList<QTreeWidgetItem *> rows = this->selectedItems();
    if (rows.isEmpty())
        return;
    // Ask
    int result = QMessageBox::question(this, text("title_delete"), text("message_delete").arg(rows.count()).arg(this->_current), QMessageBox::Yes, QMessageBox::No);
    if (result == QMessageBox::No)
        return;
    // List
    QStringList files;
    Bridge::File file;
    foreach (QTreeWidgetItem *row, rows) {
        file = qvariant_cast<Bridge::File>(row->data(0, ROLE_STRUCT));
        files.append(file.path);
    }
    // Initialize
    Runtime::RM *rm = new Runtime::RM(this->_device, files, true);
    // Bind
    this->connect(rm, SIGNAL(rm(const QMap<QString, bool> &)), this, SLOT(__delete(const QMap<QString, bool> &)));
    // Start
    rm->start();
    // Broadcast
    emit progress(-1);
    emit message(text("start_delete").arg(rows.count()).arg(this->_current));
}

void Files::new_()
{
    // Ask
    bool input = false;
    QString name = QInputDialog::getText(this, text("title_new"), text("label_name"), QLineEdit::Normal, QString(), &input);
    // Verify
    if (!input)
        return;
    if (!QRegularExpression(QString(REGEX_FILENAME)).match(name).hasMatch()) {
        emit message(text("message_new"));
        return;
    }
    QString directory = QString(this->_current).append(name);
    // Disable
    this->setEnabled(false);
    // Initialize
    Runtime::New *new_ = new Runtime::New(this->_device, directory);
    // Bind
    this->connect(new_, SIGNAL(new_(const bool, const QString &)), this, SLOT(__new(const bool, const QString &)));
    // Start
    new_->start();
    // Broadcast
    emit progress(-1);
    emit message(text("start_new").arg(directory));
}

void Files::pull()
{
    // Check
    QList<QTreeWidgetItem *> rows = this->selectedItems();
    if (rows.count() < 1)
        return;
    // Ask
    QString directory = QFileDialog::getExistingDirectory(this, text("title_pull"), Files::path());
    if (directory.isEmpty())
        return;
    // Disable
    this->setEnabled(false);
    // Files
    QStringList files;
    foreach (QTreeWidgetItem *row, rows)
        files.append(qvariant_cast<QString>(row->data(0, ROLE_PATH)));
    // Initialize
    Runtime::Pull *pull = new Runtime::Pull(this->_device, files, directory);
    // Bind
    this->connect(pull, SIGNAL(pull(const QMap<QString, bool> &)), this, SLOT(__pull(const QMap<QString, bool> &)));
    // Start
    pull->start();
    // Broadcast
    emit progress(-1);
    emit message(text("start_pull").arg(files.count()).arg(directory));
}

void Files::push()
{
    // Ask
    QStringList files = QFileDialog::getOpenFileNames(this, text("title_push"), Files::path());
    if (files.count() < 1)
        return;
    // Initialize
    Runtime::Push *push = new Runtime::Push(this->_device, files, this->_current);
    // Bind
    this->connect(push, SIGNAL(push(const QMap<QString, bool> &)), this, SLOT(__push(const QMap<QString, bool> &)));
    // Start
    push->start();
    // Broadcast
    emit progress(-1);
    emit message(text("start_push").arg(files.count()).arg(this->_current));
}

void Files::refresh()
{
    // Disable
    this->setEnabled(false);
    // Initialize
    Runtime::File *file = new Runtime::File(this->_device, this->_current);
    // Bind
    this->connect(file, SIGNAL(file(const QList<Bridge::File> &)), this, SLOT(__file(const QList<Bridge::File> &)));
    // Start
    file->start();
    // Broadcast
    emit progress(-1);
    emit message(text("start_refresh"));
}

void Files::rename()
{
    // Check
    QList<QTreeWidgetItem *> rows = this->selectedItems();
    if (rows.count() != 1)
        return;
    QTreeWidgetItem *row = rows.first();
    if (!row)
        return;
    Bridge::File file = qvariant_cast<Bridge::File>(row->data(0, ROLE_STRUCT));
    if (file.path.isEmpty())
        return;
    // Ask
    bool input = false;
    QString name = QInputDialog::getText(this, text("title_rename"), text("label_rename"), QLineEdit::Normal, file.name, &input);
    // Verify
    if (!input)
        return;
    if (!QRegularExpression(QString(REGEX_FILENAME)).match(name).hasMatch()) {
        emit message(text("message_rename"));
        return;
    }
    QString previous = QString(file.path);
    QString current = QString(this->_current).append(name);
    // Disable
    this->setEnabled(false);
    // Initialize
    Runtime::Rename *rename = new Runtime::Rename(this->_device, previous, current);
    // Bind
    this->connect(rename, SIGNAL(rename(const bool, const QString &)), this, SLOT(__rename(const bool, const QString &)));
    // Start
    rename->start();
    // Broadcast
    emit progress(-1);
    emit message(text("start_rename").arg(previous).arg(current));
}

bool Files::selected()
{
    return (this->selectedItems().count() > 0);
}

void Files::__chmod(const QMap<QString, bool> &map)
{
    // Broadcast
    emit progress(0);
    // Enable
    this->setEnabled(true);
    // Check
    if (map.count() < 1)
        return;
    // Loop
    int failure = 0;
    int success = 0;
    foreach (const QString &key, map.keys()) {
        if (map.value(key))
            success++;
        else
            failure++;
    }
    if (success > 0) {
        this->refresh();
        emit message(text("stop_chmod_success").arg(success).arg(failure));
    } else
        emit message(text("stop_chmod_failed").arg(success).arg(failure));
}

void Files::__click(QTreeWidgetItem *row, const int /*column*/)
{
    if (!row)
        return;
    Bridge::File file = qvariant_cast<Bridge::File>(row->data(0, ROLE_STRUCT));
    if (file.path.isEmpty())
        return;
    if (!((file.type == Bridge::File::DIRECTORY) || (file.type == Bridge::File::SYMLINK_DIRECTORY)))
        return;
    this->_current = QString(file.path);
    if (!this->_current.endsWith('/'))
        this->_current.append('/');
    this->refresh();
}

void Files::__delete(const QMap<QString, bool> &map)
{
    // Broadcast
    emit progress(0);
    // Enable
    this->setEnabled(true);
    // Check
    if (map.count() < 1)
        return;
    // Loop
    int failure = 0;
    int success = 0;
    foreach (const QString &key, map.keys()) {
        if (map.value(key)) {
            success++;
            QList<QTreeWidgetItem *> rows = this->selectedItems();
            if (rows.count() < 1)
                continue;
            foreach (QTreeWidgetItem *row, rows) {
                if (row->data(0, ROLE_PATH).toString() != key)
                    continue;
                delete row;
                break;
            }
        } else
            failure++;
    }
    emit message(text("stop_delete").arg(success).arg(failure));
}

void Files::__file(const QList<Bridge::File> &files)
{
    // Broadcast
    emit progress(0);
    // Enable
    this->setEnabled(true);
    // Clear
    if (this->model()->hasChildren())
        this->model()->removeRows(0, this->model()->rowCount());
    // Up
    QString current = QString(this->_current);
    QString previous;
    if (current.count('/') > 1) {
        QString temporary = current.endsWith('/') ? QString(current).left(current.length() - 1) : QString(current);
        if (temporary.count('/') == 1)
            previous.append('/');
        else
            previous.append(temporary.mid(0, temporary.lastIndexOf('/')));
    } else
        previous.append('/');
    int directories = 0;
    int documents = 0;
    Bridge::File structure;
    structure.type = Bridge::File::DIRECTORY;
    structure.path = previous;
    QTreeWidgetItem *up = new QTreeWidgetItem();
    up->setData(0, ROLE_STRUCT, QVariant::fromValue(structure));
    up->setIcon(0, icon("up"));
    up->setFlags(up->flags() & ~Qt::ItemIsSelectable);
    up->setText(0, QString(".."));
    up->setToolTip(0, text("tooltip_previous"));
    this->addTopLevelItem(up);
    if (files.count() < 1)
        return;
    // Regex
    QRegularExpression access(QString(REGEX_ACCESS));
    QRegularExpression adobe(QString(REGEX_ADOBE));
    QRegularExpression apk(QString(REGEX_APK));
    QRegularExpression audio(QString(REGEX_AUDIO));
    QRegularExpression epub(QString(REGEX_EPUB));
    QRegularExpression excel(QString(REGEX_EXCEL));
    QRegularExpression flash(QString(REGEX_FLASH));
    QRegularExpression image(QString(REGEX_IMAGE));
    QRegularExpression php(QString(REGEX_PHP));
    QRegularExpression photoshop(QString(REGEX_PHOTOSHOP));
    QRegularExpression powerpoint(QString(REGEX_POWERPOINT));
    QRegularExpression video(QString(REGEX_VIDEO));
    QRegularExpression website(QString(REGEX_WEBSITE));
    QRegularExpression word(QString(REGEX_WORD));
    // Loop
    foreach (const Bridge::File &file, files) {
        // Count
        switch (file.type)
        {
        case Bridge::File::DIRECTORY:
        case Bridge::File::SYMLINK_DIRECTORY:
            directories++;
            break;
        default:
            documents++;
            break;
        }
        // Initialize
        QTreeWidgetItem *row = new QTreeWidgetItem();
        // Icon
        switch (file.type)
        {
        case Bridge::File::BLOCK:
            row->setIcon(0, icon("block"));
            break;
        case Bridge::File::CHARACTER:
            row->setIcon(0, icon("character"));
            break;
        case Bridge::File::DIRECTORY:
            row->setIcon(0, icon("directory"));
            break;
        case Bridge::File::FILE:
        {
            QString path = QString(file.path).toLower();
            if (access.match(path).hasMatch())
                row->setIcon(0, icon("access"));
            else if (adobe.match(path).hasMatch())
                row->setIcon(0, icon("adobe"));
            else if (apk.match(path).hasMatch())
                row->setIcon(0, icon("apk"));
            else if (audio.match(path).hasMatch())
                row->setIcon(0, icon("audio"));
            else if (epub.match(path).hasMatch())
                row->setIcon(0, icon("epub"));
            else if (excel.match(path).hasMatch())
                row->setIcon(0, icon("excel"));
            else if (flash.match(path).hasMatch())
                row->setIcon(0, icon("flash"));
            else if (image.match(path).hasMatch())
                row->setIcon(0, icon("image"));
            else if (php.match(path).hasMatch())
                row->setIcon(0, icon("php"));
            else if (photoshop.match(path).hasMatch())
                row->setIcon(0, icon("photoshop"));
            else if (powerpoint.match(path).hasMatch())
                row->setIcon(0, icon("powerpoint"));
            else if (video.match(path).hasMatch())
                row->setIcon(0, icon("video"));
            else if (website.match(path).hasMatch())
                row->setIcon(0, icon("website"));
            else if (word.match(path).hasMatch())
                row->setIcon(0, icon("word"));
            else
                row->setIcon(0, icon("file"));
            break;
        }
        case Bridge::File::PIPE:
            row->setIcon(0, icon("pipe"));
            break;
        case Bridge::File::SOCKET:
            row->setIcon(0, icon("socket"));
            break;
        case Bridge::File::SYMLINK_DIRECTORY:
            row->setIcon(0, icon("directory_symlink"));
            break;
        case Bridge::File::SYMLINK_FILE:
            row->setIcon(0, icon("file_symlink"));
            break;
        case Bridge::File::OTHER:
        case Bridge::File::SYMLINK:
        default:
            row->setIcon(0, icon("unknown"));
            break;
        }
        // Append
        row->setText(0, file.name);
        row->setText(1, Utility::Format::size(file.size));
        row->setText(2, file.permission.display);
        row->setText(3, file.owner);
        row->setText(4, file.group);
        row->setText(5, QString(file.date).append(' ').append(file.time));
        row->setToolTip(0, file.path);
        // Assign
        row->setData(0, ROLE_PATH, QVariant(file.path));
        row->setData(0, ROLE_STRUCT, QVariant::fromValue(file));
        // Insert
        this->addTopLevelItem(row);
    }
    this->sortByColumn(0, Qt::AscendingOrder);
    this->scrollToTop();
    emit message(text("stop_refresh").arg(directories).arg(documents));
}

void Files::__new(const bool success, const QString &path)
{
    // Broadcast
    emit progress(0);
    // Enable
    this->setEnabled(true);
    // Parse
    if (success) {
        this->refresh();
        emit message(text("stop_new_success").arg(path));
    } else
        emit message(text("stop_new_failed").arg(path));
}

void Files::__pull(const QMap<QString, bool> &map)
{
    // Broadcast
    emit progress(0);
    // Enable
    this->setEnabled(true);
    // Check
    if (map.count() < 1)
        return;
    // Loop
    int failure = 0;
    int success = 0;
    foreach (const QString &key, map.keys()) {
        if (map.value(key))
            success++;
        else
            failure++;
    }
    emit message(text("stop_pull").arg(success).arg(failure));
}

void Files::__push(const QMap<QString, bool> &map)
{
    // Broadcast
    emit progress(0);
    // Enable
    this->setEnabled(true);
    // Check
    if (map.count() < 1)
        return;
    // Loop
    int failure = 0;
    int success = 0;
    foreach (const QString &key, map.keys()) {
        if (map.value(key))
            success++;
        else
            failure++;
    }
    if (success > 0) {
        this->refresh();
        emit message(text("stop_push_success").arg(success).arg(failure));
    } else
        emit message(text("stop_push_failed").arg(success).arg(failure));
}

void Files::__rename(const bool success, const QString &path)
{
    // Broadcast
    emit progress(0);
    // Enable
    this->setEnabled(true);
    // Parse
    if (success) {
        this->refresh();
        emit message(text("stop_rename_success").arg(path));
    } else
        emit message(text("stop_rename_failed").arg(path));
}

void Files::__select(const QItemSelection &/*current*/, const QItemSelection &/*previous*/)
{
    if (this->selected())
        emit files(true);
    else
        emit files(false);
}

} // namespace UI
} // namespace APKStudio
} // namespace VPZ
