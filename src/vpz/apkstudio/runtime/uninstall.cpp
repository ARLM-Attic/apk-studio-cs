#include "uninstall.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void Uninstall::run()
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
    arguments << QString("pm");
    arguments << QString("uninstall");
    arguments << this->_package;
    // Process
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    // Start
    process.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit uninstall(false, this->_package);
        return;
    }
    // Wait (Read)
    if (!process.waitForReadyRead()) {
        emit uninstall(false, this->_package);
        return;
    }
    // Wait (Stop)
    process.waitForFinished(-1);
    // Read
    QString output = process.readAll();
    QStringList lines = output.split(QRegularExpression("[\r\n]"), QString::SkipEmptyParts);
    if (lines.count() != 1) {
        emit uninstall(false, this->_package);
        return;
    }
    // Parse
    QString line = lines.first().trimmed();
    // Broadcast
    emit uninstall(line == QString("Success"), this->_package);
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
