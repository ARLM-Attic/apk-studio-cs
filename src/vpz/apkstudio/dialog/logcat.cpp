#include "logcat.h"

namespace VPZ {
namespace APKStudio {
namespace Dialog {

void Logcat::closeEvent(QCloseEvent *event)
{
    this->__stop();
    QDialog::closeEvent(event);
}

void Logcat::initialize()
{
    /*
     * @Initialize
     */
    // Toolbar
    this->_toolbar = new QToolBar(this);
    // Tree
    this->_tree = new QTreeWidget(this);
    // Menu
    this->_menu = new QMenu(this->_tree);
    // Action
    this->_clear = new QAction(icon("clear"), text("label_clear"), this->_toolbar);
    this->_copy = new QAction(icon("copy"), text("label_copy"), this->_menu);
    this->_debug = new QAction(icon("debug"), text("label_debug"), this->_toolbar);
    this->_error = new QAction(icon("error"), text("label_error"), this->_toolbar);
    this->_info = new QAction(icon("info"), text("label_info"), this->_toolbar);
    this->_load = new QAction(icon("load"), text("label_load"), this->_toolbar);
    this->_remove = new QAction(icon("remove"), text("label_remove"), this->_menu);
    this->_save = new QAction(icon("save"), text("label_save"), this->_toolbar);
    this->_scroll = new QAction(icon("scroll"), text("label_scroll"), this->_toolbar);
    this->_start = new QAction(icon("start"), text("label_start"), this->_toolbar);
    this->_stop = new QAction(icon("stop"), text("label_stop"), this->_toolbar);
    this->_verbose = new QAction(icon("verbose"), text("label_verbose"), this->_toolbar);
    this->_warning = new QAction(icon("warning"), text("label_warning"), this->_toolbar);
    // Layout
    this->_layout = new QVBoxLayout(this);
    // Logger
    this->_logger = 0;
    // Timer
    QTimer *timer = new QTimer(this);
    /*
     * @Prepare
     */
    // Action
    this->_debug->setCheckable(true);
    this->_debug->setChecked(true);
    this->_error->setCheckable(true);
    this->_error->setChecked(true);
    this->_info->setCheckable(true);
    this->_info->setChecked(true);
    this->_scroll->setCheckable(true);
    this->_scroll->setChecked(true);
    this->_stop->setEnabled(false);
    this->_verbose->setCheckable(true);
    this->_verbose->setChecked(true);
    this->_warning->setCheckable(true);
    this->_warning->setChecked(true);
    // Layout
    this->_layout->setContentsMargins(0, 0, 0, 0);
    this->_layout->setSpacing(0);
    // Toolbar
    this->_toolbar->setAcceptDrops(false);
    this->_toolbar->setMovable(false);
    // Tree
    this->_tree->setContextMenuPolicy(Qt::CustomContextMenu);
    this->_tree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->_tree->setRootIsDecorated(false);
    this->_tree->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->_tree->setSelectionMode(QAbstractItemView::MultiSelection);
    this->_tree->setSortingEnabled(true);
    this->_tree->setUniformRowHeights(true);
    this->_tree->sortByColumn(1, Qt::DescendingOrder);
    /*
     * @Bind
     */
    // Action
    this->connect(this->_clear, SIGNAL(triggered()), this, SLOT(__clear()));
    this->connect(this->_copy, SIGNAL(triggered()), this, SLOT(__copy()));
    this->connect(this->_load, SIGNAL(triggered()), this, SLOT(__load()));
    this->connect(this->_remove, SIGNAL(triggered()), this, SLOT(__remove()));
    this->connect(this->_save, SIGNAL(triggered()), this, SLOT(__save()));
    this->connect(this->_start, SIGNAL(triggered()), this, SLOT(__start()));
    this->connect(this->_stop, SIGNAL(triggered()), this, SLOT(__stop()));
    // Timer
    this->connect(timer, SIGNAL(timeout()), this, SLOT(__update()));
    // Tree
    this->connect(this->_tree, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(__menu(const QPoint &)));
    /*
     * Inflate
     */
    // Action
    QList<QAction *> control;
    control << this->_start;
    control << this->_stop;
    QList<QAction *> level;
    level << this->_verbose;
    level << this->_debug;
    level << this->_info;
    level << this->_warning;
    level << this->_error;
    // Menu
    this->_menu->addAction(this->_copy);
    this->_menu->addAction(this->_remove);
    // Private
    this->resize(QSize(768, 640));
    this->setMinimumSize(QSize(480, 320));
#ifdef Q_OS_WIN
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
#endif
    this->setWindowIcon(icon("window"));
    this->setWindowTitle(text("title_window").arg(this->_device));
    // Toolbar
    this->_toolbar->addActions(control);
    this->_toolbar->addSeparator();
    this->_toolbar->addAction(this->_load);
    this->_toolbar->addAction(this->_clear);
    this->_toolbar->addSeparator();
    this->_toolbar->addActions(level);
    this->_toolbar->addSeparator();
    this->_toolbar->addAction(this->_save);
    this->_toolbar->addSeparator();
    this->_toolbar->addAction(this->_scroll);
    // Layout
    this->_layout->addWidget(this->_toolbar);
    this->_layout->addWidget(this->_tree);
    this->setLayout(this->_layout);
    // Headers
    QStringList labels;
    labels << text("header_priority");
    labels << text("header_time");
    labels << text("header_pid");
    labels << text("header_tid");
    labels << text("header_tag");
    labels << text("header_message");
    this->_tree->setHeaderLabels(labels);
    this->_tree->setColumnWidth(0, 64);
    this->_tree->setColumnWidth(1, 128);
    this->_tree->setColumnWidth(2, 48);
    this->_tree->setColumnWidth(3, 48);
    this->_tree->setColumnWidth(4, 128);
    /*
     * @Assign
     */
    // Timer
    timer->start(1 * 500);
}

void Logcat::__clear()
{
    if (this->_tree->model()->hasChildren())
        this->_tree->model()->removeRows(0, this->_tree->model()->rowCount());
}

void Logcat::__copy()
{
    QModelIndexList list = this->_tree->selectionModel()->selectedRows(0);
    if (list.count() < 1)
        return;
    QStringList lines;
    foreach (QModelIndex index, list) {
        Bridge::Log log = qvariant_cast<Bridge::Log>(this->_tree->model()->data(index, ROLE_STRUCT));
        lines << log.line;
    }
    if (lines.isEmpty() || (lines.count() < 1))
        return;
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(lines.join(QString("\n")));
}

void Logcat::__load()
{
    QString path = QFileDialog::getOpenFileName(this, text("title_load"), QString(""), text("lcat"), 0, 0);
    if (path.isEmpty())
        return;
    if (path.indexOf(".alog") == -1)
        path += QString(".alog");
    QFile file(path);
    if (!file.exists()) {
        QMessageBox::critical(this, text("failure"), text("found"), QMessageBox::Close);
        return;
    }
    if (!file.open(QIODevice::Text | QIODevice::ReadOnly)) {
        QMessageBox::critical(this, text("failure"), text("read"), QMessageBox::Close);
        return;
    }
    this->__clear();
    QTextStream stream(&file);
    QString line;
    do {
        line = stream.readLine();
        if (!line.isEmpty())
            this->__logcat(line);
    } while (!line.isNull());
    file.close();
}

void Logcat::__logcat(const QString &line)
{
    // Match
    if (line.isEmpty())
        return;
    QRegularExpressionMatch matcher = this->_regex.match(line);
    if (!matcher.hasMatch())
        return;
    // Parse
    Bridge::Log log;
    log.line = line;
    log.message = matcher.captured(QString("message"));
    log.pid = matcher.captured(QString("pid"));
    log.priority = matcher.captured(QString("priority")).at(0);
    log.tag = matcher.captured(QString("tag")).trimmed();
    log.tid = matcher.captured(QString("tid"));
    log.time = matcher.captured(QString("time"));
    // Initialize
    QTreeWidgetItem *row = new QTreeWidgetItem();
    // Append
    row->setText(0, log.priority);
    row->setText(1, log.time);
    row->setText(2, log.pid);
    row->setText(3, log.tid);
    row->setText(4, log.tag);
    row->setText(5, log.message);
    // Assign
    QVariant data;
    data.setValue(log);
    row->setData(0, ROLE_STRUCT, data);
    row->setData(0, Qt::TextAlignmentRole, Qt::AlignCenter);
    row->setData(1, Qt::TextAlignmentRole, Qt::AlignCenter);
    row->setData(2, Qt::TextAlignmentRole, Qt::AlignCenter);
    row->setData(3, Qt::TextAlignmentRole, Qt::AlignCenter);
    // Colorize
    QColor color;
    if (log.priority == QString('A'))
        color = QColor("#000000");
    else if (log.priority == QString('D'))
        color = QColor("#0072BC");
    else if (log.priority == QString('E'))
        color = QColor("#ED1C24");
    else if (log.priority == QString('F'))
        color = QColor("#000000");
    else if (log.priority == QString('I'))
        color = QColor("#39B54A");
    else if (log.priority == QString('V'))
        color = QColor("#000000");
    else if (log.priority == QString('W'))
        color = QColor("#ABA000");
    else
        color = QColor("#000000");
    row->setForeground(0, color);
    row->setForeground(1, color);
    row->setForeground(2, color);
    row->setForeground(3, color);
    row->setForeground(4, color);
    row->setForeground(5, color);
    // Insert
    this->_tree->addTopLevelItem(row);
    // Scroll
    if (this->_scroll->isChecked())
        this->_tree->scrollToBottom();
}

void Logcat::__menu(const QPoint &point)
{
    QModelIndex index = this->_tree->indexAt(point);
    if (index.isValid()) {
        this->_tree->selectionModel()->select(index, QItemSelectionModel::Select | QItemSelectionModel::Rows);
        this->_menu->exec(this->_tree->mapToGlobal(point));
    }
}

void Logcat::__remove()
{
    QModelIndexList list = this->_tree->selectionModel()->selectedRows(0);
    if (list.count() > 0) {
        foreach (QModelIndex index, list)
            this->_tree->model()->removeRow(index.row());
    }
    this->_tree->clearSelection();
}

void Logcat::__save()
{
    if (this->_tree->model()->rowCount() > 0) {
        QString path = QFileDialog::getSaveFileName(this, text("title_save"), QString(""), text("lcat"), 0, 0);
        if (path.isEmpty())
            return;
        if (path.indexOf(".lcat") == -1)
            path += QString(".lcat");
        QFile file(path);
        if (file.exists()) {
            int button = QMessageBox::information(this, text("title_overwrite"), text("message_overwrite"), QMessageBox::Ok, QMessageBox::Cancel);
            if (button == QMessageBox::Cancel)
                return;
        }
        if (file.exists())
            file.remove();
        if (!file.open(QIODevice::Text | QIODevice::WriteOnly)) {
            QMessageBox::critical(this, text("title_write"), text("message_write"), QMessageBox::Close);
            return;
        }
        QTextStream stream(&file);
        QModelIndex parent = this->_tree->rootIndex();
        int rows = this->_tree->model()->rowCount(parent);
        for (int row = 0; row < rows; ++row) {
            QModelIndex index = this->_tree->model()->index(row, 0, parent);
            Bridge::Log log = qvariant_cast<Bridge::Log>(this->_tree->model()->data(index, ROLE_STRUCT));
            stream << log.line << endl;
        }
        file.close();
    } else
        QMessageBox::critical(this, text("title_empty"), text("message_empty"), QMessageBox::Close);
}

void Logcat::__start()
{
    this->_logger = new Runtime::Logger(this->_device);
    this->connect(this->_logger, SIGNAL(logcat(const QString &)), this, SLOT(__logcat(const QString &)));
    this->connect(this->_logger, SIGNAL(status(const bool)), this, SLOT(__status(const bool)));
    this->_logger->start();
}

void Logcat::__status(const bool running)
{
    if (running) {
        this->_load->setEnabled(false);
        this->_save->setEnabled(false);
        this->_start->setEnabled(false);
        this->_stop->setEnabled(true);
    } else {
        this->_load->setEnabled(true);
        this->_save->setEnabled(true);
        this->_start->setEnabled(true);
        this->_stop->setEnabled(false);
    }
}

void Logcat::__stop()
{
    if (this->_logger || (this->_logger != 0))
        this->_logger->stop();
    this->_logger = 0;
}

void Logcat::__update()
{
    if (this->_tree->model()->rowCount() < 1)
        return;
    while (this->_tree->model()->rowCount() >= 1000)
        this->_tree->model()->removeRow(0);
}

} // namespace Dialog
} // namespace APKStudio
} // namespace VPZ
