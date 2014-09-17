#include "remount.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void Remount::run()
{
    bool rw = this->_partition.flags.contains(QString("rw"));
    // Arguments
    QStringList arguments;
    arguments << QString("-s");
    arguments << this->_device;
    arguments << QString("shell");
    if (Utility::Configuration::root()) {
        arguments << QString("su");
        arguments << QString("-c");
    }
    QString mode = rw ? QString("ro") : QString("rw");
    arguments << QString("mount");
    arguments << QString("-t");
    arguments << this->_partition.fs;
    arguments << QString("-o");
    arguments << QString("remount,").append(mode);
    arguments << this->_partition.device;
    arguments << this->_partition.mount;
    // Process
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    // Start
    process.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit remount(false, rw, this->_partition);
        return;
    }
    // Wait (Stop)
    if (!process.waitForFinished())
        process.kill();
    /*
     * @Verify
     */
    // Arguments
    arguments.clear();
    arguments << QString("-s");
    arguments << this->_device;
    arguments << QString("shell");
    arguments << QString("cat");
    arguments << QString("/proc/mounts");
    // Start
    process.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit remount(false, rw, this->_partition);
        return;
    }
    // Wait (Read)
    if (!process.waitForReadyRead()) {
        emit remount(false, rw, this->_partition);
        return;
    }
    // Wait (Stop)
    if (!process.waitForFinished())
        process.kill();
    // Read
    QString output = process.readAll();
    QStringList lines = output.split(QRegularExpression("[\r\n]"), QString::SkipEmptyParts);
    QRegularExpression whitespace = QRegularExpression("\\s+");
    foreach (const QString &line, lines) {
        if (line.isEmpty())
            continue;
        QStringList parts = line.split(whitespace);
        if (parts.count() != 6)
            continue;
        if (parts.at(1) != this->_partition.mount)
            continue;
        if (parts.at(3).contains(mode))
            // Broadcast
            emit remount(true, rw, this->_partition);
        else
            // Broadcast
            emit remount(false, rw, this->_partition);
        break;
    }
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
