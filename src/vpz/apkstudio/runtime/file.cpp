#include "file.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void File::run()
{
    // List
    QList<Bridge::File> list;
    // Process
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    // Arguments
    bool root = Utility::Configuration::root();
    QStringList arguments;
    arguments << QString("-s");
    arguments << this->_device;
    arguments << QString("shell");
    if (root) {
        arguments << QString("su");
        arguments << QString("-c");
    }
    arguments << QString("ls");
    arguments << QString("-l");
    QString path;
    if (root && this->_path.contains(QRegularExpression(QString("\\s")))) {
        path.append('\\');
        path.append('"');
        path.append(this->_path);
        path.append('\\');
        path.append('"');
    } else
        path.append(this->_path);
    arguments << path;
    // Start
    process.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit file(list);
        return;
    }
    // Wait (Read)
    if (!process.waitForReadyRead()) {
        emit file(list);
        return;
    }
    // Wait (Stop)
    if (!process.waitForFinished())
        process.kill();
    // Read
    QString output = process.readAll();
    QStringList lines = output.split(QRegularExpression("[\r\n]"), QString::SkipEmptyParts);
    if (lines.count() < 1) {
        emit file(list);
        return;
    }
    foreach (const QString &line, lines) {
        if (line.isEmpty())
            continue;
        Bridge::File file = File::parse(line, this->_path);
        if (!file.path.isEmpty())
            list.append(file);
    }
    // Broadcast
    emit file(list);
}

Bridge::File File::parse(const QString &line, const QString &parent)
{
    Bridge::File file;
    QRegularExpression ls = QRegularExpression(QString(REGEX_LS));
    QRegularExpressionMatch matcher = ls.match(line);
    if (!matcher.hasMatch())
        return file;
    file.date = matcher.captured(QString("date"));
    file.group = matcher.captured(QString("group"));
    file.name = matcher.captured(QString("name"));
    file.owner = matcher.captured(QString("owner"));
    QString permission = matcher.captured(QString("permission")).trimmed();
    file.permission.display = permission;
    file.permission.owner.execute = (permission[3] == 'x');
    file.permission.owner.read = (permission[1] == 'r');
    file.permission.owner.write = (permission[2] == 'w');
    file.permission.group.execute = (permission[6] == 'x');
    file.permission.group.read = (permission[4] == 'r');
    file.permission.group.write = (permission[5] == 'w');
    file.permission.world.execute = (permission[9] == 'x');
    file.permission.world.read = (permission[7] == 'r');
    file.permission.world.write = (permission[8] == 'w');
    file.size = matcher.captured(QString("size")).toInt();
    file.time = matcher.captured(QString("time"));
    const QChar first = permission[0];
    if (first == '-')
        file.type = Bridge::File::FILE;
    else if (first == 'b')
        file.type = Bridge::File::BLOCK;
    else if (first == 'c')
        file.type = Bridge::File::CHARACTER;
    else if (first == 'd')
        file.type = Bridge::File::DIRECTORY;
    else if (first == 'l')
        file.type = Bridge::File::SYMLINK;
    else if (first == 'p')
        file.type = Bridge::File::PIPE;
    else if (first == 's')
        file.type = Bridge::File::SOCKET;
    else
        file.type = Bridge::File::OTHER;
    if (file.type == Bridge::File::SYMLINK) {
        QStringList parts = file.name.split(QRegularExpression("\\s->\\s"));
        if (parts.count() == 2) {
            file.link = parts.at(1);
            file.name = parts.at(0);
            QStringList path = file.link.split('/');
            if (path.length() == 1)
                file.type = (path.at(0) == QString("..")) ? Bridge::File::SYMLINK_DIRECTORY : Bridge::File::SYMLINK_FILE;
            else
                file.type = Bridge::File::SYMLINK_DIRECTORY;
        }
    }
    file.path.append(parent);
    if (!file.path.endsWith(QString('/')))
        file.path.append('/');
    if ((file.type == Bridge::File::SYMLINK_DIRECTORY) || (file.type == Bridge::File::SYMLINK_FILE)) {
        file.path.clear();
        file.path.append(file.link);
        file.link.prepend("-> ");
    } else
        file.path.append(file.name);
    return file;
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
