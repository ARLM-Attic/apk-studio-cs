#ifndef VPZ_APKSTUDIO_UTILITY_FORMAT_H
#define VPZ_APKSTUDIO_UTILITY_FORMAT_H

#include <QDateTime>
#include <QString>
#include <QStringList>
#include <QStringListIterator>

#include "../bridge/constant.h"

namespace VPZ {
namespace APKStudio {
namespace Utility {

class Format
{
public:
    static QString size(float bytes);
    static QString time(const QDateTime & = QDateTime::currentDateTime(), const QString & = FORMAT_TIMESTAMP);
};

} // namespace Utility
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_UTILITY_FORMAT_H
