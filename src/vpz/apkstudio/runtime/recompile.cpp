#include "recompile.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void Recompile::run()
{
    /*
     * @Initialize
     */
    // Directory
    QDir directory(this->_dir);
    if (!directory.exists()) {
        emit output(text("failure_directory").arg(directory.absolutePath()));
        emit recompile(this->_dir, QString());
        return;
    }
    // File
    QFileInfo apksigned(directory.absolutePath().append("/build/signedapk.apk"));
    QFileInfo rebuilt(directory.absolutePath().append("/build/rebuilt.apk"));
    QFileInfo recompiled(directory.absolutePath().append("/build/recompiled.apk"));
    QFileInfo zipaligned(directory.absolutePath().append("/build/zipaligned.apk"));
    /*
     * @APKTool
     */
    // Arguments
    QStringList recompile;
    recompile << QString("-Xms").append(QString::number(Utility::Configuration::heap())).append("m");
    recompile << QString("-jar");
    recompile << Utility::Configuration::apktool();
    recompile << QString("--force");
    if (Utility::Configuration::verbose())
        recompile << QString("--verbose");
    recompile << QString("--output");
    recompile << QString(recompiled.absoluteFilePath());
    recompile << QString("b");
    recompile << QString(directory.absolutePath());
    // Process
    QProcess apktool;
    apktool.setEnvironment(QProcess::systemEnvironment());
    apktool.setProcessChannelMode(QProcess::MergedChannels);
    // Start
    apktool.start(QString("java"), recompile, QIODevice::ReadOnly);
    // Wait (Start)
    if (!apktool.waitForStarted()) {
        emit Recompile::recompile(this->_dir, QString());
        return;
    }
    // Wait (Read)
    apktool.waitForReadyRead(5 * 1000);
    // Wait (Stop)
    apktool.waitForFinished(-1);
    // Verify
    if (!recompiled.exists() || !recompiled.isFile()) {
        // Read
        QString output = apktool.readAll();
        emit Recompile::output(output);
        emit Recompile::recompile(this->_dir, QString());
        return;
    }
    /*
     * @Sign
     */
    // Arguments
    QStringList sign;
    sign << QString("-Xms").append(QString::number(Utility::Configuration::heap())).append("m");
    sign << QString("-jar");
    sign << Utility::Configuration::signapk();
    sign << QString("-w");
    sign << Utility::Configuration::certificate();
    sign << Utility::Configuration::key();
    sign << recompiled.absoluteFilePath();
    sign << apksigned.absoluteFilePath();
    // Process
    QProcess signapk;
    signapk.setEnvironment(QProcess::systemEnvironment());
    signapk.setProcessChannelMode(QProcess::MergedChannels);
    // Start
    signapk.start(QString("java"), sign, QIODevice::ReadOnly);
    // Wait (Start)
    if (!signapk.waitForStarted()) {
        emit Recompile::recompile(this->_dir, QString());
        return;
    }
    // Wait (Read)
    signapk.waitForReadyRead(5 * 1000);
    // Wait (Stop)
    signapk.waitForFinished(-1);
    // Verify
    if (!apksigned.exists() || !apksigned.isFile()) {
        // Read
        QString output = signapk.readAll();
        emit Recompile::output(output);
        emit Recompile::recompile(this->_dir, QString());
        return;
    }
    /*
     * @Align
     */
    // Arguments
    QStringList align;
    align << QString("-f");
    if (Utility::Configuration::verbose())
        align << QString("-v");
    align << QString("4");
    align << apksigned.absoluteFilePath();
    align << zipaligned.absoluteFilePath();
    // Process
    QProcess zipalign;
    zipalign.setEnvironment(QProcess::systemEnvironment());
    zipalign.setProcessChannelMode(QProcess::MergedChannels);
    // Start
    zipalign.start(Utility::Configuration::zipalign(), align, QIODevice::ReadOnly);
    // Wait (Start)
    if (!zipalign.waitForStarted()) {
        emit Recompile::recompile(this->_dir, QString());
        return;
    }
    // Wait (Read)
    zipalign.waitForReadyRead(5 * 1000);
    // Wait (Stop)
    zipalign.waitForFinished(-1);
    // Verify
    if (!zipaligned.exists() || !zipaligned.isFile()) {
        // Read
        QString output = zipalign.readAll();
        emit Recompile::output(output);
        emit Recompile::recompile(this->_dir, QString());
        return;
    }
    if (rebuilt.exists())
        QFile(rebuilt.absoluteFilePath()).remove();
    // Verify
    if (QFile(zipaligned.absoluteFilePath()).rename(rebuilt.absoluteFilePath())) {
        QFile(recompiled.absoluteFilePath()).remove();
        QFile(apksigned.absoluteFilePath()).remove();
        QFile(zipaligned.absoluteFilePath()).remove();
        emit Recompile::recompile(this->_dir, directory.absolutePath());
    } else
        emit Recompile::recompile(this->_dir, QString());
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
