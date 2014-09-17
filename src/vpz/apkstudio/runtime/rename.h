#ifndef VPZ_APKSTUDIO_RUNTIME_RENAME_H
#define VPZ_APKSTUDIO_RUNTIME_RENAME_H

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

class Rename : public QThread
{
    Q_OBJECT
private:
    // Variable
    QString _current;
    QString _device;
    QString _previous;
public:
    Rename(const QString &device, const QString &previous, const QString &current)
    {
        this->_current = current;
        this->_device = device;
        this->_previous = previous;
    }
    void run();
signals:
    void rename(const bool, const QString &);
};

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_RUNTIME_RENAME_H
