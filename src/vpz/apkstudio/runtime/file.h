#ifndef VPZ_APKSTUDIO_RUNTIME_FILE_H
#define VPZ_APKSTUDIO_RUNTIME_FILE_H

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

class File : public QThread
{
    Q_OBJECT
private:
    QString _device;
    QString _path;
public:
    // Constructor
    File(const QString &device, const QString &path)
    {
        this->_device = device;
        this->_path = path;
    }
    // Function
    static Bridge::File parse(const QString &, const QString &path = QString());
    void run();
    // Destructor
    ~File() { }
signals:
    void file(const QList<Bridge::File> &);
};

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_RUNTIME_FILE_H
