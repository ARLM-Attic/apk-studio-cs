#ifndef VPZ_APKSTUDIO_RUNTIME_UNINSTALL_H
#define VPZ_APKSTUDIO_RUNTIME_UNINSTALL_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <QThread>

#include "../bridge/variant.h"
#include "../utility/configuration.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

class Uninstall : public QThread
{
    Q_OBJECT
private:
    // Variable
    QString _device;
    QString _package;
public:
    Uninstall(const QString &device, const QString &package)
    {
        this->_device = device;
        this->_package = package;
    }
    void run();
signals:
    void uninstall(const bool, const QString &);
};

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_RUNTIME_UNINSTALL_H
