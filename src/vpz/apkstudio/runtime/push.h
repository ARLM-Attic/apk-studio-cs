#ifndef VPZ_APKSTUDIO_RUNTIME_PUSH_H
#define VPZ_APKSTUDIO_RUNTIME_PUSH_H

#include <QMap>
#include <QObject>
#include <QProcess>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QString>
#include <QStringList>
#include <QThread>

#include "../bridge/constant.h"
#include "../bridge/variant.h"
#include "../utility/configuration.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

class Push : public QThread
{
    Q_OBJECT
private:
    // Variable
    QString _device;
    QString _directory;
    QStringList _files;
public:
    Push(const QString &device, const QStringList &files, const QString &directory)
    {
        this->_device = device;
        this->_directory = directory;
        this->_files = files;
    }
    void run();
signals:
    void push(const QMap<QString, bool> &);
};

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_RUNTIME_PUSH_H
