#include "browser.h"

namespace VPZ {
namespace APKStudio {
namespace Dialog {

void Browser::initialize()
{
    /*
     * @Initialize
     */
    // Layout
    this->_layout = new QVBoxLayout(this);
    // Splitter
    this->_splitter = new QSplitter(this);
    // Toolbar
    this->_statusbar = new QToolBar(this);
    this->_toolbar = new QToolBar(this);
    // Tree
    this->_tree = new QTreeWidget(this);
    // Action
    this->_chmod = new QAction(icon("chmod"), text("label_chmod"), this->_toolbar);
    this->_delete = new QAction(icon("delete"), text("label_delete"), this->_toolbar);
    this->_disable = new QAction(icon("disable"), text("label_disable"), this->_toolbar);
    this->_enable = new QAction(icon("enable"), text("label_enable"), this->_toolbar);
    this->_install = new QAction(icon("install"), text("label_install"), this->_toolbar);
    this->_new = new QAction(icon("new"), text("label_new"), this->_toolbar);
    this->_pull = new QAction(icon("pull"), text("label_pull"), this->_toolbar);
    this->_push = new QAction(icon("push"), text("label_push"), this->_toolbar);
    this->_refresh = new QAction(icon("refresh"), text("label_refresh"), this->_toolbar);
    this->_remount = new QAction(icon("remount"), text("label_remount"), this->_toolbar);
    this->_rename = new QAction(icon("rename"), text("label_rename"), this->_toolbar);
    this->_uninstall = new QAction(icon("uninstall"), text("label_uninstall"), this->_toolbar);
    // Status
    this->_status = new QLabel(this->_statusbar);
    // Progress
    this->_progress = new QProgressBar(this->_statusbar);
    // Tabs
    this->_tabs = new QTabWidget(this->_splitter);
    // Item
    QTreeWidgetItem *bookmarks = new QTreeWidgetItem(this->_tree);
    QTreeWidgetItem *files = new QTreeWidgetItem(this->_tree);
    // ::
    QTreeWidgetItem *application = new QTreeWidgetItem(files);
    QTreeWidgetItem *bluetooth = new QTreeWidgetItem(bookmarks);
    QTreeWidgetItem *camera = new QTreeWidgetItem(bookmarks);
    QTreeWidgetItem *downloads = new QTreeWidgetItem(bookmarks);
    QTreeWidgetItem *external = new QTreeWidgetItem(files);
    QTreeWidgetItem *system = new QTreeWidgetItem(files);
    QTreeWidgetItem *music = new QTreeWidgetItem(bookmarks);
    QTreeWidgetItem *partitions = new QTreeWidgetItem(files);
    QTreeWidgetItem *pictures = new QTreeWidgetItem(bookmarks);
    QTreeWidgetItem *videos = new QTreeWidgetItem(bookmarks);
    /*
     * @Prepare
     */
    // Action
    this->_chmod->setEnabled(false);
    this->_delete->setEnabled(false);
    this->_disable->setEnabled(false);
    this->_enable->setEnabled(false);
    this->_install->setEnabled(false);
    this->_new->setEnabled(false);
    this->_pull->setEnabled(false);
    this->_push->setEnabled(false);
    this->_refresh->setEnabled(false);
    this->_remount->setEnabled(false);
    this->_rename->setEnabled(false);
    this->_uninstall->setEnabled(false);
    // Item
    application->setIcon(0, icon("applications"));
    application->setText(0, text("label_applications"));
    application->setData(0, ROLE_STRUCT, QVariant(APPLICATIONS));
    bookmarks->setIcon(0, icon("bookmarks"));
    bookmarks->setText(0, text("label_bookmarks"));
    bookmarks->setData(0, ROLE_STRUCT, QVariant(-1));
    bluetooth->setIcon(0, icon("bluetooth"));
    bluetooth->setText(0, text("label_bluetooth"));
    bluetooth->setData(0, ROLE_STRUCT, QVariant(BLUETOOTH));
    camera->setIcon(0, icon("camera"));
    camera->setText(0, text("label_camera"));
    camera->setData(0, ROLE_STRUCT, QVariant(CAMERA));
    downloads->setIcon(0, icon("downloads"));
    downloads->setText(0, text("label_downloads"));
    downloads->setData(0, ROLE_STRUCT, QVariant(DOWNLOADS));
    external->setIcon(0, icon("external"));
    external->setText(0, text("label_external"));
    external->setData(0, ROLE_STRUCT, QVariant(EXTERNAL));
    files->setIcon(0, icon("files"));
    files->setText(0, text("label_files"));
    files->setData(0, ROLE_STRUCT, QVariant(-1));
    system->setIcon(0, icon("system"));
    system->setText(0, text("label_system"));
    system->setData(0, ROLE_STRUCT, QVariant(SYSTEM));
    partitions->setIcon(0, icon("partitions"));
    partitions->setText(0, text("label_partitions"));
    partitions->setData(0, ROLE_STRUCT, QVariant(PARTITIONS));
    music->setIcon(0, icon("music"));
    music->setText(0, text("label_music"));
    music->setData(0, ROLE_STRUCT, QVariant(MUSIC));
    pictures->setIcon(0, icon("pictures"));
    pictures->setText(0, text("label_pictures"));
    pictures->setData(0, ROLE_STRUCT, QVariant(PICTURES));
    videos->setIcon(0, icon("videos"));
    videos->setText(0, text("label_videos"));
    videos->setData(0, ROLE_STRUCT, QVariant(VIDEOS));
    // Layout
    this->_layout->setContentsMargins(QMargins(0, 0, 0, 0));
    this->_layout->setSpacing(0);
    // Progress
    this->_progress->setMaximum(100);
    this->_progress->setMaximumHeight(16);
    this->_progress->setMaximumWidth(160);
    this->_progress->setMinimum(0);
    this->_progress->setStyleSheet("margin-left: 4px;");
    this->_progress->setTextVisible(false);
    // Status
    this->_status->setStyleSheet("color: #333333; margin-right: 4px;");
    // Statusbar
    this->_statusbar->setAcceptDrops(false);
    this->_statusbar->setMovable(false);
    // Tabs
    this->_tabs->setTabsClosable(true);
    // Toolbar
    this->_toolbar->setAcceptDrops(false);
    this->_toolbar->setMovable(false);
    // Tree
    this->_tree->header()->hide();
    this->_tree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->_tree->setMaximumWidth(192);
    this->_tree->setMinimumSize(QSize(128, 128));
    this->_tree->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->_tree->setSelectionMode(QAbstractItemView::SingleSelection);
    // Window
    this->resize(QSize(640, 480));
    this->setMinimumSize(QSize(480, 320));
#ifdef Q_OS_WIN
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
#endif
    this->setWindowIcon(icon("window"));
    this->setWindowTitle(text("title_window").arg(this->_device));
    /*
     * @Bind
     */
    // Action
    this->connect(this->_chmod, SIGNAL(triggered()), this, SLOT(__chmod()));
    this->connect(this->_delete, SIGNAL(triggered()), this, SLOT(__delete()));
    this->connect(this->_disable, SIGNAL(triggered()), this, SLOT(__disable()));
    this->connect(this->_enable, SIGNAL(triggered()), this, SLOT(__enable()));
    this->connect(this->_install, SIGNAL(triggered()), this, SLOT(__install()));
    this->connect(this->_new, SIGNAL(triggered()), this, SLOT(__new()));
    this->connect(this->_pull, SIGNAL(triggered()), this, SLOT(__pull()));
    this->connect(this->_push, SIGNAL(triggered()), this, SLOT(__push()));
    this->connect(this->_refresh, SIGNAL(triggered()), this, SLOT(__refresh()));
    this->connect(this->_remount, SIGNAL(triggered()), this, SLOT(__remount()));
    this->connect(this->_rename, SIGNAL(triggered()), this, SLOT(__rename()));
    this->connect(this->_uninstall, SIGNAL(triggered()), this, SLOT(__uninstall()));
    // Tabs
    this->connect(this->_tabs, SIGNAL(currentChanged(const int)), this, SLOT(__current(const int)));
    this->connect(this->_tabs, SIGNAL(tabCloseRequested(const int)), this, SLOT(__close(const int)));
    // Tree
    this->connect(this->_tree, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(__tree(const QModelIndex &)));
    /*
     * Inflate
     */
    // Action
    QList<QAction *> android;
    android << this->_push;
    android << this->_pull;
    QList<QAction *> applications;
    applications << this->_disable;
    applications << this->_enable;
    applications << this->_install;
    applications << this->_uninstall;
    QList<QAction *> file;
    file << this->_new;
    file << this->_rename;
    file << this->_delete;
    QList<QAction *> root;
    root << this->_chmod;
    root << this->_remount;
    // Item
    bookmarks->addChild(bluetooth);
    bookmarks->addChild(camera);
    bookmarks->addChild(downloads);
    bookmarks->addChild(music);
    bookmarks->addChild(pictures);
    bookmarks->addChild(videos);
    files->addChild(application);
    files->addChild(partitions);
    files->addChild(system);
    files->addChild(external);
    // Splitter
    this->_splitter->addWidget(this->_tree);
    this->_splitter->addWidget(this->_tabs);
    this->_splitter->setStretchFactor(0, 2);
    this->_splitter->setStretchFactor(1, 6);
    // Toolbar
    this->_statusbar->addWidget(this->_progress);
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->_statusbar->addWidget(spacer);
    this->_statusbar->addWidget(this->_status);
    this->_toolbar->addAction(this->_refresh);
    this->_toolbar->addSeparator();
    this->_toolbar->addActions(file);
    this->_toolbar->addSeparator();
    this->_toolbar->addActions(applications);
    this->_toolbar->addSeparator();
    this->_toolbar->addActions(android);
    this->_toolbar->addSeparator();
    this->_toolbar->addActions(root);
    // Layout
    this->_layout->addWidget(this->_toolbar);
    this->_layout->addWidget(this->_splitter);
    this->_layout->addWidget(this->_statusbar);
    this->setLayout(this->_layout);
    // Tree
    this->_tree->addTopLevelItem(bookmarks);
    this->_tree->addTopLevelItem(files);
    this->_tree->expandAll();
    // Resize
    this->_statusbar->setMinimumHeight(this->_toolbar->height());
}

UI::Applications *Browser::applications()
{
    // Initialize
    UI::Applications *applications = new UI::Applications(this->_device, this);
    // Bind
    this->connect(applications, SIGNAL(applications(const bool)), this, SLOT(__applications(const bool)));
    this->connect(applications, SIGNAL(message(const QString &)), this, SLOT(__message(const QString &)));
    this->connect(applications, SIGNAL(progress(const int)), this, SLOT(__progress(const int)));
    // Return
    return applications;
}

UI::Files *Browser::files(const QString &path)
{
    // Initialize
    UI::Files *files = new UI::Files(this->_device, path, this);
    // Bind
    this->connect(files, SIGNAL(files(const bool)), this, SLOT(__files(const bool)));
    this->connect(files, SIGNAL(message(const QString &)), this, SLOT(__message(const QString &)));
    this->connect(files, SIGNAL(progress(const int)), this, SLOT(__progress(const int)));
    // Return
    return files;
}

UI::Partitions *Browser::partitions()
{
    // Initialize
    UI::Partitions *partitions = new UI::Partitions(this->_device , this);
    // Bind
    this->connect(partitions, SIGNAL(partitions(const bool)), this, SLOT(__partitions(const bool)));
    this->connect(partitions, SIGNAL(message(const QString &)), this, SLOT(__message(const QString &)));
    this->connect(partitions, SIGNAL(progress(const int)), this, SLOT(__progress(const int)));
    // Return
    return partitions;
}

void Browser::__close(const int index)
{
    this->_tabs->removeTab(index);
}

void Browser::__current(const int index)
{
    this->_chmod->setEnabled(false);
    this->_delete->setEnabled(false);
    this->_disable->setEnabled(false);
    this->_enable->setEnabled(false);
    this->_install->setEnabled(false);
    this->_new->setEnabled(false);
    this->_pull->setEnabled(false);
    this->_push->setEnabled(false);
    this->_refresh->setEnabled(false);
    this->_remount->setEnabled(false);
    this->_rename->setEnabled(false);
    this->_uninstall->setEnabled(false);
    if (index < 0)
        return;
    QObject *pointer = this->_tabs->widget(index);
    UI::Applications *applications = qobject_cast<UI::Applications *>(pointer);
    if (applications != NULL) {
        this->_install->setEnabled(true);
        this->_refresh->setEnabled(true);
        if (applications->selected()) {
            this->_disable->setEnabled(false);
            this->_enable->setEnabled(false);
            this->_pull->setEnabled(true);
            this->_uninstall->setEnabled(false);
        }
        return;
    }
    UI::Files *files = qobject_cast<UI::Files *>(pointer);
    if (files != NULL) {
        this->_new->setEnabled(true);
        this->_push->setEnabled(true);
        this->_refresh->setEnabled(true);
        if (files->selected()) {
            this->_chmod->setEnabled(true);
            this->_delete->setEnabled(true);
            this->_pull->setEnabled(true);
            this->_push->setEnabled(true);
            this->_rename->setEnabled(true);
        }
        return;
    }
    UI::Partitions *partitions = qobject_cast<UI::Partitions *>(pointer);
    if (partitions != NULL) {
        this->_refresh->setEnabled(true);
        if (partitions->selected())
            this->_remount->setEnabled(true);
        return;
    }
}

void Browser::__tree(const QModelIndex &index)
{
    if (!index.isValid())
        return;
    int variant = index.data(ROLE_STRUCT).toInt();
    int tab = -1;
    switch (variant)
    {
    case APPLICATIONS:
    {
        UI::Applications *applications = this->applications();
        tab = this->_tabs->addTab(applications, icon("applications"), text("tab_applications"));
        applications->refresh();
        break;
    }
    case BLUETOOTH:
    {
        QString path("/sdcard/Bluetooth");
        UI::Files *files = this->files(path);
        tab = this->_tabs->addTab(files, icon("files"), text("tab_files"));
        files->refresh();
        break;
    }
    case CAMERA:
    {
        QString path("/sdcard/DCIM");
        UI::Files *files = this->files(path);
        tab = this->_tabs->addTab(files, icon("files"), text("tab_files"));
        files->refresh();
        break;
    }
    case DOWNLOADS:
    {
        QString path("/sdcard/Downloads");
        UI::Files *files = this->files(path);
        tab = this->_tabs->addTab(files, icon("files"), text("tab_files"));
        files->refresh();
        break;
    }
    case EXTERNAL:
    {
        QString path("/sdcard");
        UI::Files *files = this->files(path);
        tab = this->_tabs->addTab(files, icon("files"), text("tab_files"));
        files->refresh();
        break;
    }
    case SYSTEM:
    {
        QString path("/");
        UI::Files *files = this->files(path);
        tab = this->_tabs->addTab(files, icon("files"), text("tab_files"));
        files->refresh();
        break;
    }
    case MUSIC:
    {
        QString path("/sdcard/Music");
        UI::Files *files = this->files(path);
        tab = this->_tabs->addTab(files, icon("files"), text("tab_files"));
        files->refresh();
        break;
    }
    case PARTITIONS:
    {
        UI::Partitions *partitions = this->partitions();
        tab = this->_tabs->addTab(partitions, icon("partitions"), text("tab_partitions"));
        partitions->refresh();
        break;
    }
    case PICTURES:
    {
        QString path("/sdcard/Pictures");
        UI::Files *files = this->files(path);
        tab = this->_tabs->addTab(files, icon("files"), text("tab_files"));
        files->refresh();
        break;
    }
    case VIDEOS:
    {
        QString path("/sdcard/Videos");
        UI::Files *files = this->files(path);
        tab = this->_tabs->addTab(files, icon("files"), text("tab_files"));
        files->refresh();
        break;
    }
    default:
        break;
    }
    if (tab > -1)
        this->_tabs->setCurrentIndex(tab);
}

} // namespace Dialog
} // namespace APKStudio
} // namespace VPZ
