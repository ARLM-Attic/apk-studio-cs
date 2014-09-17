#ifndef VPZ_APKSTUDIO_RUNTIME_BUILD_H
#define VPZ_APKSTUDIO_RUNTIME_BUILD_H

#include <QMap>
#include <QObject>
#include <QProcess>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QString>
#include <QThread>

#include "../bridge/constant.h"
#include "../utility/configuration.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

class Build : public QThread
{
    Q_OBJECT
private:
    // Variable
    QString _device;
public:
    Build(const QString &device)
    {
        this->_device = device;
    }
    void run();
signals:
    void build(const QMap<QString, QString> &);
};

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_RUNTIME_INFO_H
