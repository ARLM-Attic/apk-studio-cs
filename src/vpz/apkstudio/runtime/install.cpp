#include "install.h"

#include <QDebug>

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void Install::run()
{
    // Map
    QMap<QString, bool> map;
    if (this->_apks.count() < 1) {
        emit install(map);
        return;
    }
    foreach (const QString &apk, this->_apks) {
        // Verify
        QFileInfo info(apk);
        if (!info.exists() || !info.isFile() || (info.suffix() != QString("apk"))) {
            map.insert(apk, false);
            continue;
        }
        // Process
        QProcess process;
        process.setEnvironment(QProcess::systemEnvironment());
        process.setProcessChannelMode(QProcess::MergedChannels);
        // Arguments
        QStringList arguments;
        arguments << QString("-s");
        arguments << this->_device;
        arguments << QString("install");
        arguments << apk;
        // Start
        process.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
        // Wait (Start)
        if (!process.waitForStarted()) {
            map.insert(apk, false);
            continue;
        }
        // Wait (Read)
        if (!process.waitForReadyRead()) {
            map.insert(apk, false);
            continue;
        }
        // Wait (Stop)
        process.waitForFinished(-1);
        // Read
        QString output = process.readAll();
        bool success = false;
        QStringList lines = output.split(QRegularExpression("[\r\n]"), QString::SkipEmptyParts);
        foreach (const QString &line, lines) {
            if (line.trimmed().startsWith("Success"))
                success = true;
        }
        map.insert(apk, success);
    }
    // Broadcast
    emit install(map);
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
