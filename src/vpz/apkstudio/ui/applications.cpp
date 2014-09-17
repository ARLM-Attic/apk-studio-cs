#include "applications.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

void Applications::initialize()
{
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setRootIsDecorated(false);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setSortingEnabled(true);
    this->setUniformRowHeights(true);
    // Headers
    QStringList labels;
    labels << text("header_package");
    labels << text("header_type");
    labels << text("header_size");
    labels << text("header_time");
    this->setHeaderLabels(labels);
    this->setColumnWidth(0, 160);
    this->setColumnWidth(1, 96);
    this->setColumnWidth(2, 96);
    this->setColumnWidth(3, 128);
    // Bind
    this->connect(this->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(__select(const QItemSelection &, const QItemSelection &)));
    // Assign
    qRegisterMetaType<QList<Bridge::Application> >("QList<Bridge::Application>");
    qRegisterMetaType<QMap<QString, bool> >("QMap<QString, bool>");
}

void Applications::install()
{
    // Ask
    QStringList files = QFileDialog::getOpenFileNames(this, text("title_install"), Applications::path(), QString("Android Binary (*.apk)"));
    if (files.count() < 1)
        return;
    // Disable
    this->setEnabled(false);
    // Initialize
    Runtime::Install *install = new Runtime::Install(this->_device, files);
    // Bind
    this->connect(install, SIGNAL(install(const QMap<QString, bool> &)), this, SLOT(__install(const QMap<QString, bool> &)));
    // Start
    install->start();
    // Broadcast
    emit progress(-1);
    emit message(text("start_install").arg(files.count()));
}

void Applications::pull()
{
    // Check
    QList<QTreeWidgetItem *> rows = this->selectedItems();
    if (rows.count() < 1)
        return;
    // Ask
    QString directory = QFileDialog::getExistingDirectory(this, text("title_pull"), Applications::path());
    if (directory.isEmpty())
        return;
    // Disable
    this->setEnabled(false);
    // Files
    QStringList files;
    foreach (QTreeWidgetItem *row, rows)
        files.append(row->data(0, ROLE_PATH).toString());
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

void Applications::state(const bool enable)
{
    // Check
    if (!this->selected())
        return;
    QTreeWidgetItem *row = this->selectedItems().first();
    if (!row)
        return;
    Bridge::Application application = qvariant_cast<Bridge::Application>(row->data(0, ROLE_STRUCT));
    if (application.package.isEmpty())
        return;
    if (application.state == enable)
        return;
    // Disable
    this->setEnabled(false);
    // Initialize
    Runtime::State *state = new Runtime::State(this->_device, application.package, enable);
    // Bind
    this->connect(state, SIGNAL(state(const bool, const QString &, const bool)), this, SLOT(__state(const bool, const QString &, const bool)));
    // Start
    state->start();
    // Broadcast
    emit progress(-1);
    emit message(text(enable ? "start_enable" : "start_disable").arg(application.package));
}

void Applications::refresh()
{
    // Disable
    this->setEnabled(false);
    // Initialize
    Runtime::Package *package = new Runtime::Package(this->_device);
    // Bind
    this->connect(package, SIGNAL(package(const QList<Bridge::Application> &)), this, SLOT(__package(const QList<Bridge::Application> &)));
    // Start
    package->start();
    // Broadcast
    emit progress(-1);
    emit message(text("start_refresh"));
}

bool Applications::selected()
{
    return (this->selectedItems().count() > 0);
}

void Applications::uninstall()
{
    // Check
    if (!this->selected())
        return;
    QTreeWidgetItem *row = this->selectedItems().first();
    if (!row)
        return;
    Bridge::Application application = qvariant_cast<Bridge::Application>(row->data(0, ROLE_STRUCT));
    if (application.package.isEmpty())
        return;
    // Confirm
    int result = QMessageBox::question(this, text("title_uninstall"), text("message_uninstall").arg(application.package), QMessageBox::Yes, QMessageBox::Cancel);
    if (result == QMessageBox::Cancel)
        return;
    // Disable
    this->setEnabled(false);
    // Initialize
    Runtime::Uninstall *uninstall = new Runtime::Uninstall(this->_device, application.package);
    // Bind
    this->connect(uninstall, SIGNAL(uninstall(const bool, const QString &)), this, SLOT(__uninstall(const bool, const QString &)));
    // Start
    uninstall->start();
    // Broadcast
    emit progress(-1);
    emit message(text("start_uninstall").arg(application.package));
}

void Applications::__install(const QMap<QString, bool> &map)
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
    // Refresh
    if (success > 0) {
        this->refresh();
        // Broadcast
        emit message(text("stop_install_success").arg(success).arg(failure));
    } else
        // Broadcast
        emit message(text("stop_install_failure").arg(success).arg(failure));
}

