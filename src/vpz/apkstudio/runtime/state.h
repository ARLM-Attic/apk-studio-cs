#ifndef VPZ_APKSTUDIO_RUNTIME_ENABLE_H
#define VPZ_APKSTUDIO_RUNTIME_ENABLE_H

#include <QObject>
#include <QProcess>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QString>
#include <QThread>

#include "../bridge/constant.h"
#include "../bridge/variant.h"
#include "../utility/configuration.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

class State : public QThread
{
    Q_OBJECT
private:
    // Variable
    QString _device;
    QString _package;
    bool _state;
public:
    State(const QString &device, const QString& package, const bool state)
    {
        this->_device = device;
        this->_package = package;
        this->_state = state;
    }
    void run();
signals:
    void state(const bool, const QString &, const bool);
};

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_RUNTIME_ENABLE_H
