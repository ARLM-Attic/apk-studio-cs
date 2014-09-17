#ifndef VPZ_APKSTUDIO_RUNTIME_NEW_H
#define VPZ_APKSTUDIO_RUNTIME_NEW_H

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

class New : public QThread
{
    Q_OBJECT
private:
    // Variable
    QString _device;
    QString _directory;
public:
    New(const QString &device, const QString &directory)
    {
        this->_device = device;
        this->_directory = directory;
    }
    void run();
signals:
    void new_(const bool, const QString &);
};

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_RUNTIME_NEW_H
