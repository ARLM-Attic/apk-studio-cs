#ifndef VPZ_APKSTUDIO_RUNTIME_LOGGER_H
#define VPZ_APKSTUDIO_RUNTIME_LOGGER_H

#include <QIODevice>
#include <QMutex>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QThread>
#include <QProcess>

#include "../bridge/variant.h"
#include "../utility/configuration.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

class Logger : public QThread
{
    Q_OBJECT
private:
    // Object
    QMutex _mutex;
    QProcess *_process;
    // Variable
    QString _device;
    bool _done;
public:
    Logger(const QString &device)
    {
        this->_device = device;
        this->_done = false;
    }
    void run();
    void stop();
    ~Logger() { }
signals:
    void logcat(const QString &);
    void status(const bool);
private slots:
    void __ready();
};

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_RUNTIME_LOGGER_H
