#ifndef VPZ_APKSTUDIO_RUNTIME_DECOMPILE_H
#define VPZ_APKSTUDIO_RUNTIME_DECOMPILE_H

#include <QFileInfo>
#include <QList>
#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QThread>

#include "../utility/format.h"
#include "../utility/configuration.h"

namespace VPZ {
namespace APKStudio {
namespace Runtime {

class Decompile : public QThread
{
    Q_OBJECT
private:
    // Variable
    QString _apk;
    bool _done;
    QString _location;
    QString _tag;
public:
    // Constructor
    Decompile(const QString &, const QString &, const QString & = QString());
    // Function
    void run();
    // Destrcutor
    ~Decompile() { }
signals:
    void output(const QString &);
    void decompile(const QString &, const QString &);
};

} // namespace Runtime
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_RUNTIME_DECOMPILE_H
