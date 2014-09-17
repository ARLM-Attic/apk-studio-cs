#include "new.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void New::run()
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
    arguments << QString("mkdir");
    arguments << this->_directory;
    // Process
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    // Start
    process.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit new_(false, this->_directory);
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
        emit new_(true, this->_directory);
    else
        emit new_(false, this->_directory);
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
