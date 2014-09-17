#include "add.h"

namespace VPZ {
namespace APKStudio {
namespace Dialog {

Add::Add(QWidget *parent) :
    QDialog(parent)
{
    /*
     * @Initialize
     */
    // Buttons
    this->_buttons = new QDialogButtonBox(this);
    // Button
    this->_browse = new QPushButton(text("label_browse"), this);
    this->_cancel = new QPushButton(text("label_cancel"), this->_buttons);
    this->_install = new QPushButton(text("label_install"), this->_buttons);
    // Edit
    this->_path = new QLineEdit(this);
    this->_tag = new QLineEdit(this);
    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    // Variable
    this->_status = false;
    // Wrapper
    QWidget *wrapper = new QWidget(this);
    // Layout
    QFormLayout *form = new QFormLayout(wrapper);
    /*
     * @Prepare
     */
    // Button
    Utility::UI::button(this->_browse);
    this->_install->setEnabled(false);
    // Layout
    layout->setContentsMargins(QMargins(4, 4, 4, 4));
    layout->setSpacing(0);
    // Wrapper
    wrapper->setLayout(form);
    // Window
    this->resize(QSize(320, 192));
    this->setMinimumSize(QSize(320, 192));
    this->setMaximumSize(QSize(480, 320));
#ifdef Q_OS_WIN
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
#endif
    this->setWindowIcon(icon("window"));
    this->setWindowTitle(text("title_window"));
    /*
     * @Bind
     */
    this->connect(this->_browse, SIGNAL(clicked()), SLOT(__browse()));
    this->connect(this->_cancel, SIGNAL(clicked()), SLOT(reject()));
    this->connect(this->_install, SIGNAL(clicked()), SLOT(__install()));
    this->connect(this->_path, SIGNAL(textChanged(const QString &)), SLOT(__changed()));
    this->connect(this->_tag, SIGNAL(textChanged(const QString &)), SLOT(__changed()));
    /*
     * @Inflate
     */
    // Buttons
    this->_buttons->addButton(this->_cancel, QDialogButtonBox::RejectRole);
    this->_buttons->addButton(this->_install, QDialogButtonBox::AcceptRole);
    // Form
    form->addRow(text("label_tag"), this->_tag);
    form->addRow(text("label_path"), this->_path);
    form->addRow("", this->_browse);
    // Layout
    layout->addWidget(wrapper);
    layout->addWidget(this->_buttons);
}

void Add::__browse()
{
    QString path = QFileDialog::getOpenFileName(this, text("title_framework"), Add::path(), QString("Android Binary (*.apk)"), 0, 0);
    if (path.isNull() || path.isEmpty())
        return;
    this->_path->setText(path);
}

void Add::__changed()
{
    this->_install->setEnabled(false);
    // Tag
    QRegularExpression tag(QString(REGEX_TAG));
    if (!tag.match(this->_tag->text()).hasMatch())
        return;
    // APK
    QFileInfo apk(this->_path->text());
    if (!apk.exists() || !apk.isFile() || (apk.suffix() != QString("apk")))
        return;
    this->_install->setEnabled(true);
}

void Add::__framework(const QString &path)
{
    if (!path.isEmpty()) {
        this->_status = true;
        this->accept();
        return;
    }
    QMessageBox::critical(this, text("title_failure"), text("message_failure").arg(this->_path->text()), QMessageBox::Close);
    this->_cancel->setEnabled(true);
    this->_install->setEnabled(true);
    this->_install->setText(text("label_install"));
    this->_path->setEnabled(true);
    this->_tag->setEnabled(true);
}

void Add::__install()
{
    this->_cancel->setEnabled(false);
    this->_install->setEnabled(false);
    this->_install->setText(text("label_wait"));
    this->_path->setEnabled(false);
    this->_tag->setEnabled(false);
    // Prepare
    Runtime::Framework *framework = new Runtime::Framework(this->_path->text(), this->_tag->text());
    // Bind
    this->connect(framework, SIGNAL(framework(const QString &)), this, SLOT(__framework(const QString &)));
    // Execute
    framework->start();
}

} // namespace Dialog
} // namespace APKStudio
} // namespace VPZ
