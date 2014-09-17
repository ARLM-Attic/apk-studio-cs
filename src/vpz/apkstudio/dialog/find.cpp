#include "find.h"

namespace VPZ {
namespace APKStudio {
namespace Dialog {

Find::Find(bool replace, QWidget *parent) :
    QDialog(parent)
{
    this->initialize();
    // Hide
    if (!replace) {
        this->_replace->setEnabled(false);
        this->_replaceable->setEnabled(false);
        this->_replaceall->setEnabled(false);
        this->setWindowIcon(icon("find"));
        this->setWindowTitle(text("title_find"));
    } else {
        this->setWindowIcon(icon("replace"));
        this->setWindowTitle(text("title_replace"));
    }
    // Private
    this->resize(QSize(360, 256));
    this->setMinimumSize(QSize(320, 192));
    this->setMaximumSize(QSize(480, 320));
#ifdef Q_OS_WIN
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
#endif
}

void Find::find(bool next)
{
    if (!this->_editor)
        return;
    const QString &searchable = this->_searchable->text();
    bool result = false;
    QTextDocument::FindFlags flags;
    if (!next)
        flags |= QTextDocument::FindBackward;
    if (this->_case->isChecked())
        flags |= QTextDocument::FindCaseSensitively;
    if (this->_whole->isChecked())
        flags |= QTextDocument::FindWholeWords;

    if (this->_regex->isChecked()) {
        QRegExp regex(searchable, (this->_case->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive));
        this->_cursor = this->_editor->document()->find(regex, this->_cursor, flags);
        this->_editor->setTextCursor(this->_cursor);
        result = !this->_cursor.isNull();
    } else
        result = this->_editor->find(searchable, flags);
    if (result)
        this->_message->setText(QString(""));
    else {
        this->_cursor = this->_editor->textCursor();
        this->_cursor.setPosition(QTextCursor::Start);
        this->_editor->setTextCursor(this->_cursor);
        this->_message->setText(text("message_find"));
    }
}

void Find::initialize()
{
    /*
     * @Initialize
     */
    // Box
    QDialogButtonBox *box = new QDialogButtonBox(this);
    // Button
    this->_find = new QPushButton(text("label_find"), box);
    this->_replace = new QPushButton(text("label_replace"), box);
    this->_replaceall = new QPushButton(text("label_replaceall"), box);
    // Checkbox
    this->_case = new QCheckBox(text("label_case"), this);
    this->_regex = new QCheckBox(text("label_regex"), this);
    this->_whole = new QCheckBox(text("label_whole"), this);
    // Group
    QGroupBox *direction = new QGroupBox(text("label_direction"), this);
    QGroupBox *flag = new QGroupBox(text("label_flag"), this);
    // Input
    this->_replaceable = new QLineEdit(this);
    this->_searchable = new QLineEdit(this);
    // Label
    this->_message = new QLabel(QString(""), this);
    // Radio
    this->_down = new QRadioButton(text("label_down"), this);
    this->_up = new QRadioButton(text("label_up"), this);
    // Layout
    QVBoxLayout *content = new QVBoxLayout();
    QVBoxLayout *directions = new QVBoxLayout();
    QVBoxLayout *flags = new QVBoxLayout();
    QFormLayout *form = new QFormLayout();
    QVBoxLayout *main = new QVBoxLayout();
    QHBoxLayout *options = new QHBoxLayout();
    /*
     * @Prepare
     */
    // Button
    this->_find->setEnabled(false);
    // Checkbox
    this->_down->setChecked(true);
    // Layout
    /*
     * @Bind
     */
    // Input
    this->connect(this->_searchable, SIGNAL(textChanged(const QString &)), this, SLOT(__changed(const QString &)));
    this->connect(this->_searchable, SIGNAL(textChanged(const QString &)), this, SLOT(__validate(const QString &)));
    // Checkbox
    this->connect(this->_regex, SIGNAL(toggled(const bool)), this, SLOT(__regex(const bool)));
    // Button
    this->connect(this->_find, SIGNAL(clicked()), this, SLOT(__find()));
    this->connect(this->_replace, SIGNAL(clicked()), this, SLOT(__replace()));
    this->connect(this->_replaceall, SIGNAL(clicked()), this, SLOT(__replaceall()));
    /*
     * @Inflate
     */
    // Box
    box->addButton(this->_find, QDialogButtonBox::AcceptRole);
    box->addButton(this->_replace, QDialogButtonBox::ActionRole);
    box->addButton(this->_replaceall, QDialogButtonBox::ActionRole);
    // Direction
    directions->addWidget(this->_up);
    directions->addWidget(this->_down);
    // Flags
    flags->addWidget(this->_case);
    flags->addWidget(this->_whole);
    flags->addWidget(this->_regex);
    // Form
    form->addRow(text("label_searchable"), this->_searchable);
    form->addRow(text("label_replaceable"), this->_replaceable);
    // Horizontal
    content->addLayout(form);
    content->addLayout(options);
    // Group
    direction->setLayout(directions);
    flag->setLayout(flags);
    // Options
    options->addWidget(direction);
    options->addWidget(flag);
    // Vertical
    main->addLayout(content);
    main->addWidget(this->_message);
    main->addWidget(box);
    /*
     * @Assign
     */
    this->setLayout(main);
}

void Find::__changed(const QString &text)
{
    this->_find->setEnabled(text.length() > 0);
}

void Find::__find()
{
    this->find(this->_down->isChecked());
}

void Find::__regex(const bool checked)
{
    if (checked)
        this->__validate(this->_searchable->text());
    else
        this->__validate(QString());
}

void Find::__replace()
{
    if (this->_editor->isReadOnly())
        return;
    if (!this->_editor->textCursor().hasSelection())
        this->find();
    else {
        this->_editor->textCursor().insertText(this->_replaceable->text());
        this->find();
    }
}

void Find::__replaceall()
{
    if (this->_editor->isReadOnly())
        return;
    int replaced = 0;
    while (this->_editor->textCursor().hasSelection()) {
        this->_editor->textCursor().insertText(this->_replaceable->text());
        this->find();
        replaced++;
    }
    this->_message->setText(text("message_replaced").arg(replaced));
}

void Find::__validate(const QString &pattern)
{
    if (!this->_regex->isChecked() || (pattern.length() == 0)) {
        this->_message->setText(QString(""));
        return;
    }
    if (!QRegExp(pattern, (this->_case->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive)).isValid())
        this->_message->setText(text("message_regex"));
}

} // namespace Dialog
} // namespace APKStudio
} // namespace VPZ
