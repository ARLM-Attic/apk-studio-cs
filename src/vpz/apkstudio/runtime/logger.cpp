#include "logger.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

void Logger::run()
{
    /*
     * @Clear
     */
    // Arguments
    QStringList arguments;
    arguments << QString("-s");
    arguments << this->_device;
    arguments << QString("logcat");
    arguments << QString("-c");
    // Process
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    // Start
    process.start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit status(false);
        return;
    }
    // Wait (Stop)
    if (!process.waitForFinished())
        process.kill();
    /*
     * @Receive
     */
    // Arguments
    arguments.clear();
    arguments << QString("-s");
    arguments << this->_device;
    arguments << QString("logcat");
    arguments << QString("-v");
    arguments << QString("threadtime");
    // Process
    this->_process = new QProcess();
    this->_process->setEnvironment(QProcess::systemEnvironment());
    this->_process->setProcessChannelMode(QProcess::MergedChannels);
    // Execute
    this->_process->start(Utility::Configuration::adb(), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!this->_process->waitForStarted()) {
        emit status(false);
        return;
    }
    emit status(true);
    // Bind
    this->connect(this->_process, SIGNAL(readyReadStandardOutput()), this, SLOT(__ready()));
    // Wait (Read)
    if (!this->_process->waitForReadyRead()) {
        emit status(false);
        return;
    }
    while (true) {
        this->_mutex.lock();
        if (this->_done)
            break;
        this->_mutex.unlock();
        this->_process->waitForFinished(100);
    }
    this->_process->kill();
    this->_process->waitForFinished();
    // Clear
    delete this->_process;
    // Broadcast
    emit status(false);
}

void Logger::stop()
{
    this->_mutex.lock();
    this->_done = true;
    this->_mutex.unlock();
}

void Logger::__ready()
{
    QTextStream stream(this->_process);
    QString line;
    do {
        line = stream.readLine();
        emit logcat(line);
    } while (!this->_done && !line.isNull());
}

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ
