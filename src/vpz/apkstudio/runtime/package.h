#ifndef VPZ_APKSTUDIO_RUNTIME_APPLICATION_H
#define VPZ_APKSTUDIO_RUNTIME_APPLICATION_H

#include <QFileInfo>
#include <QList>
#include <QObject>
#include <QProcess>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QString>
#include <QThread>

#include "../bridge/constant.h"
#include "../bridge/variant.h"
#include "../runtime/file.h"
#include "../utility/configuration.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

class Package : public QThread
{
    Q_OBJECT
private:
    // Function
    Bridge::File ls(const QString &);
    // Variable
    QString _device;
public:
    // Constructor
    Package(const QString &device)
    {
        this->_device = device;
    }
    // Function
    void run();
    // Destructor
    ~Package() { }
signals:
    void package(const QList<Bridge::Application> &);
};

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_RUNTIME_APPLICATION_H
