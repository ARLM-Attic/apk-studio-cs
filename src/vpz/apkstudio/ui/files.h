#ifndef VPZ_APKSTUDIO_UI_FILES_H
#define VPZ_APKSTUDIO_UI_FILES_H

#include <QFileDialog>
#include <QInputDialog>
#include <QLineEdit>
#include <QList>
#include <QMap>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QString>
#include <QStringList>
#include <QTreeWidget>
#include <QWidget>

#include "../bridge/constant.h"
#include "../bridge/variant.h"
#include "../dialog/permissions.h"
#include "../runtime/chmod.h"
#include "../runtime/file.h"
#include "../runtime/new.h"
#include "../runtime/pull.h"
#include "../runtime/push.h"
#include "../runtime/rename.h"
#include "../runtime/rm.h"
#include "../utility/format.h"
#include "../utility/resource.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

class Files : public QTreeWidget
{
    Q_OBJECT
private:
    // Function
    void initialize();
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("files" ,name);
    }
    static const QString path()
    {
        return Utility::Resource::root();
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("files", key);
    }
    // Variable
    QString _device;
    QString _current;
private slots:
    void __chmod(const QMap<QString, bool> &);
    void __click(QTreeWidgetItem *, const int);
    void __delete(const QMap<QString, bool> &);
    void __file(const QList<Bridge::File> &);
    void __new(const bool, const QString &);
    void __rename(const bool, const QString &);
    void __pull(const QMap<QString, bool> &);
    void __push(const QMap<QString, bool> &);
    void __select(const QItemSelection &, const QItemSelection &);
public:
    // Constructor
    Files(const QString &device, const QString &path, QWidget *parent = 0)
        : QTreeWidget(parent)
    {
        this->_device = device;
        this->_current = path;
        this->initialize();
    }
    // Function
    void chmod();
    void copy() {}
    void delete_();
    void move() {}
    void new_();
    void pull();
    void push();
    void refresh();
    void rename();
    bool selected();
    // Destructor
    ~Files() { }
signals:
    void files(const bool);
    void message(const QString &);
    void progress(const int);
};

} // namespace UI
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_UI_FILES_H
