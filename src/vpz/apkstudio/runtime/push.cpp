#include "push.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void Push::run()
{
    // Map
    QMap<QString, bool> map;
    if (this->_files.count() < 1) {
        emit push(map);
        return;
    }
    QRegularExpression regex(QString(REGEX_TRANSFER));
    foreach (const QString &file, this->_files) {
        // Process
        QProcess process;
        process.setEnvironment(QProcess::systemEnvironment());
        process.setProcessChannelMode(QProcess::MergedChannels);
        // Arguments
        QStringList arguments;
        arguments << QString("-s");
        arguments << this->_device;
        arguments << QString("push");
        arguments << file;
        arguments << this->_directory;
        // Start
        process.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
        // Wait (Start)
        if (!process.waitForStarted()) {
            map.insert(file, false);
            continue;
        }
        // Wait (Read)
        if (!process.waitForReadyRead()) {
            map.insert(file, false);
            continue;
        }
        // Wait (Stop)
        process.waitForFinished(-1);
        // Read
        QString output = process.readAll();
        // Parse
        bool success = false;
        QStringList lines = output.split(QRegularExpression("[\r\n]"), QString::SkipEmptyParts);
        foreach (const QString &line, lines) {
            if (line.trimmed().startsWith("Success"))
                success = true;
        }
        map.insert(file, success);
    }
    // Broadcast
    emit push(map);
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
