#include "format.h"

namespace VPZ {
namespace APKStudio {
namespace Utility {

QString Format::size(float bytes)
{
    QStringList list;
    list << "KB" << "MB" << "GB" << "TB";
    QStringListIterator iterator(list);
    QString unit("B");
    while (bytes >= 1024.0 && iterator.hasNext()) {
        unit = iterator.next();
        bytes /= 1024.0;
    }
    return QString().setNum(bytes, 'f', 2) + ' ' + unit;
}

QString Format::time(const QDateTime &date, const QString &format)
{
    return date.toString(format);
}

} // namespace Utility
} // namespace APKStudio
} // namespace VPZ
