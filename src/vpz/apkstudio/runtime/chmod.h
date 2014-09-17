#ifndef VPZ_APKSTUDIO_RUNTIME_CHMOD_H
#define VPZ_APKSTUDIO_RUNTIME_CHMOD_H

#include <QObject>
#include <QProcess>
#include <QRegularExpression>
#include <QString>
#include <QThread>

#include "../bridge/constant.h"
#include "../utility/configuration.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

class CHMOD : public QThread
{
    Q_OBJECT
private:
    // Variable
    QString _device;
    QStringList _files;
    QString _mode;
    bool _recursive;
public:
    CHMOD(const QString &device, const QStringList &files, const QString mode, bool recursive = false)
    {
        this->_device = device;
        this->_files = files;
        this->_mode = mode;
        this->_recursive = recursive;
    }
    void run();
signals:
    void chmod(const QMap<QString, bool> &);
};

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_RUNTIME_CHMOD_H
