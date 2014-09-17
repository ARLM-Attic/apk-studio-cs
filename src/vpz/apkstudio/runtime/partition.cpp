#include "partition.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void Partition::run()
{
    // List
    QList<Bridge::Partition> list;
    // Process
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    // Arguments
    QStringList arguments;
    arguments << QString("-s");
    arguments << this->_device;
    arguments << QString("shell");
    if (Utility::Configuration::root()) {
        arguments << QString("su");
        arguments << QString("-c");
    }
    arguments << QString("cat");
    arguments << QString("/proc/mounts");
    // Start
    process.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit partition(list);
        return;
    }
    // Wait (Read)
    if (!process.waitForReadyRead()) {
        emit partition(list);
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
        Bridge::Partition partition;
        partition.device = parts.at(0);
        partition.flags = parts.at(3).split(',');
        partition.mount = parts.at(1);
        partition.fs = parts.at(2);
        list.append(partition);
    }
    // Broadcast
    emit partition(list);
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
