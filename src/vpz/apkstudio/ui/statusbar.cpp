#include "statusbar.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

Statusbar::Statusbar(QWidget *parent) :
    QToolBar(parent)
{
    /*
     * @Initialize
     */
    // Action
    this->_sidebar = new QAction(icon("sidebar"), text("label_sidebar"), this);
    // Button
    this->_button = new QToolButton(this);
    // Social
    this->_facebook = new QAction(icon("facebook"), text("label_facebook"), this);
    this->_github = new QAction(icon("github"), text("label_github"), this);
    this->_googleplus = new QAction(icon("googleplus"), text("label_googleplus"), this);
    this->_linkedin = new QAction(icon("linkedin"), text("label_linkedin"), this);
    this->_mail = new QAction(icon("mail"), text("label_mail"), this);
    this->_paypal = new QAction(icon("paypal"), text("label_paypal"), this);
    this->_twitter = new QAction(icon("twitter"), text("label_twitter"), this);
    this->_website = new QAction(icon("website"), text("label_website"), this);
    this->_youtube = new QAction(icon("youtube"), text("label_youtube"), this);
    // Label
    this->_message = new QLabel(text("label_message"), this);
    // Progress
    this->_progress = new QProgressBar(this);
    // Spacer
    QWidget *spacer = new QWidget(this);
    /*
     * @Prepare
     */
    // Action
    this->_sidebar->setCheckable(true);
    this->_sidebar->setChecked(true);
    // Menu
    QMenu *menu = new QMenu(this->_button);
    menu->addAction(this->_facebook);
    menu->addAction(this->_twitter);
    menu->addAction(this->_googleplus);
    menu->addAction(this->_linkedin);
    menu->addAction(this->_youtube);
    menu->addSeparator();
    menu->addAction(this->_github);
    menu->addSeparator();
    menu->addAction(this->_website);
    menu->addAction(this->_mail);
    menu->addSeparator();
    menu->addAction(this->_paypal);
    // Button
    this->_button->setDefaultAction(this->_website);
    this->_button->setIcon(icon("social"));
    this->_button->setMenu(menu);
    this->_button->setPopupMode(QToolButton::MenuButtonPopup);
    this->_button->setText(text("label_social"));
    this->_button->setToolTip(text("tooltip_social"));
    // Message
    this->_message->setStyleSheet("color: #333333; margin-left: 8px;");
    // Progress
    this->_progress->setMaximum(100);
    this->_progress->setMaximumHeight(16);
    this->_progress->setMaximumWidth(160);
    this->_progress->setMinimum(0);
    this->_progress->setStyleSheet("margin-right: 8px;");
    this->_progress->setTextVisible(false);
    // Spacer
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // Toolbar
    this->setAcceptDrops(false);
    this->setMovable(false);
    QMargins margins = this->contentsMargins();
    margins.setRight(4);
    this->setContentsMargins(margins);
    /*
     * @Bind
     */
    // Action
    this->connect(this->_sidebar, SIGNAL(toggled(const bool)), this, SLOT(__sidebar(const bool)));
    // Social
    this->connect(this->_facebook, SIGNAL(triggered()), this, SLOT(__facebook()));
    this->connect(this->_twitter, SIGNAL(triggered()), this, SLOT(__twitter()));
    this->connect(this->_googleplus, SIGNAL(triggered()), this, SLOT(__googleplus()));
    this->connect(this->_linkedin, SIGNAL(triggered()), this, SLOT(__linkedin()));
    this->connect(this->_youtube, SIGNAL(triggered()), this, SLOT(__youtube()));
    this->connect(this->_github, SIGNAL(triggered()), this, SLOT(__github()));
    this->connect(this->_website, SIGNAL(triggered()), this, SLOT(__website()));
    this->connect(this->_mail, SIGNAL(triggered()), this, SLOT(__mail()));
    this->connect(this->_paypal, SIGNAL(triggered()), this, SLOT(__paypal()));
    /*
     * @Inflate
     */
    // Action
    this->addAction(this->_sidebar);
    // Progress
    this->addWidget(this->_message);
    // Spacer
    this->addWidget(spacer);
    // Progress
    this->addWidget(this->_progress);
    this->addWidget(this->_button);
}

QAction *Statusbar::get(const int action)
{
    switch (action)
    {
    case SIDEBAR:
        return this->_sidebar;
    default:
        return 0;
    }
}

void Statusbar::toggle(const int action, const bool check, const bool block)
{
    QAction *pointer = this->get(action);
    if (pointer != 0) {
        if (block)
            this->blockSignals(true);
        if (pointer->isCheckable())
            pointer->setChecked(check);
        if (block)
            this->blockSignals(false);
    }
}

void Statusbar::message(const QString &text)
{
    if (text.isNull() || text.isEmpty())
        return;
    this->_message->setText(text);
}

void Statusbar::progress(const int value)
{
    if (value > -1) {
        if (this->_progress->maximum() < 100)
            this->_progress->setMaximum(100);
        this->_progress->setValue(value);
    } else {
        this->_progress->setMaximum(0);
        this->_progress->setValue(0);
    }
}

} // namespace UI
} // namespace APKStudio
} // namespace VPZ