void Applications::__package(const QList<Bridge::Application> &packages)
{
    // Broadcast
    emit progress(0);
    // Enable
    this->setEnabled(true);
    // Clear
    if (this->model()->hasChildren())
        this->model()->removeRows(0, this->model()->rowCount());
    if (packages.count() < 1)
        return;
    foreach (const Bridge::Application &package, packages) {
        // Initialize
        QTreeWidgetItem *row = new QTreeWidgetItem();
        // Append
        row->setIcon(0, icon(package.state ? "enabled" : "disabled"));
        row->setText(0, package.package);
        row->setText(1, (package.type == Bridge::Application::SYSTEM)? QString("System") : QString("User"));
        row->setText(2, Utility::Format::size(package.file.size));
        row->setText(3, QString(package.file.date).append(' ').append(package.file.time));
        row->setToolTip(0, package.state ? text("tooltip_enabled") : text("tooltip_disabled"));
        row->setToolTip(1, package.file.path);
        // Assign
        row->setData(0, ROLE_PATH, package.file.path);
        row->setData(0, ROLE_STRUCT, QVariant::fromValue(package));
        // Insert
        this->addTopLevelItem(row);
    }
    this->sortByColumn(3, Qt::DescendingOrder);
    this->scrollToTop();
    // Broadcast
    emit message(text("stop_refresh").arg(packages.count()));
}

void Applications::__pull(const QMap<QString, bool> &map)
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
    // Broadcast
    emit message(text("stop_pull").arg(success).arg(failure));
}

void Applications::__select(const QItemSelection &/*current*/, const QItemSelection &/*previous*/)
{
    if (this->selected())
        emit applications(true);
    else
        emit applications(false);
}

void Applications::__state(const bool success, const QString &package, const bool state)
{
    // Broadcast
    emit progress(0);
    // Enable
    this->setEnabled(true);
    if (!success) {
        emit message(text("stop_state").arg(package));
        return;
    }
    QList<QTreeWidgetItem *> rows = this->findItems(package, Qt::MatchExactly);
    if (rows.count() != 1)
        return;
    QTreeWidgetItem *row = rows.first();
    if (!row)
        return;
    Bridge::Application application = qvariant_cast<Bridge::Application>(row->data(0, ROLE_STRUCT));
    if (application.package.isEmpty())
        return;
    application.state = state;
    row->setData(0, ROLE_STRUCT, QVariant::fromValue(application));
    row->setIcon(0, icon(state ? "enabled" : "disabled"));
    row->setToolTip(0, state ? text("tooltip_enabled") : text("tooltip_disabled"));
    // Broadcast
    if (state)
        emit message(text("stop_enable").arg(package));
    else
        emit message(text("stop_disable").arg(package));
}

void Applications::__uninstall(const bool success, const QString &package)
{
    // Broadcast
    emit progress(0);
    // Enable
    this->setEnabled(true);
    if (!success) {
        emit message(text("stop_uninstall_failure").arg(package));
        return;
    }
    QList<QTreeWidgetItem *> rows = this->findItems(package, Qt::MatchExactly);
    if (rows.count() != 1)
        return;
    QTreeWidgetItem *row = rows.first();
    if (!row)
        return;
    delete row;
    // Broadcast
    emit message(text("stop_uninstall_success").arg(package));
}

} // namespace UI
} // namespace APKStudio
} // namespace VPZ
