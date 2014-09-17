#include "package.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void Package::run()
{
    // List
    QList<Bridge::Application> list;
    // Process
    QProcess disabled;
    disabled.setEnvironment(QProcess::systemEnvironment());
    disabled.setProcessChannelMode(QProcess::MergedChannels);
    // Regex
    QRegularExpression applications = QRegularExpression(QString(REGEX_APPLICATION));
    /*
     * @Disabled
     */
    // Arguments
    QStringList arguments;
    arguments << QString("-s");
    arguments << this->_device;
    arguments << QString("shell");
    arguments << QString("pm");
    arguments << QString("list");
    arguments << QString("packages");
    arguments << QString("-f");
    arguments << QString("-d");
    // Start
    disabled.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!disabled.waitForStarted()) {
        emit package(list);
        return;
    }
    // Wait (Read)
    disabled.waitForReadyRead();
    // Wait (Stop)
    if (!disabled.waitForFinished())
        disabled.kill();
    // Read
    QString output = disabled.readAll();
    QStringList lines = output.split(QRegularExpression("[\r\n]"), QString::SkipEmptyParts);
    foreach (const QString &line, lines) {
        if (line.isEmpty())
            continue;
        QRegularExpressionMatch matcher = applications.match(line);
        if (!matcher.hasMatch())
            continue;
        QString path = matcher.captured(QString("path"));
        Bridge::File file = this->ls(path);
        if (file.path.isEmpty())
            continue;
        file.path = path;
        Bridge::Application package;
        package.file = file;
        package.state = false;
        package.type = path.startsWith(QString("/system")) ? Bridge::Application::SYSTEM : Bridge::Application::USER;
        package.package = matcher.captured(QString("package"));
        list.append(package);
    }
    /*
     * @Enabled
     */
    // Process
    QProcess enabled;
    enabled.setEnvironment(QProcess::systemEnvironment());
    enabled.setProcessChannelMode(QProcess::MergedChannels);
    // Arguments
    arguments.clear();
    arguments << QString("-s");
    arguments << this->_device;
    arguments << QString("shell");
    arguments << QString("pm");
    arguments << QString("list");
    arguments << QString("packages");
    arguments << QString("-f");
    arguments << QString("-e");
    // Start
    enabled.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!enabled.waitForStarted()) {
        emit package(list);
        return;
    }
    // Wait (Read)
    enabled.waitForReadyRead();
    // Wait (Stop)
    if (!enabled.waitForFinished())
        enabled.kill();
    // Flush
    output.clear();
    lines.clear();
    // Read
    output = enabled.readAll();
    lines = output.split(QRegularExpression("[\r\n]"), QString::SkipEmptyParts);
    foreach (const QString &line, lines) {
        if (line.isEmpty())
            continue;
        QRegularExpressionMatch matcher = applications.match(line);
        if (!matcher.hasMatch())
            continue;
        QString path = matcher.captured(QString("path"));
        Bridge::File file = this->ls(path);
        if (file.path.isEmpty())
            continue;
        file.path = path;
        Bridge::Application package;
        package.file = file;
        package.state = true;
        package.type = path.startsWith(QString("/system")) ? Bridge::Application::SYSTEM : Bridge::Application::USER;
        package.package = matcher.captured(QString("package"));
        list.append(package);
    }
    // Broadcast
    emit package(list);
}

Bridge::File Package::ls(const QString &path)
{
    Bridge::File file;
    // Process
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    // Arguments
    QStringList arguments;
    arguments << QString("-s");
    arguments << this->_device;
    arguments << QString("shell");
    arguments << QString("ls");
    arguments << QString("-l");
    arguments << path;
    // Start
    process.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted())
        return file;
    // Wait (Read)
    if (!process.waitForReadyRead())
        return file;
    // Wait (Stop)
    if (!process.waitForFinished())
        process.kill();
    // Read
    QString output = process.readAll().trimmed();
    // Parse
    file = File::parse(output, QString());
    return file;
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
