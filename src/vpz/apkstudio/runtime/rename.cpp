#include "rename.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void Rename::run()
{
    // Arguments
    QStringList arguments;
    arguments << QString("-s");
    arguments << this->_device;
    arguments << QString("shell");
    if (Utility::Configuration::root()) {
        arguments << QString("su");
        arguments << QString("-c");
    }
    arguments << QString("mv");
    arguments << this->_previous;
    arguments << this->_current;
    // Process
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    // Start
    process.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit rename(false, this->_previous);
        return;
    }
    // Wait (Read)
    process.waitForReadyRead(5 * 1000);
    // Wait (Stop)
    if (!process.waitForFinished())
        process.kill();
    // Read
    QString output = process.readAll();
    if (output.trimmed().isEmpty())
        emit rename(true, this->_previous);
    else
        emit rename(false, this->_previous);
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
