#ifndef VPZ_APKSTUDIO_RUNTIME_ADB_H
#define VPZ_APKSTUDIO_RUNTIME_ADB_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <QThread>

#include "../bridge/constant.h"
#include "../utility/configuration.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

class ADB : public QThread
{
    Q_OBJECT
private:
    int _command;
public:
    // Constructor
    ADB(const int command)
    {
        this->_command = command;
    }
    // Enum
    enum Command {
        RESTART = 0,
        START,
        STOP
    };
    // Function
    void run();
    // Destrcutor
    ~ADB() { }
signals:
    void adb(const int);
};

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_RUNTIME_ADB_H
