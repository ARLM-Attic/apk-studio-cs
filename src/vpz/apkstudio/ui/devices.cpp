#include "devices.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

Devices::Devices(QWidget *parent) :
    QWidget(parent)
{
    /*
     * @Initialize
     */
    // Toolbar
    this->_toolbar = new QToolBar(this);
    // Action
    this->_browser = new QAction(icon("browser"), text("label_browser"), this->_toolbar);
    this->_information = new QAction(icon("information"), text("label_information"), this->_toolbar);
    this->_logcat = new QAction(icon("logcat"), text("label_logcat"), this->_toolbar);
    this->_refresh = new QAction(icon("refresh"), text("label_refresh"), this->_toolbar);
    this->_restart = new QAction(icon("restart"), text("label_restart"), this->_toolbar);
    this->_screenshot = new QAction(icon("screenshot"), text("label_screenshot"), this->_toolbar);
    this->_shell = new QAction(icon("shell"), text("label_shell"), this->_toolbar);
    this->_start = new QAction(icon("start"), text("label_start"), this->_toolbar);
    this->_stop = new QAction(icon("stop"), text("label_stop"), this->_toolbar);
    // Button
    this->_adb = new QToolButton(this);
    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    // Menu
    QMenu *menu = new QMenu(this->_adb);
    // Tree
    this->_tree = new QTreeView(this);
    // Model
    this->_model = new QStandardItemModel(this->_tree);
    // Title
    QLabel *title = new QLabel(this->_toolbar);
    /*
     * @Prepare
     */
    // Action
    this->_browser->setEnabled(false);
    this->_information->setEnabled(false);
    this->_logcat->setEnabled(false);
    this->_screenshot->setEnabled(false);
    this->_shell->setEnabled(false);
    // Layout
    layout->setContentsMargins(QMargins(2, 2, 2, 2));
    layout->setSpacing(0);
    // List
    this->_tree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->_tree->setRootIsDecorated(false);
    this->_tree->setModel(this->_model);
    this->_tree->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->_tree->setSelectionMode(QAbstractItemView::SingleSelection);
    this->_tree->setSortingEnabled(true);
    // Model
    this->_model->setHorizontalHeaderItem(0, new QStandardItem(text("header_id")));
    this->_model->setHorizontalHeaderItem(1, new QStandardItem(text("header_type")));
    // Menu
    menu->addAction(this->_start);
    menu->addSeparator();
    menu->addAction(this->_restart);
    menu->addAction(this->_stop);
    // Button
    this->_adb->setDefaultAction(this->_restart);
    this->_adb->setIcon(icon("adb"));
    this->_adb->setText(text("label_adb"));
    this->_adb->setToolTip(text("tooltip_adb"));
    this->_adb->setMenu(menu);
    this->_adb->setPopupMode(QToolButton::MenuButtonPopup);
    // Title
    title->setStyleSheet("color: #333333;");
    title->setText(text("label_devices"));
    title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // Widget
    this->setMinimumSize(QSize(160, 160));
    /*
     * @Bind
     */
    // Action
    this->connect(this->_browser, SIGNAL(triggered()), this, SLOT(__browser()));
    this->connect(this->_information, SIGNAL(triggered()), this, SLOT(__information()));
    this->connect(this->_logcat, SIGNAL(triggered()), this, SLOT(__logcat()));
    this->connect(this->_refresh, SIGNAL(triggered()), this, SLOT(__refresh()));
    this->connect(this->_restart, SIGNAL(triggered()), this, SLOT(__restart()));
    this->connect(this->_screenshot, SIGNAL(triggered()), this, SLOT(__screenshot()));
    this->connect(this->_shell, SIGNAL(triggered()), this, SLOT(__shell()));
    this->connect(this->_start, SIGNAL(triggered()), this, SLOT(__start()));
    this->connect(this->_stop, SIGNAL(triggered()), this, SLOT(__stop()));
    // List
    this->connect(this->_tree->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(__select(const QItemSelection &, const QItemSelection &)));
    /*
     * @Inflate
     */
    // Layout
    layout->addWidget(this->_toolbar);
    layout->addWidget(this->_tree);
    // Toolbar
    this->_toolbar->addWidget(title);
    this->_toolbar->addWidget(this->_adb);
    this->_toolbar->addAction(this->_refresh);
    this->_toolbar->addSeparator();
    this->_toolbar->addAction(this->_information);
    this->_toolbar->addSeparator();
    this->_toolbar->addAction(this->_browser);
    this->_toolbar->addAction(this->_screenshot);
    this->_toolbar->addAction(this->_logcat);
    this->_toolbar->addAction(this->_shell);
    // Widget
    this->setLayout(layout);
    /*
     * @Assign
     */
    // Register
    qRegisterMetaType<QList<Bridge::Device> >("QList<Bridge::Device>");
}

Bridge::Device Devices::selected()
{
    QModelIndexList selection = this->_tree->selectionModel()->selectedRows(0);
    if (selection.count() != 1)
        return Bridge::Device();
    QModelIndex selected = selection.first();
    return qvariant_cast<Bridge::Device>(selected.data(ROLE_STRUCT));
}

void Devices::__adb()
{
    this->_adb->setEnabled(true);
}

