#include "ide.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

IDE::IDE(QWidget *parent)
    : QMainWindow(parent)
{
    /*
     * @Initialize
     */
    // Clipboard
    this->_clipboard = QApplication::clipboard();
    // Dialog
    this->_find = NULL;
    this->_replace = NULL;
    // Menubar
    this->_menubar = new Menubar(this);
    // Splitter
    this->_main = new QSplitter(Qt::Horizontal, this);
    this->_centre = new QSplitter(Qt::Vertical, this->_main);
    QSplitter *left = new QSplitter(Qt::Vertical, this->_main);
    // Panel
    this->_devices = new Devices(left);
    this->_editors = new Editors(this->_centre);
    this->_projects = new Projects(left);
    // Statusbar
    this->_statusbar = new Statusbar(this);
    // Toolbar
    this->_toolbar = new Toolbar(this);
    /*
     * @Prepare
     */
    // Window
    this->resize(QSize(800, 600));
    this->setMinimumSize(QSize(640, 480));
    this->setWindowTitle(text("title_window"));
    /*
     * @Bind
     */
    // Clipboard
    this->connect(this->_clipboard, SIGNAL(changed(const QClipboard::Mode &)), this, SLOT(__clipboard(const QClipboard::Mode &)));
    // Menubar
    this->connect(this->_menubar, SIGNAL(action(const int)), this, SLOT(__action(const int)));
    this->connect(this->_menubar, SIGNAL(toggled(const int, const bool)), this, SLOT(__toggle(const int, const bool)));
    // Editors
    this->connect(this->_editors, SIGNAL(changed()), this, SLOT(__changed()));
    this->connect(this->_editors, SIGNAL(cutable(const bool)), this, SLOT(__cutable(const bool)));
    this->connect(this->_editors, SIGNAL(count(const int)), this, SLOT(__editors(const int)));
    this->connect(this->_editors, SIGNAL(message(const QString &)), this, SLOT(__message(const QString &)));
    this->connect(this->_editors, SIGNAL(progress(const int)), this, SLOT(__progress(const int)));
    this->connect(this->_editors, SIGNAL(redoable(const bool)), this, SLOT(__redoable(const bool)));
    this->connect(this->_editors, SIGNAL(undoable(const bool)), this, SLOT(__undoable(const bool)));
    // Projects
    this->connect(this->_projects, SIGNAL(build()), this, SLOT(__build()));
    this->connect(this->_projects, SIGNAL(closed(const QString &)), this, SLOT(__closed(const QString &)));
    this->connect(this->_projects, SIGNAL(deleted(const QString &)), this, SLOT(__deleted(const QString &)));
    this->connect(this->_projects, SIGNAL(edit(const QString &)), this, SLOT(__edit(const QString &)));
    this->connect(this->_projects, SIGNAL(renamed(const QString &, const QString &)), this, SLOT(__renamed(const QString &, const QString &)));
    this->connect(this->_projects, SIGNAL(message(const QString &)), this, SLOT(__message(const QString &)));
    this->connect(this->_projects, SIGNAL(selected(const bool)), this, SLOT(__projects(const bool)));
    // Toolbar
    this->connect(this->_toolbar, SIGNAL(action(const int)), this, SLOT(__action(const int)));
    // Statusbar
    this->connect(this->_statusbar, SIGNAL(toggled(const int, const bool)), this, SLOT(__toggle(const int, const bool)));
    /*
     * @Inflate
     */
    // Splitter
    left->addWidget(this->_projects);
    left->addWidget(this->_devices);
    this->_centre->addWidget(this->_editors);
    this->_main->setContentsMargins(QMargins(2, 0, 2, 0));
    this->_main->addWidget(left);
    this->_main->addWidget(this->_centre);
    /*
     * @Assign
     */
    // Menubar
    this->setMenuBar(this->_menubar);
    // Splitter
    this->_centre->setStretchFactor(0, 1);
    this->_centre->setStretchFactor(1, 3);
    this->_main->setStretchFactor(0, 1);
    this->_main->setStretchFactor(1, 3);
    left->setStretchFactor(0, 2);
    left->setStretchFactor(1, 1);
    // Statusbar
    this->addToolBar(Qt::BottomToolBarArea, this->_statusbar);
    // Toolbar
    this->addToolBar(Qt::TopToolBarArea, this->_toolbar);
    // Window
    this->setCentralWidget(this->_main);
    this->context();
}

void IDE::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if (QMessageBox::Yes == QMessageBox::question(this, text("title_close"), text("message_close"), QMessageBox::No | QMessageBox::Yes))
        event->accept();
}

