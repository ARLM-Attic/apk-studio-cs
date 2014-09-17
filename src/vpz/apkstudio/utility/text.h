#ifndef VPZ_APKSTUDIO_UTILITY_TEXT_H
#define VPZ_APKSTUDIO_UTILITY_TEXT_H

#include <QString>

namespace VPZ {
namespace APKStudio {
namespace Utility {

class Text
{
public:
    static QString capitalize(const QString &text, bool force = false);
};

} // namespace Utility
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_UTILITY_TEXT_H
