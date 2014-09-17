#ifndef VPZ_APKSTUDIO_RUNTIME_SCREENSHOT_H
#define VPZ_APKSTUDIO_RUNTIME_SCREENSHOT_H

#include <QDateTime>
#include <QDir>
#include <QFileInfo>
#include <QObject>
#include <QProcess>
#include <QString>
#include <QThread>

#include "../utility/format.h"
#include "../utility/configuration.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

class Screenshot : public QThread
{
    Q_OBJECT
private:
    // Variable
    QString _device;
public:
    // Constructor
    Screenshot(const QString &device)
    {
        this->_device = device;
    }
    // Function
    void run();
    // Destrcutor
    ~Screenshot() { }
signals:
    void screenshot(const QString &);
};

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_RUNTIME_SCREENSHOT_H
