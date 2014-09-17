#include "highlighter.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

void Highlighter::highlightBlock(const QString &text)
{
    // Inline
    foreach (const Bridge::Highlight &highlight, this->_definitions) {
        QRegularExpression expression(highlight.regex);
        QRegularExpressionMatch matcher = expression.match(text);
        while (matcher.hasMatch()) {
            int index = matcher.capturedStart();
            int length = matcher.capturedLength();
            this->setFormat(index, length, highlight.format);
            matcher = expression.match(text, index + length);
        }
    }
    // Block-comments
    if (!this->_blockcomment.isEmpty()) {
        QTextCharFormat multiline;
        multiline.setForeground(QColor(this->_blockcomment));
        QRegularExpression begin("/\\*");
        QRegularExpression end("\\*/");
        this->setCurrentBlockState(0);
        int start = 0;
        if (this->previousBlockState() != 1)
            start = begin.match(text).capturedStart();
        while (start >= 0) {
            QRegularExpressionMatch matcher = end.match(text, start);
            int stop = matcher.capturedStart();
            int length;
            if (stop == -1) {
                this->setCurrentBlockState(1);
                length = text.length() - start;
            } else
                length = stop - start + matcher.capturedLength();
            this->setFormat(start, length, multiline);
            start = begin.match(text, start + length).capturedStart();
        }
    }
}

void Highlighter::initialize(const QString &extension)
{
    this->_blockcomment.clear();
    this->_definitions.clear();
    QFile *rules = new QFile(QString(PATH_HIGHLIGHT).append(extension).append(".xml"));
    if (rules->exists() && rules->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QXmlStreamReader xml(rules);
        while (!xml.atEnd() && !xml.hasError()) {
            QXmlStreamReader::TokenType token = xml.readNext();
            if (token == QXmlStreamReader::StartDocument)
                continue;
            if (token == QXmlStreamReader::StartElement) {
                if (xml.name() == "rules") {
                    QXmlStreamAttributes attributes = xml.attributes();
                    if (attributes.hasAttribute("blockcomment"))
                        this->_blockcomment.append(attributes.value("blockcomment"));
                    continue;
                }
                if (xml.name() == "rule")
                    this->rule(xml);
            }
        }
        rules->close();
        xml.clear();
    }
}

void Highlighter::rule(QXmlStreamReader &xml)
{
    if ((xml.tokenType() != QXmlStreamReader::StartElement) && (xml.name() == "rule"))
        return;
    QXmlStreamAttributes attributes = xml.attributes();
    if (attributes.hasAttribute("type")) {
        Bridge::Highlight highlight;
        highlight.type = attributes.value("type").toString();
        xml.readNext();
        while(!((xml.tokenType() == QXmlStreamReader::EndElement) && (xml.name() == "rule"))) {
            if (xml.tokenType() == QXmlStreamReader::StartElement) {
                if (xml.name() == "format") {
                    QXmlStreamAttributes formatting = xml.attributes();
                    if (formatting.hasAttribute("bold") && (QString::compare(formatting.value("bold").toString(), "true", Qt::CaseInsensitive) == 1))
                        highlight.format.setFontWeight(QFont::Bold);
                    highlight.format.setForeground(QColor(formatting.hasAttribute("color") ? formatting.value("color").toString() : "#000000"));
                    if (formatting.hasAttribute("italic") && (QString::compare(formatting.value("italic").toString(), "true", Qt::CaseInsensitive) == 1))
                        highlight.format.setFontItalic(true);
                } else if (xml.name() == "regex") {
                    QString regex = xml.readElementText();
                    highlight.regex = QRegularExpression(regex);
                }
            }
            xml.readNext();
        }
        this->_definitions.push_back(highlight);
    }
}

} // namespace UI
} // namespace APKStudio
} // namespace VPZ