void IDE::context()
{
#ifdef Q_OS_WIN
    QSettings apk("HKEY_CURRENT_USER\\Software\\Classes\\.apk", QSettings::NativeFormat);
    apk.setValue("Content Type", "application/vnd.android.package-archive");
    apk.setValue("DefaultIcon", QCoreApplication::applicationFilePath().append(", 0"));
    apk.sync();
#endif
}

void IDE::open(const QString &path)
{
    if (path.isEmpty())
        return;
    this->_projects->load(path);
}

void IDE::__action(const int action)
{
    switch (action)
    {
    case UI::Menubar::ABOUT:
    {
        Dialog::About *about = new Dialog::About(this);
        about->show();
        break;
    }
    case UI::Menubar::APK:
    case UI::Toolbar::APK:
    {
        Dialog::Project *project = new Dialog::Project(this);
        int code = project->exec();
        if (code != QDialog::Accepted)
            break;
        QString location = QString(project->location()).append('/').append(project->name());
        // Prepare
        Runtime::Decompile *decompile = new Runtime::Decompile(project->apk(), location, project->framework());
        // Bind
        this->connect(decompile, SIGNAL(output(const QString &)), this, SLOT(__output(const QString &)));
        this->connect(decompile, SIGNAL(decompile(const QString &, const QString &)), this, SLOT(__decompile(const QString &, const QString &)));
        // Execute
        decompile->start();
        // Status
        this->_statusbar->progress(-1);
        this->_statusbar->message(text("start_decompile").arg(project->apk()));
        break;
    }
    case UI::Menubar::BUILD:
    case UI::Toolbar::BUILD:
    {
        QString directory = this->_projects->selected();
        if (directory.isEmpty())
            break;
        // Prepare
        Runtime::Recompile *recompile = new Runtime::Recompile(directory);
        // Bind
        this->connect(recompile, SIGNAL(output(const QString &)), this, SLOT(__output(const QString &)));
        this->connect(recompile, SIGNAL(recompile(const QString &, const QString &)), this, SLOT(__recompile(const QString &, const QString &)));
        // Execute
        recompile->start();
        // Status
        this->_statusbar->progress(-1);
        this->_statusbar->message(text("start_recompile").arg(directory));
        break;
    }
    case UI::Menubar::CLEAN:
    {
        QString path = this->_projects->selected();
        if (path.isEmpty())
            break;
        bool success = false;
        QDir directory(QString(path).append("/build"));
        if (directory.exists()) {
            directory.setFilter( QDir::NoDotAndDotDot | QDir::Files );
            foreach(QString item, directory.entryList()) {
                directory.remove(item);
                success = true;
            }
            directory.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
            foreach(QString item, directory.entryList()) {
                QDir sub(directory.absoluteFilePath(item));
                sub.removeRecursively();
                success = true;
            }
        }
        if (success) {
            this->_projects->refresh(path);
            this->_statusbar->message(text("success_clean").arg(path));
        } else
            this->_statusbar->message(text("success_clean").arg(path));
        break;
    }
    case UI::Menubar::CLOSE:
        this->_editors->close();
        break;
    case UI::Menubar::COPY:
        this->_editors->copy();
        break;
    case UI::Menubar::CUT:
        this->_editors->cut();
        break;
    case UI::Menubar::DIRECTORY:
    case UI::Toolbar::DIRECTORY:
    {
        QString path = QFileDialog::getOpenFileName(this, text("title_project"), IDE::path(), QString("apktool.yml (*.yml)"), 0, 0);
        if (path.isNull() || path.isEmpty())
            break;
        QFileInfo info(path);
        if (info.exists() && info.isFile())
            this->open(info.absoluteFilePath());
        break;
    }
    case UI::Menubar::FIND:
    {
        Coder *coder = this->_editors->coder();
        if (!coder || (coder == 0))
            break;
        if (this->_find)
            delete this->_find;
        this->_find = new Dialog::Find(false, this);
        this->_find->editor(coder);
        this->_find->show();
        break;
    }
    case UI::Menubar::GOTO:
    {
        Coder *coder = this->_editors->coder();
        if (!coder || (coder == 0))
            break;
        bool ok;
        int line = QInputDialog::getInt(this, text("title_goto"), text("message_goto"), 1, 1, coder->document()->blockCount(), 1, &ok);
        if (ok) {
            QTextCursor cursor(coder->document()->findBlockByLineNumber(line - 1));
            coder->setTextCursor(cursor);
        }
        break;
    }
    case UI::Menubar::PASTE:
        this->_editors->paste();
        break;
    case UI::Menubar::PRINT:
    case UI::Toolbar::PRINT:
    {
        Coder *coder = this->_editors->coder();
        if (!coder || (coder == 0))
            break;
        QPrinter printer;
        QPrintDialog *dialog = new QPrintDialog(&printer, this);
        if (dialog->exec() != QDialog::Accepted)
            break;
        coder->print(&printer);
        break;
    }
    case UI::Menubar::REDO:
        this->_editors->redo();
        break;
    case UI::Menubar::SAVE:
    case UI::Toolbar::SAVE:
        this->_editors->save();
        break;
    case UI::Menubar::SAVE_ALL:
        this->_editors->saveall();
        break;
    case UI::Menubar::UNDO:
        this->_editors->undo();
        break;
    case UI::Menubar::REPLACE:
    {
        Coder *coder = this->_editors->coder();
        if (!coder || (coder == 0))
            break;
        if (this->_replace != 0)
            delete this->_replace;
        this->_replace = new Dialog::Find(true, this);
        this->_replace->editor(coder);
        this->_replace->show();
        break;
    }
    case UI::Menubar::QUIT:
        this->close();
        break;
    case UI::Menubar::SETTINGS:
    {
        Dialog::Settings *settings = new Dialog::Settings(this);
        settings->exec();
        break;
    }
    case UI::Toolbar::SHELL:
    {
        QStringList arguments;
        QString command;
#ifdef Q_OS_WIN
        command.append("cmd.exe");
        arguments << QString("/k");
        arguments << QString("cd /d ").append(Utility::Configuration::apkstudio());
#else
        command.append("gnome-terminal");
        arguments << QString("--working-directory=").append(Utility::Configuration::apkstudio());
#endif
        QProcess::startDetached(command, arguments);
        break;
    }
    default:
        break;
    }
}

