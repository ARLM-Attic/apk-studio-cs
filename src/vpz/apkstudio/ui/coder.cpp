#include "coder.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

Coder::Coder(QWidget *parent) :
    QPlainTextEdit(parent)
{
    // Font
    QFont font;
    font.setFamily("Source Code Pro");
    font.setFixedPitch(true);
    font.setPointSize(10);
    font.setStyleHint(QFont::Monospace);
    this->setFont(font);
    // Menu
    this->_menu = new QMenu(this);
    // Action
    this->_close = new QAction(icon("close"), text("label_close"), this);
    this->_copy = new QAction(icon("copy"), text("label_copy"), this);
    this->_cut = new QAction(icon("cut"), text("label_cut"), this);
    this->_paste = new QAction(icon("paste"), text("label_paste"), this);
    this->_save = new QAction(icon("save"), text("label_save"), this);
    this->_select_all = new QAction(icon("select_all"), text("label_select_all"), this);
    // Tabs
    QFontMetrics metrics(font);
    this->setTabStopWidth(4 * metrics.width(' '));
    // Color
    QPalette palette;
    palette.setColor(QPalette::Highlight, QColor(EDITOR_SELECTION));
    palette.setColor(QPalette::HighlightedText, QColor("#FFFFFF"));
    palette.setColor(QPalette::Active, QPalette::Base, QColor(EDITOR_BACKGROUND));
    palette.setColor(QPalette::Inactive, QPalette::Base, QColor(EDITOR_BACKGROUND));
    palette.setColor(QPalette::Text, QColor(EDITOR_FOREGROUND));
    this->setPalette(palette);
    // Text Wrap
    this->setWordWrapMode(QTextOption::NoWrap);
    // Line Numbers
    this->_liner = new Liner(this);
    this->connect(this, SIGNAL(blockCountChanged(const int)), this, SLOT(updateLinerAreaWidth(const int)));
    this->connect(this, SIGNAL(updateRequest(const QRect &, const int)), this, SLOT(updateLinerArea(const QRect, const int)));
    this->connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlight()));
    this->updateLinerAreaWidth(0);
    this->highlight();
    // Completer
    this->_completer = new Completer(this);
    this->connect(this->_completer, SIGNAL(activated(const QString &)), this, SLOT(complete(const QString &)));
    /*
     * @Prepare
     */
    // Widget
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    /*
     * @Bind
     */
    // Action
    this->connect(this->_close, SIGNAL(triggered()), this, SLOT(__close()));
    this->connect(this->_copy, SIGNAL(triggered()), this, SLOT(__copy()));
    this->connect(this->_cut, SIGNAL(triggered()), this, SLOT(__cut()));
    this->connect(this->_paste, SIGNAL(triggered()), this, SLOT(__paste()));
    this->connect(this->_save, SIGNAL(triggered()), this, SLOT(__save()));
    this->connect(this->_select_all, SIGNAL(triggered()), this, SLOT(__select_all()));
    // Widget
    this->connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(__menu(const QPoint &)));
    /*
     * @Inflate
     */
    // Menu
    this->_menu->addAction(this->_select_all);
    this->_menu->addSeparator();
    this->_menu->addAction(this->_cut);
    this->_menu->addAction(this->_copy);
    this->_menu->addAction(this->_paste);
    this->_menu->addSeparator();
    this->_menu->addAction(this->_save);
    this->_menu->addAction(this->_close);
}

void Coder::focusInEvent(QFocusEvent *event)
{
    if (this->_completer)
        this->_completer->setWidget(this);
    // Cursor
    QTextCursor cursor = this->textCursor();
    int line = cursor.blockNumber() + 1;
    int column = cursor.columnNumber() + 1;
    emit changed(line, column);
    // Cursor
    QPlainTextEdit::focusInEvent(event);
}

