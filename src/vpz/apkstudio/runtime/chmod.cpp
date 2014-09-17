#include "chmod.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void CHMOD::run()
{
    // Map
    QMap<QString, bool> map;
    if (this->_files.count() < 1) {
        emit chmod(map);
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
        arguments << QString("chmod");
        if (this->_recursive)
            arguments << QString("-R"); // --recursive
        arguments << this->_mode;
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
        if (!process.waitForFinished())
            process.kill();
        // Read
        QString output = process.readAll();
        if (output.trimmed().isEmpty())
            map.insert(file, true);
        else
            map.insert(file, false);
    }
    emit chmod(map);
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
