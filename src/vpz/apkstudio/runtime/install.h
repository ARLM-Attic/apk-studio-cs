#ifndef VPZ_APKSTUDIO_RUNTIME_INSTALL_H
#define VPZ_APKSTUDIO_RUNTIME_INSTALL_H

#include <QFileInfo>
#include <QMap>
#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QThread>

#include "../bridge/variant.h"
#include "../utility/configuration.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

class Install : public QThread
{
    Q_OBJECT
private:
    // Variable
    QString _device;
    QStringList _apks;
public:
    Install(const QString &device, const QStringList &apks)
    {
        this->_device = device;
        this->_apks = apks;
    }
    void run();
signals:
    void install(const QMap<QString, bool> &);
};

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_RUNTIME_INSTALL_H
