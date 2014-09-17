#ifndef VPZ_APKSTUDIO_DIALOG_PROJECT_H
#define VPZ_APKSTUDIO_DIALOG_PROJECT_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QDirIterator>
#include <QFileDialog>
#include <QFileInfo>
#include <QFormLayout>
#include <QIcon>
#include <QItemSelection>
#include <QLineEdit>
#include <QList>
#include <QModelIndex>
#include <QModelIndexList>
#include <QObject>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QSize>
#include <QStackedWidget>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QStandardPaths>
#include <QString>
#include <QStringList>
#include <QTreeView>
#include <QVBoxLayout>
#include <QWidget>

#include "../bridge/constant.h"
#include "../bridge/variant.h"
#include "../utility/configuration.h"
#include "../utility/format.h"
#include "../utility/resource.h"
#include "../utility/ui.h"

namespace VPZ {
namespace APKStudio {
namespace Dialog {

class Project : public QDialog
{
    Q_OBJECT
private:
    // Enum
    enum Browse {
        APK_ = 1,
        LOCATION
    };
    enum Page {
        PROPERTIES = 1,
        DEPENDENCIES
    };
    // Textbox
    QLineEdit *_apk;
    QLineEdit *_name;
    QLineEdit *_location;
    // Buttons
    QDialogButtonBox *_buttons;
    // Button
    QPushButton *_cancel;
    QPushButton *_create;
    // Tree
    QTreeView *_tree;
    // Model
    QStandardItemModel *_model;
    // Function
    void browse(int);
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("project", name);
    }
    QWidget *page();
    static const QString path()
    {
        return Utility::Resource::root();
    }
    void refresh();
    static QString text(const char *key)
    {
        return Utility::Resource::text("project", key);
    }
private slots:
    void __apk()
    {
        this->browse(APK_);
    }
    void __changed();
    void __location()
    {
        this->browse(LOCATION);
    }
public:
    // Constructor
    Project(QWidget * = 0);
    // Function
    QString apk()
    {
        return this->_apk->text();
    }
    QString framework();
    QString location()
    {
        return this->_location->text();
    }
    QString name()
    {
        return this->_name->text();
    }
    // Destructor
    ~Project() { }
};

} // namespace Wizard
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_DIALOG_PROJECT_H