void Coder::highlight()
{
    // Update
    QTextCursor cursor = this->textCursor();
    int line = cursor.blockNumber() + 1;
    int column = cursor.columnNumber() + 1;
    emit changed(line, column);
    // Completion
    QList<QTextEdit::ExtraSelection> selections;
    if (!this->isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        QColor Color = QColor(EDITOR_HIGHLIGHT);
        selection.format.setBackground(Color);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        selections.append(selection);
    }
    this->setExtraSelections(selections);
}

void Coder::complete(const QString& completion)
{
    if (this->_completer->widget() != this)
        return;
    QTextCursor cursor = textCursor();
    int extra = completion.length() - this->_completer->completionPrefix().length();
    cursor.movePosition(QTextCursor::Left);
    cursor.movePosition(QTextCursor::EndOfWord);
    cursor.insertText(completion.right(extra));
    this->setTextCursor(cursor);
}

QString Coder::cursored()
{
    QTextCursor cursor = this->textCursor();
    cursor.select(QTextCursor::WordUnderCursor);
    return cursor.selectedText();
}

void Coder::keyPressEvent(QKeyEvent *event)
{
    bool backward = false;
    bool override = false;
    QString text = event->text();
    switch (event->key()) {
    case Qt::Key_Apostrophe:
        backward = true;
        override = true;
        text = "''";
        break;
    case Qt::Key_Backtab:
        if (this->_completer->popup()->isVisible()) {
            event->ignore();
            return;
        }
        break;
    case Qt::Key_BraceLeft:
        backward = true;
        override = true;
        text = "{}";
        break;
    case Qt::Key_BracketLeft:
        backward = true;
        override = true;
        text = "[]";
        break;
    case Qt::Key_Enter:
        if (this->_completer->popup()->isVisible()) {
            event->ignore();
            return;
        }
        break;
    case Qt::Key_Escape:
        if (this->_completer->popup()->isVisible()) {
            event->ignore();
            return;
        }
        break;
    case Qt::Key_ParenLeft:
        backward = true;
        override = true;
        text = "()";
        break;
    case Qt::Key_QuoteDbl:
        backward = true;
        override = true;
        text = "\"\"";
        break;
    case Qt::Key_Return:
        if (this->_completer->popup()->isVisible()) {
            event->ignore();
            return;
        } /* else {
            override = true;
            QTextCursor cursor = this->textCursor();
            QString line = cursor.block().text();
            QString whitespace = line.replace(QString("[^\\s+]*"), QString(""));
            cursor.movePosition(QTextCursor::Left);
            cursor.movePosition(QTextCursor::EndOfWord);
            cursor.insertText(QString("\n").append(whitespace).append("    "));
            return;
        } */
        break;
    case Qt::Key_Tab:
        if (this->_completer->popup()->isVisible()) {
            event->ignore();
            return;
        } else {
            override = true;
            text = "    ";
        }
        break;
    default:
        break;
    }
    // Override
    if (override) {
        QTextCursor cursor = this->textCursor();
        cursor.insertText(text);
        if (backward)
            cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
        this->setTextCursor(cursor);
        return;
    }
    // Popup
    bool shortcut = ((event->modifiers() & Qt::ControlModifier) && event->key() == Qt::Key_Space);
    if (!shortcut)
        QPlainTextEdit::keyPressEvent(event);
    // Completion
    const bool controlshift = event->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (controlshift && event->text().isEmpty())
        return;
    static QString endofword("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-=");
    bool modifier = (event->modifiers() != Qt::NoModifier) && !controlshift;
    QString prefix = this->cursored();
    if (!shortcut && (modifier || event->text().isEmpty()|| (prefix.length() < EDITOR_TRIGGER) || endofword.contains(event->text().right(1)))) {
        this->_completer->popup()->hide();
        return;
    }
    if (prefix != this->_completer->completionPrefix()) {
        this->_completer->setCompletionPrefix(prefix);
        this->_completer->popup()->setCurrentIndex(this->_completer->completionModel()->index(0, 0));
    }
    QRect rectangle = this->cursorRect();
    rectangle.setWidth(this->_completer->popup()->sizeHintForColumn(0) + this->_completer->popup()->verticalScrollBar()->sizeHint().width());
    this->_completer->complete(rectangle);
}