void IDE::__changed()
{
    Coder *coder = this->_editors->coder();
    if (!coder || (coder == 0))
        return;
    if (this->_find && (this->_find != NULL))
        this->_find->editor(coder);
    if (this->_replace && (this->_replace!= NULL))
        this->_replace->editor(coder);
}

void IDE::__clipboard(const QClipboard::Mode &mode)
{
    if (mode == QClipboard::Clipboard) {
        if (this->_clipboard->ownsClipboard())
            this->_menubar->enable(Menubar::PASTE, true);
        else
            this->_menubar->enable(Menubar::PASTE, false);
    }
}

void IDE::__closed(const QString &path)
{
    this->_editors->close(path);
}

void IDE::__cutable(const bool yes)
{
    this->_menubar->disable(Menubar::COPY, true);
    this->_menubar->disable(Menubar::CUT, true);
    if (yes) {
        this->_menubar->enable(Menubar::COPY, true);
        this->_menubar->enable(Menubar::CUT, true);
    }
}

void IDE::__decompile(const QString &apk, const QString &path)
{
    this->_statusbar->progress(0);
    if (path.isEmpty()) {
        this->_statusbar->message(text("stop_decompile_failed").arg(apk));
        return;
    }
    this->_statusbar->message(text("stop_decompile_success").arg(apk));
    this->open(path);
}

void IDE::__deleted(const QString &path)
{
    this->_editors->deleted(path);
}

void IDE::__edit(const QString &path)
{
    this->_editors->load(path);
}

void IDE::__editors(const int count)
{
    this->_menubar->disable(Menubar::CLOSE, true);
    this->_menubar->disable(Menubar::FIND, true);
    this->_menubar->disable(Menubar::GOTO, true);
    this->_menubar->disable(Menubar::PASTE, true);
    this->_menubar->disable(Menubar::PRINT, true);
    this->_menubar->disable(Menubar::REPLACE, true);
    this->_menubar->disable(Menubar::SAVE, true);
    this->_menubar->disable(Menubar::SAVE_ALL, true);
    this->_toolbar->disable(Toolbar::PRINT, true);
    this->_toolbar->disable(Toolbar::SAVE, true);
    if (count > 0) {
        this->_menubar->enable(Menubar::CLOSE, true);
        this->_menubar->enable(Menubar::FIND, true);
        this->_menubar->enable(Menubar::GOTO, true);
        if (this->_clipboard->ownsClipboard())
            this->_menubar->enable(Menubar::PASTE, true);
        this->_menubar->enable(Menubar::PRINT, true);
        this->_menubar->enable(Menubar::REPLACE, true);
        this->_menubar->enable(Menubar::SAVE, true);
        this->_menubar->enable(Menubar::SAVE_ALL, true);
        this->_toolbar->enable(Toolbar::PRINT, true);
        this->_toolbar->enable(Toolbar::SAVE, true);
    } else {
        this->_menubar->disable(Menubar::COPY, true);
        this->_menubar->disable(Menubar::CUT, true);
        this->_menubar->disable(Menubar::REDO, true);
        this->_menubar->disable(Menubar::UNDO, true);
    }
}

