#include "refresh.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void Refresh::run()
{
    // List
    QList<Bridge::Device> list;
    // Process
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    // Start
    process.start(Utility::Configuration::adb(), QStringList(QString("devices")), QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit refresh(list);
        return;
    }
    // Wait (Read)
    if (!process.waitForReadyRead()) {
        emit refresh(list);
        return;
    }
    // Wait (Stop)
    if (!process.waitForFinished(60 * 1000))
        process.kill();
    // Read
    QString output = process.readAll();
    QStringList lines = output.split(QRegularExpression("[\r\n]"), QString::SkipEmptyParts);
    QRegularExpression emulator = QRegularExpression(QString(REGEX_EMULATOR));
    foreach (const QString &line, lines) {
        if (line.isEmpty())
            continue;
        QStringList parts = line.split(QString("\t"));
        if (parts.count() != 2)
            continue;
        Bridge::Device device;
        device.id = parts.at(0).trimmed();
        QString status = parts.at(1).trimmed();
        if (status == QString("bootloader"))
            device.status = Bridge::Device::BOOTLOADER;
        else if (status == QString("offline"))
            device.status = Bridge::Device::OFFLINE;
        else
            device.status = Bridge::Device::ONLINE;
        if (emulator.match(device.id).hasMatch())
            device.type = Bridge::Device::EMULATOR;
        else
            device.type = Bridge::Device::DEVICE;
        list.append(device);
    }
    // Broadcast
    emit refresh(list);
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
