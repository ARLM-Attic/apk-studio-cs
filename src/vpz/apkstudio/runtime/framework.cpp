#include "framework.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void Framework::run()
{
    // Process
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    // Arguments
    QStringList arguments;
    arguments << QString("-Xms").append(QString::number(Utility::Configuration::heap())).append("m");
    arguments << QString("-jar");
    arguments << Utility::Configuration::apktool();
    arguments << QString("--force");
    arguments << QString("--frame-path");
    arguments << Utility::Configuration::framework();
    arguments << QString("--frame-tag");
    arguments << QString(this->_tag);
    arguments << QString("--verbose");
    arguments << QString("if");
    arguments << QString(this->_path);
    // Start
    process.start(QString("java"), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit framework(QString());
        return;
    }
    // Wait (Read)
    if (!process.waitForReadyRead()) {
        emit framework(QString());
        return;
    }
    // Wait (Stop)
    if (!process.waitForFinished(2 * 60 * 1000))
        process.kill();
    // Read
    QString output = process.readAll();
    QStringList lines = output.split(QRegularExpression("[\r\n]"), QString::SkipEmptyParts);
    if (lines.count() < 1) {
        emit framework(QString());
        return;
    }
    foreach (const QString &line, lines) {
        if (line.startsWith(QString("INFO: Framework installed to:")) && line.endsWith(QString(".apk"))) {
            QFileInfo file(line.section(':', 2).trimmed());
            if (file.exists() && file.isFile()) {
                emit framework(file.absoluteFilePath());
                return;
            }
        }
    }
    // Broadcast
    emit framework(QString(""));
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
