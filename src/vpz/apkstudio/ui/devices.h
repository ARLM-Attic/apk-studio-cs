#ifndef VPZ_APKSTUDIO_UI_DEVICES_H
#define VPZ_APKSTUDIO_UI_DEVICES_H

#include <QAbstractItemView>
#include <QAction>
#include <QDesktopServices>
#include <QIcon>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QLabel>
#include <QList>
#include <QMap>
#include <QMargins>
#include <QMenu>
#include <QMessageBox>
#include <QModelIndex>
#include <QModelIndexList>
#include <QObject>
#include <QProcess>
#include <QSize>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QStringList>
#include <QString>
#include <QToolBar>
#include <QToolButton>
#include <QTreeView>
#include <QUrl>
#include <QVBoxLayout>
#include <QWidget>

#include "../bridge/constant.h"
#include "../bridge/variant.h"
#include "../dialog/browser.h"
#include "../dialog/information.h"
#include "../dialog/logcat.h"
#include "../runtime/adb.h"
#include "../runtime/refresh.h"
#include "../runtime/screenshot.h"
#include "../utility/configuration.h"
#include "../utility/resource.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

class Devices : public QWidget
{
    Q_OBJECT
private:
    // Action
    QAction *_browser;
    QAction *_information;
    QAction *_logcat;
    QAction *_refresh;
    QAction *_restart;
    QAction *_screenshot;
    QAction *_shell;
    QAction *_start;
    QAction *_stop;
    // Button
    QToolButton *_adb;
    // Function
    Bridge::Device selected();
    // Model
    QStandardItemModel *_model;
    // Tree
    QTreeView *_tree;
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("devices" ,name);
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("devices", key);
    }
    // Toolbar
    QToolBar *_toolbar;
private slots:
    // Action
    void __adb();
    void __adb(const int);
    void __browser();
    void __information();
    void __logcat();
    void __refresh();
    void __refresh(const QList<Bridge::Device> &);
    void __restart()
    {
        this->__adb(Runtime::ADB::RESTART);
    }
    void __screenshot();
    void __screenshot(const QString &);
    void __shell();
    void __start()
    {
        this->__adb(Runtime::ADB::START);
    }
    void __stop()
    {
        this->__adb(Runtime::ADB::STOP);
    }
    // List
    void __select(const QItemSelection &, const QItemSelection &);
public:
    // Constructor
    Devices(QWidget * = 0);
    // Destructor
    ~Devices() { }
};

} // namespace UI
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_UI_DEVICES_H
