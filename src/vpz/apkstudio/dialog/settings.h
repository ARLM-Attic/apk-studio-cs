#ifndef VPZ_APKSTUDIO_DIALOG_SETTINGS_H
#define VPZ_APKSTUDIO_DIALOG_SETTINGS_H

#include <QAbstractItemView>
#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDirIterator>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFormLayout>
#include <QIcon>
#include <QItemSelection>
#include <QLineEdit>
#include <QListView>
#include <QMargins>
#include <QModelIndex>
#include <QModelIndexList>
#include <QObject>
#include <QPushButton>
#include <QSettings>
#include <QSize>
#include <QSpinBox>
#include <QSplitter>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QString>
#include <QTreeView>
#include <QVariant>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

#include "add.h"
#include "../bridge/constant.h"
#include "../utility/resource.h"
#include "../utility/format.h"
#include "../utility/configuration.h"
#include "../utility/ui.h"

namespace VPZ {
namespace APKStudio {
namespace Dialog {

class Settings : public QDialog
{
    Q_OBJECT
private:
    QPushButton *_add;
    QLineEdit *_binaries;
    QDialogButtonBox *_buttons;
    QPushButton *_cancel;
    QTreeView *_tree;
    QStandardItemModel *_model;
    QSpinBox *_heap;
    QPushButton *_remove;
    QCheckBox *_root;
    QPushButton *_save;
    QLineEdit *_text;
    QCheckBox *_verbose;
    QSettings _settings;
    enum Browse {
        BINARIES = 1,
        CERTIFICATE,
        KEY
    };
    enum Setting {
        BUILD = 1,
        DIRECTORIES,
        EDITOR,
        GENERAL,
        KEYS,
        LICENSE
    };
    QWidget *page();
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("settings", name);
    }
    static const QString path()
    {
        return Utility::Resource::root();
    }
    void refresh();
    static QString text(const char *key)
    {
        return Utility::Resource::text("settings", key);
    }
private slots:
    void __add();
    void __browse();
    void __cancel();
    void __changed();
    void __remove();
    void __save();
    void __select(const QItemSelection &, const QItemSelection &);
public:
    Settings(QWidget * = 0, Qt::WindowFlags = 0);
    ~Settings() { }
};

} // namespace Dialog
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_DIALOG_SETTINGS_H
