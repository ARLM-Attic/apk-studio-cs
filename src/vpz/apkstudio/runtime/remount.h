#ifndef VPZ_APKSTUDIO_RUNTIME_REMOUNT_H
#define VPZ_APKSTUDIO_RUNTIME_REMOUNT_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <QThread>

#include "../bridge/variant.h"
#include "../utility/configuration.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

class Remount : public QThread
{
    Q_OBJECT
private:
    // Variable
    QString _device;
    Bridge::Partition _partition;
public:
    Remount(const QString &device, const Bridge::Partition partition)
    {
        this->_device = device;
        this->_partition = partition;
    }
    void run();
signals:
    void remount(const bool, const bool, const Bridge::Partition &);
};

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_RUNTIME_REMOUNT_H
