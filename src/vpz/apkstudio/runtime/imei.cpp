#include "imei.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void IMEI::run()
{
    // Arguments
    QStringList arguments;
    arguments << QString("-s");
    arguments << this->_device;
    arguments << QString("shell");
    arguments << QString("dumpsys");
    arguments << QString("iphonesubinfo");
    // Process
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    // Start
    process.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit imei(QString());
        return;
    }
    // Wait (Read)
    if (!process.waitForReadyRead()) {
        emit imei(QString());
        return;
    }
    // Wait (Stop)
    if (!process.waitForFinished())
        process.kill();
    // Read
    QString output = process.readAll();
    QStringList lines = output.split(QRegularExpression("[\r\n]"), QString::SkipEmptyParts);
    QRegularExpression regex = QRegularExpression(QString(REGEX_IMEI));
    foreach (const QString &line, lines) {
        if (line.isEmpty() || !line.contains('='))
            continue;
        QStringList parts = line.split(regex);
        if (parts.at(0).trimmed() == QString("Device ID")) {
            emit imei(parts.at(1).trimmed());
            return;
        }
    }
    // Broadcast
    emit imei(QString());
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
