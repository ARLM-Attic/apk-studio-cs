#include "screenshot.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void Screenshot::run()
{
    // Directory
    QDir directory(Utility::Configuration::screenshot());
    if (!directory.exists())
        directory.mkdir(Utility::Configuration::screenshot());
    // Initialize
    QString file = QString(this->_device).append('_').append(Utility::Format::time(QDateTime::currentDateTime(), QString("yyyy-MM-dd_hh_mm_ss"))).append(".png");
    QStringList arguments;
    /*
     * @Capture
     */
    // Process
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    // Arguments
    arguments << QString("-s");
    arguments << this->_device;
    arguments << QString("shell");
    arguments << QString("screencap");
    arguments << QString("-p");
    arguments << QString(Utility::Configuration::screenshot(true)).append('/').append(file);
    // Start
    process.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit screenshot(QString());
        return;
    }
    // Wait (Stop)
    if (!process.waitForFinished(60 * 1000))
        process.kill();
    /*
     * @Pull
     */
    // Arguments
    arguments.clear();
    arguments << QString("-s");
    arguments << this->_device;
    arguments << QString("pull");
    arguments << QString(Utility::Configuration::screenshot(true)).append('/').append(file);
    arguments << Utility::Configuration::screenshot();
    // Start
    process.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit screenshot(QString());
        return;
    }
    // Wait (Stop)
    if (!process.waitForFinished(60 * 1000))
        process.kill();
    /*
     * @Remove
     */
    // Arguments
    arguments.clear();
    arguments << QString("-s");
    arguments << this->_device;
    arguments << QString("shell");
    arguments << QString("rm");
    arguments << QString(Utility::Configuration::screenshot(true)).append('/').append(file);
    // Start
    process.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit screenshot(QString());
        return;
    }
    // Wait (Stop)
    if (!process.waitForFinished(60 * 1000))
        process.kill();
    // Broadcast
    QFileInfo info(QString(Utility::Configuration::screenshot()).append('/').append(file));
    if (info.exists() && info.isFile())
        emit screenshot(info.absoluteFilePath());
    else
        emit screenshot(QString());
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
