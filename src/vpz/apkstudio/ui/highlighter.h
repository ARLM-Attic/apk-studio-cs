#ifndef VPZ_APKSTUDIO_UI_HIGHLIGHTER_H
#define VPZ_APKSTUDIO_UI_HIGHLIGHTER_H

#include <QFile>
#include <QIODevice>
#include <QObject>
#include <QRegularExpression>
#include <QSyntaxHighlighter>
#include <QString>
#include <QTextCharFormat>
#include <QVector>
#include <QXmlStreamReader>

#include "../bridge/constant.h"
#include "../bridge/variant.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT
private:
    QString _blockcomment;
    QVector<Bridge::Highlight> _definitions;
    void rule(QXmlStreamReader &);
public:
    Highlighter(QTextDocument *document = 0) : QSyntaxHighlighter(document) { }
    void highlightBlock(const QString &);
    void initialize(const QString &);
};

} // namespace UI
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_UI_HIGHLIGHTER_H
