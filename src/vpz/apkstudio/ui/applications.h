#ifndef VPZ_APKSTUDIO_UI_APPLICATIONS_H
#define VPZ_APKSTUDIO_UI_APPLICATIONS_H

#include <QFileDialog>
#include <QMap>
#include <QMessageBox>
#include <QString>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>

#include "../bridge/variant.h"
#include "../runtime/install.h"
#include "../runtime/pull.h"
#include "../runtime/state.h"
#include "../runtime/uninstall.h"
#include "../runtime/package.h"
#include "../utility/format.h"
#include "../utility/resource.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

class Applications : public QTreeWidget
{
    Q_OBJECT
private:
    // Function
    void initialize();
    void state(const bool enable);
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("applications" ,name);
    }
    static const QString path()
    {
        return Utility::Resource::root();
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("applications", key);
    }
    // Variable
    QString _device;
private slots:
    void __install(const QMap<QString, bool> &);
    void __package(const QList<Bridge::Application> &);
    void __pull(const QMap<QString, bool> &);
    void __select(const QItemSelection &, const QItemSelection &);
    void __state(const bool, const QString &, const bool);
    void __uninstall(const bool, const QString &);
public:
    // Constructor
    Applications(const QString &device, QWidget *parent = 0)
        : QTreeWidget(parent)
    {
        this->_device = device;
        this->initialize();
    }
    // Function
    void disable()
    {
        this->state(false);
    }
    void enable()
    {
        this->state(true);
    }
    void install();
    void pull();
    void refresh();
    bool selected();
    void uninstall();
    // Destructor
    ~Applications() { }
signals:
    void applications(const bool);
    void message(const QString &);
    void progress(const int);
};

} // namespace UI
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_UI_APPLICATIONS_H
