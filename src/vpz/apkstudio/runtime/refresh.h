#ifndef VPZ_APKSTUDIO_RUNTIME_REFRESH_H
#define VPZ_APKSTUDIO_RUNTIME_REFRESH_H

#include <QList>
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

class Refresh : public QThread
{
    Q_OBJECT
public:
    // Constructor
    Refresh() { }
    // Function
    void run();
    // Destructor
    ~Refresh() { }
signals:
    void refresh(const QList<Bridge::Device> &);
};

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_RUNTIME_REFRESH_H