int Coder::linerAreaWidth()
{
    int digits = 1;
    int max = qMax(1, this->blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }
    digits++;
    digits++;
    return (3 + this->fontMetrics().width('9') * digits);
}

void Coder::linerPaintEvent(QPaintEvent *event)
{
    QPainter painter(this->_liner);
    painter.fillRect(event->rect(), EDITOR_SIDEBAR);
    QTextBlock block = this->firstVisibleBlock();
    int number = block.blockNumber();
    int top = (int) this->blockBoundingGeometry(block).translated(this->contentOffset()).top();
    int bottom = top + (int) this->blockBoundingRect(block).height();
    while (block.isValid() && (top <= event->rect().bottom())) {
        if (block.isVisible() && (bottom >= event->rect().top())) {
            QString newer = QString::number(number + 1).append(" ");
            painter.setPen(QColor(EDITOR_LINE));
            painter.drawText(0, top, this->_liner->width(), this->fontMetrics().height(), Qt::AlignRight, newer);
        }
        block = block.next();
        top = bottom;
        bottom = (top + ((int) this->blockBoundingRect(block).height()));
        ++number;
    }
}

QString Coder::path()
{
    return this->_path;
}

void Coder::path(const QString &path)
{
    this->_path = path;
}

void Coder::read(const QString &path)
{
    this->_path.clear();
    this->_path.append(path);
    this->revert();
}

bool Coder::revert()
{
    this->clear();
    QFileInfo info(this->_path);
    if (!info.exists() || !info.isFile())
        return false;
    this->_completer->initialize(info.suffix());
    if (info.suffix() == QString("xml")) {
        XMLHighlighter *highlighter = new XMLHighlighter(this->document());
        highlighter->initialize();
    } else {
        Highlighter *highlighter = new Highlighter(this->document());
        highlighter->initialize(info.suffix());
    }
    QFile file(info.absoluteFilePath());
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        this->setPlainText(file.readAll());
        file.close();
        return true;
    } else
        return false;
}

bool Coder::save()
{
    QFileInfo info(this->_path);
    if (!info.exists() || !info.isFile())
        return false;
    QFile file(info.absoluteFilePath());
    if (!file.open(QIODevice::Text | QIODevice::Truncate | QIODevice::WriteOnly))
        return false;
    QTextStream stream(&file);
    stream.setGenerateByteOrderMark(false);
    stream.setCodec("UTF-8");
    stream << QString::fromUtf8(this->toPlainText().toStdString().c_str());
    file.close();
    return true;
}

void Coder::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    QRect resized = this->contentsRect();
    this->_liner->setGeometry(QRect(resized.left(), resized.top(), this->linerAreaWidth(), resized.height()));
}

bool Coder::selected()
{
    return (this->textCursor().selection().toPlainText().trimmed().length() > 0);
}

void Coder::updateLinerArea(const QRect &rectangle, const int column)
{
    if (column)
        this->_liner->scroll(0, column);
    else if ((_cache.first != blockCount()) || (_cache.second != this->textCursor().block().lineCount())) {
        this->_liner->update(0, rectangle.y(), _liner->width(), rectangle.height());
        _cache.first = this->blockCount();
        _cache.second = this->textCursor().block().lineCount();
    }
    if (rectangle.contains(viewport()->rect()))
        this->updateLinerAreaWidth(0);
}

void Coder::updateLinerAreaWidth(const int /* count */)
{
    this->setViewportMargins(this->linerAreaWidth(), 0, 0, 0);
}

void Coder::__menu(const QPoint &point)
{
    this->_copy->setEnabled(false);
    this->_cut->setEnabled(false);
    this->_paste->setEnabled(false);
    if (this->selected()) {
        this->_copy->setEnabled(true);
        this->_cut->setEnabled(true);
    }
    if (QApplication::clipboard()->ownsClipboard())
        this->_paste->setEnabled(true);
    this->_menu->exec(this->mapToGlobal(point));
}

} // namespace UI
} // namespace APKStudio
} // namespace VPZ
