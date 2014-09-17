#include "adb.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void ADB::run()
{
    // Process
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    // Start
    switch (this->_command) {
    case START:
        process.start(Utility::Configuration::adb(), QStringList(QString("start-server")), QIODevice::ReadOnly);
        break;
    case RESTART:
    case STOP:
        process.start(Utility::Configuration::adb(), QStringList(QString("kill-server")), QIODevice::ReadOnly);
    default:
        break;
    }
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit adb(0);
        return;
    }
    // Wait (Stop)
    if (!process.waitForFinished())
        process.kill();
    // Restart
    if (this->_command == RESTART) {
        // Start
        process.start(Utility::Configuration::adb(), QStringList(QString("start-server")), QIODevice::ReadOnly);
        // Wait (Start)
        if (!process.waitForStarted()) {
            emit adb(0);
            return;
        }
        // Wait (Stop)
        if (!process.waitForFinished())
            process.kill();
    }
    // Broadcast
    emit adb(this->_command);
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
