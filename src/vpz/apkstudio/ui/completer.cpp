#include "completer.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

Completer::Completer(QWidget *parent) :
    QCompleter(parent)
{
    this->_definitions = new QStandardItemModel();
    this->setCaseSensitivity(Qt::CaseInsensitive);
    this->setCompletionMode(QCompleter::PopupCompletion);
    this->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    this->setModel(this->_definitions);
    this->setWidget(parent);
    this->setWrapAround(false);
}

void Completer::initialize(const QString &extension)
{
    this->_definitions->clear();
    QFile *rules = new QFile(QString(PATH_COMPLETION).append(extension).append(".xml"));
    if (rules->exists() && rules->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QXmlStreamReader xml(rules);
        while (!xml.atEnd() && !xml.hasError()) {
            QXmlStreamReader::TokenType token = xml.readNext();
            if (token == QXmlStreamReader::StartDocument)
                continue;
            if (token == QXmlStreamReader::StartElement) {
                if (xml.name() == "completions")
                    continue;
                if (xml.name() == "completion")
                    this->completion(xml, (extension == QString("smali")));
            }
        }
    }
}

void Completer::completion(QXmlStreamReader &xml, const bool extract)
{
    if ((xml.tokenType() != QXmlStreamReader::StartElement) && (xml.name() == QString("completion")))
        return;
    QStandardItem *item = new QStandardItem();
    QXmlStreamAttributes attributes = xml.attributes();
    QString label = attributes.value("label").toString();
    QString tooltip = xml.readElementText();
    item->setIcon(icon(attributes.value("type").toString().toStdString().c_str()));
    if (extract && label.contains(' ')) {
        QString keyword = label.split(' ').at(0);
        QString howto = QString("[<strong>Usage:</strong> <i>%0</i>]<br/><br/>").arg(label);
        item->setText(keyword);
        item->setToolTip(QString(tooltip).prepend(howto));
    } else {
        item->setText(label);
        item->setToolTip(tooltip);
    }
    this->_definitions->appendRow(item);
}

} // namespace UI
} // namespace APKStudio
} // namespace VPZ
