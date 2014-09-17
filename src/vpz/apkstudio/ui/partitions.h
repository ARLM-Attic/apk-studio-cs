#ifndef VPZ_APKSTUDIO_UI_PARTITIONS_H
#define VPZ_APKSTUDIO_UI_PARTITIONS_H

#include <QMessageBox>
#include <QString>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>

#include "../runtime/partition.h"
#include "../runtime/remount.h"
#include "../utility/resource.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

class Partitions : public QTreeWidget
{
    Q_OBJECT
private:
    // Function
    void initialize();
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("partitions" ,name);
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("partitions", key);
    }
    // Variable
    QString _device;
private slots:
    void __partition(const QList<Bridge::Partition> &);
    void __remount(const bool, const bool, const Bridge::Partition &);
    void __select(QTreeWidgetItem *, QTreeWidgetItem *);
public:
    // Constructor
    Partitions(const QString &device, QWidget *parent = 0)
        : QTreeWidget(parent)
    {
        this->_device = device;
        this->initialize();
    }
    // Function
    void refresh();
    void remount();
    bool selected();
    // Destructor
    ~Partitions() { }
signals:
    void partitions(const bool);
    void message(const QString &);
    void progress(const int);
};

} // namespace UI
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_UI_PARTITIONS_H