void IDE::__initialize()
{
    /*
     * @Splitter
     */
    // Main
    QList<int> sizes = this->_main->sizes();
    int width = sizes[0] + sizes[1];
    sizes[0] = static_cast<int>(width / 4);
    sizes[1] = width - sizes[0];
    this->_main->setSizes(sizes);
    /*
     * @CLI
     */
    QStringList arguments = QCoreApplication::arguments();
    if (arguments.count() > 0) {
        foreach (const QString &argument, arguments) {
            if (argument.isEmpty())
                continue;
            QFileInfo file(argument);
        }
    }
}

void IDE::__message(const QString &text)
{
    QString message = QString(text);
    if (text.length() > 64) {
        QString left = QString(text).left(32);
        QString right = QString(text).right(32);
        message = QString(left).append("...").append(right);
    }
    emit this->_statusbar->message(message.trimmed());
}

void IDE::__output(const QString &text)
{
    if (text.isEmpty())
        return;
    // Directory
    QDir directory(Utility::Configuration::log());
    if (!directory.exists())
        directory.mkdir(Utility::Configuration::log());
    QString name = QString(Utility::Format::time(QDateTime::currentDateTime(), QString("yyyy-MM-dd_hh-mm-ss"))).append(".txt");
    QFile file(QString(directory.absolutePath()).append('/').append(name));
    if (file.exists())
        file.remove();
    if (!file.open(QIODevice::Text | QIODevice::WriteOnly))
        return;
    QTextStream stream(&file);
    stream << text << endl;
    file.close();
    QProcess::startDetached(Utility::Configuration::text(), QStringList(file.fileName()));
}

void IDE::__projects(const bool selected)
{
    if (selected) {
        this->_menubar->enable(Menubar::BUILD, true);
        this->_menubar->enable(Menubar::CLEAN, true);
        this->_menubar->enable(Menubar::PROPERTIES, true);
        this->_toolbar->enable(Toolbar::BUILD, true);
    } else {
        this->_menubar->disable(Menubar::BUILD, true);
        this->_menubar->disable(Menubar::CLEAN, true);
        this->_menubar->disable(Menubar::PROPERTIES, true);
        this->_toolbar->disable(Toolbar::BUILD, true);
    }
}

void IDE::__progress(const int value)
{
    emit this->_statusbar->progress(value);
}

void IDE::__recompile(const QString &directory, const QString &path)
{
    this->_statusbar->progress(0);
    if (path.isEmpty()) {
        this->_statusbar->message(text("stop_recompile_failed").arg(directory));
        this->_projects->refresh(directory, true);
        return;
    }
    this->_statusbar->message(text("stop_recompile_success").arg(directory));
    this->_statusbar->progress(0);
    QFileInfo project(directory);
    if (project.exists() && project.isDir())
        this->_projects->refresh(project.absoluteFilePath());
}

void IDE::__redoable(const bool yes)
{
    if (yes)
        this->_menubar->enable(Menubar::REDO, true);
    else
        this->_menubar->disable(Menubar::REDO, true);
}

void IDE::__renamed(const QString &current, const QString &previous)
{
    this->_editors->renamed(current, previous);
}

void IDE::__toggle(const int action, const bool checked)
{
    switch (action)
    {
    case UI::Statusbar::SIDEBAR:
    case UI::Menubar::SIDEBAR:
    {
        QList<int> sizes = this->_main->sizes();
        int width = sizes[0] + sizes[1];
        if (checked) {
            sizes[0] = static_cast<int>(width / 4);
            sizes[1] = width - sizes[0];
        } else {
            sizes[1] = sizes[0] + sizes[1];
            sizes[0] = 0;
        }
        this->_main->setSizes(sizes);
        this->_menubar->toggle(Menubar::SIDEBAR, checked, true);
        this->_statusbar->toggle(Statusbar::SIDEBAR, checked, true);
        break;
    }
    default:
        break;
    }
}

void IDE::__undoable(const bool yes)
{
    if (yes)
        this->_menubar->enable(Menubar::UNDO, true);
    else
        this->_menubar->disable(Menubar::UNDO, true);
}

} // namespace UI
} // namespace APKStudio
} // namespace VPZ
