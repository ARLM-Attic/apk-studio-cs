#ifndef VPZ_APKSTUDIO_UI_XMLHIGHLIGHTER_H
#define VPZ_APKSTUDIO_UI_XMLHIGHLIGHTER_H

#include <QObject>
#include <QPlainTextEdit>
#include <QTextDocument>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QColor>

namespace VPZ {
namespace APKStudio {
namespace UI {

class XMLHighlighter : public QSyntaxHighlighter
{
public:
    XMLHighlighter(QObject* parent);
    XMLHighlighter(QTextDocument* parent);
    XMLHighlighter(QPlainTextEdit* parent);
    ~XMLHighlighter();
    enum HighlightType
    {
        SyntaxChar,
        ElementName,
        Comment,
        AttributeName,
        AttributeValue,
        Error,
        Other
    };
    void initialize();
    void setHighlightColor(HighlightType type, QColor color, bool foreground = true);
    void setHighlightFormat(HighlightType type, QTextCharFormat format);
protected:
    void highlightBlock(const QString& rstrText);
    int  processDefaultText(int i, const QString& rstrText);
private:
    QTextCharFormat fmtSyntaxChar;
    QTextCharFormat fmtElementName;
    QTextCharFormat fmtComment;
    QTextCharFormat fmtAttributeName;
    QTextCharFormat fmtAttributeValue;
    QTextCharFormat fmtError;
    QTextCharFormat fmtOther;
    enum ParsingState
    {
        NoState = 0,
        ExpectElementNameOrSlash,
        ExpectElementName,
        ExpectAttributeOrEndOfElement,
        ExpectEqual,
        ExpectAttributeValue
    };
    enum BlockState
    {
        NoBlock = -1,
        InComment,
        InElement
    };
    ParsingState state;
};

} // namespace UI
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_UI_XMLHIGHLIGHTER_H
