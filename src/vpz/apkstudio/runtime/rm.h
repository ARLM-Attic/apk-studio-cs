#ifndef VPZ_APKSTUDIO_RUNTIME_RM_H
#define VPZ_APKSTUDIO_RUNTIME_RM_H

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

class RM : public QThread
{
    Q_OBJECT
private:
    // Variable
    QString _device;
    QStringList _files;
    bool _recursive;
public:
    RM(const QString &device, const QStringList &files, bool recursive = false)
    {
        this->_device = device;
        this->_files = files;
        this->_recursive = recursive;
    }
    void run();
signals:
    void rm(const QMap<QString, bool> &);
};

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_RUNTIME_CHMOD_H
