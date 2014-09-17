#ifndef VPZ_APKSTUDIO_BRIDGE_RESOURCE_H
#define VPZ_APKSTUDIO_BRIDGE_RESOURCE_H

#include <QApplication>
#include <QStandardPaths>
#include <QString>
#include <QIcon>

#include "../bridge/constant.h"

namespace VPZ {
namespace APKStudio {
namespace Utility {

class Resource
{
public:
    static QIcon icon(const char *context, const char *name)
    {
        QString path(PATH_ICON);
        path.append(context);
        path.append('/');
        path.append(name);
        path.append(".png");
        return QIcon(path);
    }
    static const QString root()
    {
        return QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    }
    static QString text(const char *context, const char *key)
    {
        return QApplication::translate(context, key);
    }
};

} // namespace Utility
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_BRIDGE_RESOURCE_H
