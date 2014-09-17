#ifndef VPZ_APKSTUDIO_RUNTIME_MOUNT_H
#define VPZ_APKSTUDIO_RUNTIME_MOUNT_H

#include <QList>
#include <QObject>
#include <QProcess>
#include <QRegularExpression>
#include <QString>
#include <QThread>

#include "../bridge/constant.h"
#include "../bridge/variant.h"
#include "../utility/configuration.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

class Partition : public QThread
{
    Q_OBJECT
private:
    // Variable
    QString _device;
public:
    // Constructor
    Partition(const QString &device)
    {
        this->_device = device;
    }
    // Function
    void run();
    // Destructor
    ~Partition() { }
signals:
    void partition(const QList<Bridge::Partition> &);
};

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_RUNTIME_MOUNT_H
