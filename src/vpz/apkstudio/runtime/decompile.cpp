#include "decompile.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

Decompile::Decompile(const QString &apk, const QString &location, const QString &tag)
{
    this->_apk = apk;
    this->_location = location;
    this->_tag = tag;
}

void Decompile::run()
{
    // Arguments
    QStringList arguments;
    arguments << QString("-Xms").append(QString::number(Utility::Configuration::heap())).append("m");
    arguments << QString("-jar");
    arguments << Utility::Configuration::apktool();
    arguments << QString("--force");
    if (!this->_tag.isEmpty()) {
        arguments << QString("--frame-path");
        arguments << Utility::Configuration::framework();
        arguments << QString("--frame-tag");
        arguments << QString(this->_tag);
    }
    if (Utility::Configuration::verbose())
        arguments << QString("--verbose");
    arguments << QString("--output");
    arguments << QString(this->_location);
    arguments << QString("d");
    arguments << QString(this->_apk);
    // Process
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    // Start
    process.start(QString("java"), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit decompile(this->_apk, QString());
    }
    // Wait (Read)
    process.waitForReadyRead(5 * 1000);
    // Wait (Stop)
    process.waitForFinished(-1);
    // Verify
    QString yml = QString(this->_location).append("/apktool.yml");
    QFileInfo info(yml);
    if (!info.exists() || !info.isFile()) {
        // Read
        QString output = process.readAll();
        emit Decompile::output(output);
        emit decompile(this->_apk, QString());
        return;
    } else
        // Broadcast
        emit decompile(this->_apk, info.absoluteFilePath());
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
