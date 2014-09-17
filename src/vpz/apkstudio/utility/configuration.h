#ifndef VPZ_APKSTUDIO_UTILITY_CONFIGURATION_H
#define VPZ_APKSTUDIO_UTILITY_CONFIGURATION_H

#include <QApplication>
#include <QDir>
#include <QSettings>
#include <QString>
#include <QVariant>

#include "../bridge/constant.h"

namespace VPZ {
namespace APKStudio {
namespace Utility {

class Configuration
{
public:
    static QString adb()
    {
#ifdef Q_OS_WIN
        return apkstudio().append("/adb/adb.exe");
#else
        return apkstudio().append("/adb/adb");
#endif
    }
    static QString apktool()
    {
        return apkstudio().append("/apktool/apktool.jar");
    }
    static QString apkstudio()
    {
        return get(PREFERENCE_BINARIES, QVariant(QString(QApplication::applicationDirPath()).append("/binaries"))).toString();
    }
    static void apkstudio(const QString &path)
    {
        return set(PREFERENCE_BINARIES, QVariant(path));
    }
    static QString certificate()
    {
        return apkstudio().append("/signapk/testkey.x509.pem");
    }
    static QString framework()
    {
        return QDir::homePath().append("/apktool/framework");
    }
    static QVariant get(const QString &key, const QVariant &fallback = QVariant())
    {
        QSettings settings;
        return settings.value(key, fallback);
    }
    static int heap()
    {
        return get(PREFERENCE_HEAP, QVariant(PREFERENCE_HEAP_DEFAULT)).toInt();
    }
    static void heap(int heap)
    {
        set(PREFERENCE_HEAP, QVariant(heap));
    }
    static QString key()
    {
        return apkstudio().append("/signapk/testkey.pk8");
    }
    static QString log()
    {
        return apkstudio().append("/log");
    }
    static bool root()
    {
        return get(PREFERENCE_ROOT, QVariant(false)).toBool();
    }
    static void root(const bool enable)
    {
        set(PREFERENCE_ROOT, QVariant(enable));
    }
    static QString screenshot(bool device = false)
    {
        if (device)
            return QString("/mnt/sdcard");
        else
            return apkstudio().append("/screenshot");
    }
    static void set(const QString &key, const QVariant &value)
    {
        QSettings settings;
        settings.setValue(key, value);
    }
    static QString signapk()
    {
        return apkstudio().append("/signapk/signapk.jar");
    }
    static void sync()
    {
        QSettings settings;
        settings.sync();
    }
    static QString text()
    {
#ifdef Q_OS_WIN
        return get(PREFERENCE_TEXT, QVariant(QString("notepad.exe"))).toString();
#else
        return get(PREFERENCE_TEXT, QVariant(QString("gedit"))).toString();
#endif
    }
    static void text(const QString &editor)
    {
        set(PREFERENCE_TEXT, QVariant(editor));
    }
    static bool verbose()
    {
        return get(PREFERENCE_VERBOSE, QVariant(false)).toBool();
    }
    static void verbose(const bool enable)
    {
        set(PREFERENCE_VERBOSE, QVariant(enable));
    }
    static QString zipalign()
    {
#ifdef Q_OS_WIN
        return apkstudio().append("/zipalign/zipalign.exe");
#else
        return apkstudio().append("/zipalign/zipalign");
#endif
    }
};

} // namespace Utility
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_UTILITY_CONFIGURATION_H
