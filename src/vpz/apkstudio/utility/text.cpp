#include "text.h"

namespace VPZ {
namespace APKStudio {
namespace Utility {

QString Text::capitalize(const QString &text, bool force)
{
    QString temporary = text;
    if (force)
        temporary = text.toLower();
    temporary[0] = temporary[0].toUpper();
    return temporary;
}

} // namespace Utility
} // namespace APKStudio
} // namespace VPZ
