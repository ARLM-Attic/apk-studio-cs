#ifndef VPZ_APKSTUDIO_DIALOG_BROWSER_H
#define VPZ_APKSTUDIO_DIALOG_BROWSER_H

#include <QAction>
#include <QDialog>
#include <QHeaderView>
#include <QIcon>
#include <QItemSelection>
#include <QLabel>
#include <QMargins>
#include <QMenu>
#include <QObject>
#include <QProgressBar>
#include <QSize>
#include <QSplitter>
#include <QString>
#include <QTabWidget>
#include <QToolButton>
#include <QTreeWidget>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>

#include "../bridge/variant.h"
#include "../ui/applications.h"
#include "../ui/files.h"
#include "../ui/partitions.h"
#include "../utility/resource.h"
#include "../utility/text.h"

namespace VPZ {
namespace APKStudio {
namespace Dialog {

class Browser : public QDialog
{
    Q_OBJECT
private:
    // Action
    QAction *_chmod;
    QAction *_delete;
    QAction *_disable;
    QAction *_enable;
    QAction *_install;
    QAction *_new;
    QAction *_pull;
    QAction *_push;
    QAction *_refresh;
    QAction *_remount;
    QAction *_rename;
    QAction *_uninstall;
    // Enum
    enum Tree {
        APPLICATIONS = 0,
        BLUETOOTH,
        CAMERA,
        DOWNLOADS,
        EXTERNAL,
        SYSTEM,
        MUSIC,
        PARTITIONS,
        PICTURES,
        VIDEOS
    };
    // Function
    void initialize();
    UI::Applications *applications();
    UI::Files *files(const QString & = QString('/'));
    UI::Partitions *partitions();
    // Layout
    QVBoxLayout *_layout;
    // Progress
    QProgressBar *_progress;
    // Status
    QLabel *_status;
    // Tabs
    QTabWidget *_tabs;
    // Tree
    QSplitter *_splitter;
    // Tree
    QTreeWidget *_tree;
    // Toolbar
    QToolBar *_statusbar;
    QToolBar *_toolbar;
    // Variable
    QString _device;
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("browser", name);
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("browser", key);
    }
private slots:
    void __applications(const bool selected)
    {
        this->_disable->setEnabled(false);
        this->_enable->setEnabled(false);
        this->_pull->setEnabled(false);
        this->_uninstall->setEnabled(false);
        if (!selected)
            return;
        this->_disable->setEnabled(true);
        this->_enable->setEnabled(true);
        this->_pull->setEnabled(true);
        this->_uninstall->setEnabled(true);
    }
    void __chmod()
    {
        QObject *pointer = this->_tabs->currentWidget();
        if (pointer == NULL)
            return;
        UI::Files *files = qobject_cast<UI::Files *>(pointer);
        if (files != NULL) {
            files->chmod();
            return;
        }
    }
    void __close(const int);
    void __current(const int index);
    void __delete()
    {
        QObject *pointer = this->_tabs->currentWidget();
        if (pointer == NULL)
            return;
        UI::Files *files = qobject_cast<UI::Files *>(pointer);
        if (files != NULL) {
            files->delete_();
            return;
        }
    }
    void __disable()
    {
        QObject *pointer = this->_tabs->currentWidget();
        if (pointer == NULL)
            return;
        UI::Applications *applications = qobject_cast<UI::Applications *>(pointer);
        if (applications != NULL) {
            applications->disable();
            return;
        }
    }
    void __enable()
    {
        QObject *pointer = this->_tabs->currentWidget();
        if (pointer == NULL)
            return;
        UI::Applications *applications = qobject_cast<UI::Applications *>(pointer);
        if (applications != NULL) {
            applications->enable();
            return;
        }
    }
    void __files(const bool selected)
    {
        this->_chmod->setEnabled(false);
        this->_delete->setEnabled(false);
        this->_pull->setEnabled(false);
        this->_rename->setEnabled(false);
        if (!selected)
            return;
        this->_chmod->setEnabled(true);
        this->_delete->setEnabled(true);
        this->_pull->setEnabled(true);
        this->_rename->setEnabled(true);
    }
    void __install()
    {
        QObject *pointer = this->_tabs->currentWidget();
        if (pointer == NULL)
            return;
        UI::Applications *applications = qobject_cast<UI::Applications *>(pointer);
        if (applications != NULL) {
            applications->install();
            return;
        }
    }
    void __new()
    {
        QObject *pointer = this->_tabs->currentWidget();
        if (pointer == NULL)
            return;
        UI::Files *files = qobject_cast<UI::Files *>(pointer);
        if (files != NULL) {
            files->new_();
            return;
        }
    }
    void __partitions(const bool selected)
    {
        this->_remount->setEnabled(false);
        if (!selected)
            return;
        this->_remount->setEnabled(true);
    }
    void __pull()
    {
        QObject *pointer = this->_tabs->currentWidget();
        if (pointer == NULL)
            return;
        UI::Files *files = qobject_cast<UI::Files *>(pointer);
        if (files != NULL) {
            files->pull();
            return;
        }
        UI::Applications *applications = qobject_cast<UI::Applications *>(pointer);
        if (applications != NULL) {
            applications->pull();
            return;
        }
    }
    void __push()
    {
        QObject *pointer = this->_tabs->currentWidget();
        if (pointer == NULL)
            return;
        UI::Files *files = qobject_cast<UI::Files *>(pointer);
        if (files != NULL) {
            files->push();
            return;
        }
    }
    void __refresh()
    {
        QObject *pointer = this->_tabs->currentWidget();
        if (pointer == NULL)
            return;
        UI::Applications *applications = qobject_cast<UI::Applications *>(pointer);
        if ((applications != NULL) && applications->isEnabled()) {
            applications->refresh();
            return;
        }
        UI::Files *files = qobject_cast<UI::Files *>(pointer);
        if ((files != NULL) && files->isEnabled()) {
            files->refresh();
            return;
        }
        UI::Partitions *partitions = qobject_cast<UI::Partitions *>(pointer);
        if ((partitions != NULL) && partitions->isEnabled()) {
            partitions->refresh();
            return;
        }
    }
    void __remount()
    {
        QObject *pointer = this->_tabs->currentWidget();
        if (pointer == NULL)
            return;
        UI::Partitions *partitions = qobject_cast<UI::Partitions *>(pointer);
        if (partitions != NULL) {
            partitions->remount();
            return;
        }
    }
    void __rename()
    {
        QObject *pointer = this->_tabs->currentWidget();
        if (pointer == NULL)
            return;
        UI::Files *files = qobject_cast<UI::Files *>(pointer);
        if (files != NULL) {
            files->rename();
            return;
        }
    }
    void __tree(const QModelIndex &);
    void __uninstall()
    {
        QObject *pointer = this->_tabs->currentWidget();
        if (pointer == NULL)
            return;
        UI::Applications *applications = qobject_cast<UI::Applications *>(pointer);
        if (applications != NULL) {
            applications->uninstall();
            return;
        }
    }
public:
    // Constructor
    Browser(const QString &device, QWidget *parent = 0)
        : QDialog(parent)
    {
        this->_device = device;
        this->initialize();
    }
    // Destructor
    ~Browser() { }
public slots:
    void __message(const QString &message)
    {
        this->_status->setText(message);
    }
    void __progress(const int value)
    {
        if (value > -1) {
            if (this->_progress->maximum() < 100)
                this->_progress->setMaximum(100);
            this->_progress->setValue(value);
        } else {
            this->_progress->setMaximum(0);
            this->_progress->setValue(0);
        }
    }
};

} // namespace Dialog
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_DIALOG_BROWSER_H