void Devices::__adb(const int command)
{
    this->_adb->setEnabled(false);
    // Prepare
    Runtime::ADB *adb = new Runtime::ADB(command);
    // Bind
    this->connect(adb, SIGNAL(adb(const int)), this, SLOT(__adb()));
    // Execute
    adb->start();
}

void Devices::__browser()
{
    // Check
    QModelIndexList selection = this->_tree->selectionModel()->selectedRows(0);
    if (selection.count() != 1)
        return;
    Bridge::Device device = this->selected();
    if (device.id.isEmpty())
        return;
    if (device.status != Bridge::Device::ONLINE)
        return;
    // Show
    Dialog::Browser *browser = new Dialog::Browser(device.id, this);
    browser->show();
}

void Devices::__information()
{
    // Check
    QModelIndexList selection = this->_tree->selectionModel()->selectedRows(0);
    if (selection.count() != 1)
        return;
    Bridge::Device device = this->selected();
    if (device.id.isEmpty())
        return;
    if (device.status != Bridge::Device::ONLINE)
        return;
    // Show
    Dialog::Information *information = new Dialog::Information(device.id, this);
    information->show();
}

void Devices::__logcat()
{
    // Check
    QModelIndexList selection = this->_tree->selectionModel()->selectedRows(0);
    if (selection.count() != 1)
        return;
    Bridge::Device device = this->selected();
    if (device.id.isEmpty())
        return;
    if (device.status != Bridge::Device::ONLINE)
        return;
    Dialog::Logcat *logcat = new Dialog::Logcat(device.id, this);
    logcat->show();
}

void Devices::__refresh()
{
    // Prepare
    Runtime::Refresh *refresh = new Runtime::Refresh();
    // Bind
    this->connect(refresh, SIGNAL(refresh(const QList<Bridge::Device> &)), this, SLOT(__refresh(const QList<Bridge::Device> &)));
    // Execute
    refresh->start();
}

void Devices::__refresh(const QList<Bridge::Device> &devices)
{
    if (devices.count() < 1)
        return;
    while (this->_model->rowCount() > 0)
        this->_model->removeRow(0);
    foreach (const Bridge::Device &device, devices) {
        // Initialize
        QStandardItem *id = new QStandardItem(device.id);
        QStandardItem *_type = new QStandardItem();
        // Prepare
        switch (device.status) {
        case Bridge::Device::BOOTLOADER:
            id->setIcon(icon("bootloader"));
            id->setToolTip(text("label_bootloader"));
            break;
        case Bridge::Device::ONLINE:
            id->setIcon(icon("online"));
            id->setToolTip(text("label_online"));
            break;
        default:
            id->setIcon(icon("offline"));
            id->setToolTip(text("label_offline"));
            break;
        }
        switch (device.type) {
        case Bridge::Device::DEVICE:
            _type->setText(text("label_phone"));
            break;
        default:
            _type->setText(text("label_emulator"));
            break;
        }
        // Format
        id->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
        QVariant data;
        data.setValue(device);
        id->setData(data, ROLE_STRUCT);
        _type->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
        // Inflate
        QList<QStandardItem *> row;
        row << id;
        row << _type;
        this->_model->appendRow(row);
    }
}

void Devices::__select(const QItemSelection &/*current*/, const QItemSelection &/*previous*/)
{
    this->_browser->setEnabled(false);
    this->_information->setEnabled(false);
    this->_logcat->setEnabled(false);
    this->_screenshot->setEnabled(false);
    this->_shell->setEnabled(false);
    QModelIndexList selection = this->_tree->selectionModel()->selectedRows(0);
    if (selection.count() != 1)
        return;
    Bridge::Device device = this->selected();
    if (device.id.isEmpty())
        return;
    if (device.status != Bridge::Device::ONLINE)
        return;
    this->_browser->setEnabled(true);
    this->_information->setEnabled(true);
    this->_logcat->setEnabled(true);
    this->_screenshot->setEnabled(true);
    this->_shell->setEnabled(true);
}

void Devices::__screenshot()
{
    // Selection
    Bridge::Device device = this->selected();
    if (device.id.isEmpty())
        return;
    if (device.status != Bridge::Device::ONLINE)
        return;
    // Prepare
    Runtime::Screenshot *screenshot = new Runtime::Screenshot(device.id);
    // Bind
    this->connect(screenshot, SIGNAL(screenshot(const QString &)), this, SLOT(__screenshot(const QString &)));
    // Execute
    screenshot->start();
}

void Devices::__screenshot(const QString &path)
{
    if (!path.isEmpty())
        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void Devices::__shell()
{
    Bridge::Device device = this->selected();
    if (device.id.isEmpty())
        return;
    if (device.status != Bridge::Device::ONLINE)
        return;
    QStringList arguments;
    QString command;
#ifdef Q_OS_WIN
    command.append("cmd.exe");
    arguments << QString("/c");
#else
    command.append("xterm");
    arguments << QString("-e");
#endif
    arguments << Utility::Configuration::adb();
    arguments << QString("-s");
    arguments << device.id;
    arguments << QString("shell");
    QProcess::startDetached(command, arguments);
}

} // namespace UI
} // namespace APKStudio
} // namespace VPZ
