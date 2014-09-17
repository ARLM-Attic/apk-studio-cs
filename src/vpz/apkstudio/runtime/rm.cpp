#include "rm.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void RM::run()
{
    // Map
    QMap<QString, bool> map;
    if (this->_files.count() < 1) {
        emit rm(map);
        return;
    }
    foreach (const QString &file, this->_files) {
        // Arguments
        QStringList arguments;
        arguments << QString("-s");
        arguments << this->_device;
        arguments << QString("shell");
        if (Utility::Configuration::root()) {
            arguments << QString("su");
            arguments << QString("-c");
        }
        arguments << QString("rm");
        if (this->_recursive)
            arguments << QString("-R"); // --recursive
        arguments << file;
        // Process
        QProcess process;
        process.setEnvironment(QProcess::systemEnvironment());
        process.setProcessChannelMode(QProcess::MergedChannels);
        // Start
        process.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
        // Wait (Start)
        if (!process.waitForStarted()) {
            map.insert(file, false);
            continue;
        }
        // Wait (Read)
        process.waitForReadyRead(5 * 1000);
        // Wait (Stop)
        if (!process.waitForFinished(60 * 1000))
            process.kill();
        // Read
        QString output = process.readAll();
        if (output.trimmed().isEmpty())
            map.insert(file, true);
        else
            map.insert(file, false);
    }
    emit rm(map);
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
