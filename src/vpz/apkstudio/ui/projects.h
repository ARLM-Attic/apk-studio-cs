#ifndef VPZ_APKSTUDIO_UI_PROJECTS_H
#define VPZ_APKSTUDIO_UI_PROJECTS_H

#include <QAction>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QFileInfoList>
#include <QHeaderView>
#include <QIcon>
#include <QInputDialog>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QLabel>
#include <QMenu>
#include <QMessageBox>
#include <QModelIndex>
#include <QModelIndexList>
#include <QMouseEvent>
#include <QObject>
#include <QProcess>
#include <QPoint>
#include <QSize>
#include <QStandardItemModel>
#include <QString>
#include <QToolBar>
#include <QTreeView>
#include <QVariant>
#include <QVBoxLayout>
#include <QWidget>

#ifdef Q_OS_WIN
#include "qt_windows.h"
#include "qwindowdefs_win.h"
#include <shellapi.h>
#endif

#include "../bridge/constant.h"
#include "../utility/resource.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

class QTree : public QTreeView
{
    Q_OBJECT
public:
    QTree(QWidget *parent = 0) : QTreeView(parent) { }
    void mouseDoubleClickEvent(QMouseEvent *event)
    {
        QTreeView::mouseDoubleClickEvent(event);
        QModelIndexList indexes = this->selectedIndexes();
        if (indexes.count() == 1)
            emit doubleClick(indexes.first());
    }
signals:
    void doubleClick(const QModelIndex &index);
};

class Projects : public QWidget
{
    Q_OBJECT
private:
    // Action
    QAction *_build;
    QAction *_close;
    QAction *_delete;
    QAction *_delete_;
    QAction *_edit;
    QAction *_properties;
    QAction *_properties_;
    QAction *_refresh;
    QAction *_refresh_;
    QAction *_rename;
    QAction *_rename_;
    QAction *_show;
    // Function
    void refresh(QStandardItem *);
    // Menu
    QMenu *_menu;
    // Model
    QStandardItemModel *_model;
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("projects" ,name);
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("projects", key);
    }
    // Toolbar
    QToolBar *_toolbar;
    // Tree
    QTree *_tree;
private slots:
    // Action
    void __build()
    {
        emit build();
    }
    void __close();
    void __click(const QModelIndex &);
    void __delete();
    void __menu(const QPoint &);
    void __edit();
    void __properties();
    void __refresh();
    void __rename();
    void __show();
    // Tree
    void __select(const QItemSelection &, const QItemSelection &);
public:
    // Constructor
    Projects(QWidget * = 0);
    enum Type {
        DIRECTORY = 1,
        FILE,
        PROJECT
    };
    // Function
    QString selected();
    void refresh(const QString &, bool build = false);
    bool load(const QString &);
    // Destructor
    ~Projects() { }
signals:
    void build();
    void closed(const QString &);
    void deleted(const QString &);
    void edit(const QString &);
    void message(const QString &);
    void progress(const int);
    void renamed(const QString &, const QString &);
    void selected(const bool);
};

} // namespace UI
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_UI_PROJECTS_H
