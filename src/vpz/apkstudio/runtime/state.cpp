#include "state.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void State::run()
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
    QString status = this->_state ? QString("enable") : QString("disable");
    arguments << status;
    arguments << this->_package;
    // Process
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    // Start
    process.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    // Wait (Read)
    if (!process.waitForReadyRead()) {
        emit state(false, this->_package, false);
        return;
    }
    // Wait (Stop)
    if (!process.waitForFinished())
        process.kill();
    // Read
    QString output = process.readAll();
    QStringList lines = output.split(QRegularExpression("[\r\n]"), QString::SkipEmptyParts);
    if (lines.count() != 1) {
        emit state(false, this->_package, false);
        return;
    }
    // Parse
    QString line = lines.first().trimmed();
    if (line == QString("Killed")) {
        emit state(false, this->_package, false);
        return;
    }
    QRegularExpressionMatch matcher = QRegularExpression(REGEX_STATE).match(line);
    if (!matcher.hasMatch()) {
        emit state(false, this->_package, false);
        return;
    }
    if (matcher.captured(QString("state")) == QString("enabled"))
        emit state(true, this->_package, true);
    else
        emit state(true, this->_package, false);
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
