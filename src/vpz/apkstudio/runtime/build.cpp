#include "build.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void Build::run()
{
    // Map
    QMap<QString, QString> list;
    // Arguments
    QStringList arguments;
    arguments << QString("-s");
    arguments << this->_device;
    arguments << QString("shell");
    arguments << QString("sh");
    arguments << QString("-c");
    arguments << QString("getprop");
    // Process
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    // Start
    process.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit build(list);
        return;
    }
    // Wait (Read)
    if (!process.waitForReadyRead()) {
        emit build(list);
        return;
    }
    // Wait (Stop)
    if (!process.waitForFinished())
        process.kill();
    // Read
    QString output = process.readAll();
    QStringList lines = output.split(QRegularExpression("[\r\n]"), QString::SkipEmptyParts);
    QRegularExpression regex = QRegularExpression(QString(REGEX_GETPROP));
    foreach (const QString &line, lines) {
        if (line.isEmpty() || line.startsWith('#'))
            continue;
        QRegularExpressionMatch matcher = regex.match(line);
        if (!matcher.hasMatch())
            continue;
        QString key = matcher.captured(QString("key"));
        QString value = matcher.captured(QString("value"));
        list.insert(key.trimmed(), value.trimmed());
    }
    // Broadcast
    emit build(list);
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
