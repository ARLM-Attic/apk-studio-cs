#ifndef VPZ_APKSTUDIO_UI_IDE_H
#define VPZ_APKSTUDIO_UI_IDE_H

#include <QApplication>
#include <QClipboard>
#include <QCloseEvent>
#include <QCoreApplication>
#include <QDialog>
#include <QDir>
#include <QFileInfo>
#include <QFileDialog>
#include <QInputDialog>
#include <QIcon>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QPrintDialog>
#include <QPrinter>
#include <QSize>
#include <QSplitter>
#include <QString>
#include <QTextStream>
#include <QVariant>
#include <QWidget>

#include "devices.h"
#include "editors.h"
#include "menubar.h"
#include "projects.h"
#include "statusbar.h"
#include "toolbar.h"
#include "../dialog/about.h"
#include "../dialog/find.h"
#include "../dialog/project.h"
#include "../dialog/settings.h"
#include "../runtime/decompile.h"
#include "../runtime/recompile.h"
#include "../utility/resource.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

class IDE : public QMainWindow
{
    Q_OBJECT
private:
    // Clipbard
    QClipboard *_clipboard;
    // Dialog
    Dialog::Find *_find;
    Dialog::Find *_replace;
    // Event
    void closeEvent(QCloseEvent *);
    // Function
    void context();
    void open(const QString &);
    static const QString path()
    {
        return Utility::Resource::root();
    }
    void terminate();
    // Panel
    Devices *_devices;
    Editors *_editors;
    Projects *_projects;
    // Resource
    static QString text(const char *key)
    {
        return Utility::Resource::text("ide", key);
    }
    // Splitter
    QSplitter *_centre;
    QSplitter *_main;
    // UI
    Menubar *_menubar;
    Statusbar *_statusbar;
    Toolbar *_toolbar;
private slots:
    void __action(const int);
    void __build()
    {
        this->__action(Toolbar::BUILD);
    }
    void __changed();
    void __clipboard(const QClipboard::Mode & = QClipboard::Selection);
    void __closed(const QString &);
    void __cutable(const bool);
    void __decompile(const QString &, const QString &);
    void __deleted(const QString &);
    void __edit(const QString &);
    void __editors(const int);
    void __message(const QString &);
    void __output(const QString &);
    void __projects(const bool);
    void __progress(const int);
    void __recompile(const QString &, const QString &);
    void __redoable(const bool);
    void __renamed(const QString &, const QString &);
    void __toggle(const int, const bool);
    void __undoable(const bool);
public:
    // Constructor
    IDE(QWidget * = 0);
    // Destrcutor
    ~IDE() { }
public slots:
    void __initialize();
};

} // namespace UI
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_UI_IDE_H
