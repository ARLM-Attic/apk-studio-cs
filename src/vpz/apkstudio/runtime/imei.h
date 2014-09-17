#ifndef VPZ_APKSTUDIO_RUNTIME_IMEI_H
#define VPZ_APKSTUDIO_RUNTIME_IMEI_H

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

class IMEI : public QThread
{
    Q_OBJECT
private:
    // Variable
    QString _device;
public:
    IMEI(const QString &device)
    {
        this->_device = device;
    }
    void run();
signals:
    void imei(const QString &);
};

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_RUNTIME_IMEI_H
