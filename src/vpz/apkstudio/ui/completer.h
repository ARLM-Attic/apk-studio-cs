#ifndef VPZ_APKSTUDIO_UI_COMPLETER_H
#define VPZ_APKSTUDIO_UI_COMPLETER_H

#include <QCompleter>
#include <QFile>
#include <QIcon>
#include <QIODevice>
#include <QObject>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QString>
#include <QWidget>
#include <QXmlStreamReader>

#include "../bridge/constant.h"
#include "../utility/resource.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

class Completer : public QCompleter
{
    Q_OBJECT
private:
    // Model
    QStandardItemModel *_definitions;
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("completion" ,name);
    }
public:
    explicit Completer(QWidget * = 0);
    void initialize(const QString &);
    void completion(QXmlStreamReader &, const bool = false);
};

} // namespace UI
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_UI_COMPLETER_H
