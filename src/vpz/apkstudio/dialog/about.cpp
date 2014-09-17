#include "about.h"

namespace VPZ {
namespace APKStudio {
namespace Dialog {

QWidget *About::android()
{
    // Intitialize
    QWidget *widget = new QWidget(this);
    QLabel *author = new QLabel(widget);
    QVBoxLayout *content = new QVBoxLayout();
    QLabel *description = new QLabel(widget);
    QLabel *image = new QLabel(widget);
    QVBoxLayout *imagebar = new QVBoxLayout();
    QLabel *label = new QLabel(widget);
    QWidget *left = new QWidget(widget);
    QWidget *right = new QWidget(widget);
    QHBoxLayout *splitter = new QHBoxLayout(widget);
    // Font
    QFont big("Arial", 12, QFont::Bold);
    QFont small("Arial", 8, QFont::Bold);
    // Prepare
    author->setFont(small);
    author->setOpenExternalLinks(true);
    author->setText(text("author_android"));
    author->setTextFormat(Qt::RichText);
    author->setTextInteractionFlags(Qt::TextBrowserInteraction);
    content->setContentsMargins(QMargins(0, 0, 0, 0));
    content->setSpacing(0);
    imagebar->setContentsMargins(QMargins(0, 0, 0, 0));
    imagebar->setSpacing(0);
    QMargins margins(description->contentsMargins());
    margins.setTop(4);
    description->setContentsMargins(margins);
    description->setText(text("description_android"));
    description->setTextFormat(Qt::RichText);
    description->setWordWrap(true);
    description->setOpenExternalLinks(true);
    image->setPixmap(icon("android").pixmap(32, 32));
    label->setFont(big);
    label->setText(text("label_android"));
    left->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    right->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitter->setContentsMargins(QMargins(8, 8, 8, 8));
    splitter->setSpacing(8);
    // Inflate
    content->addWidget(label);
    content->addWidget(author);
    content->addWidget(description);
    content->addWidget(right);
    imagebar->addWidget(image);
    imagebar->addWidget(left);
    splitter->addLayout(imagebar);
    splitter->addLayout(content);
    widget->setLayout(splitter);
    // Stretch
    splitter->setStretchFactor(imagebar, 0);
    splitter->setStretchFactor(content, 1);
    // Return
    return widget;
}

QWidget *About::apkstudio()
{
    // Intitialize
    QWidget *widget = new QWidget(this);
    QLabel *author = new QLabel(widget);
    QVBoxLayout *content = new QVBoxLayout();
    QLabel *description = new QLabel(widget);
    QLabel *image = new QLabel(widget);
    QVBoxLayout *imagebar = new QVBoxLayout();
    QLabel *label = new QLabel(widget);
    QWidget *left = new QWidget(widget);
    QWidget *right = new QWidget(widget);
    QHBoxLayout *splitter = new QHBoxLayout(widget);
    // Font
    QFont big("Arial", 12, QFont::Bold);
    QFont small("Arial", 8, QFont::Bold);
    // Prepare
    author->setFont(small);
    author->setOpenExternalLinks(true);
    author->setText(text("author_apkstudio"));
    author->setTextFormat(Qt::RichText);
    author->setTextInteractionFlags(Qt::TextBrowserInteraction);
    content->setContentsMargins(QMargins(0, 0, 0, 0));
    content->setSpacing(0);
    imagebar->setContentsMargins(QMargins(0, 0, 0, 0));
    imagebar->setSpacing(0);
    QMargins margins(description->contentsMargins());
    margins.setTop(4);
    description->setContentsMargins(margins);
    description->setText(text("description_apkstudio"));
    description->setTextFormat(Qt::RichText);
    description->setWordWrap(true);
    description->setOpenExternalLinks(true);
    image->setPixmap(icon("apkstudio").pixmap(32, 32));
    label->setFont(big);
    label->setText(text("label_apkstudio"));
    left->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    right->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitter->setContentsMargins(QMargins(8, 8, 8, 8));
    splitter->setSpacing(8);
    // Inflate
    content->addWidget(label);
    content->addWidget(author);
    content->addWidget(description);
    content->addWidget(right);
    imagebar->addWidget(image);
    imagebar->addWidget(left);
    splitter->addLayout(imagebar);
    splitter->addLayout(content);
    widget->setLayout(splitter);
    // Stretch
    splitter->setStretchFactor(imagebar, 0);
    splitter->setStretchFactor(content, 1);
    // Return
    return widget;
}

QWidget *About::apktool()
{
    // Intitialize
    QWidget *widget = new QWidget(this);
    QLabel *author = new QLabel(widget);
    QVBoxLayout *content = new QVBoxLayout();
    QLabel *description = new QLabel(widget);
    QLabel *image = new QLabel(widget);
    QVBoxLayout *imagebar = new QVBoxLayout();
    QLabel *label = new QLabel(widget);
    QWidget *left = new QWidget(widget);
    QWidget *right = new QWidget(widget);
    QHBoxLayout *splitter = new QHBoxLayout(widget);
    // Font
    QFont big("Arial", 12, QFont::Bold);
    QFont small("Arial", 8, QFont::Bold);
    // Prepare
    author->setFont(small);
    author->setOpenExternalLinks(true);
    author->setText(text("author_apktool"));
    author->setTextFormat(Qt::RichText);
    author->setTextInteractionFlags(Qt::TextBrowserInteraction);
    content->setContentsMargins(QMargins(0, 0, 0, 0));
    content->setSpacing(0);
    imagebar->setContentsMargins(QMargins(0, 0, 0, 0));
    imagebar->setSpacing(0);
    QMargins margins(description->contentsMargins());
    margins.setTop(4);
    description->setContentsMargins(margins);
    description->setText(text("description_apktool"));
    description->setTextFormat(Qt::RichText);
    description->setWordWrap(true);
    description->setOpenExternalLinks(true);
    image->setPixmap(icon("apktool").pixmap(32, 32));
    label->setFont(big);
    label->setText(text("label_apktool"));
    left->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    right->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitter->setContentsMargins(QMargins(8, 8, 8, 8));
    splitter->setSpacing(8);
    // Inflate
    content->addWidget(label);
    content->addWidget(author);
    content->addWidget(description);
    content->addWidget(right);
    imagebar->addWidget(image);
    imagebar->addWidget(left);
    splitter->addLayout(imagebar);
    splitter->addLayout(content);
    widget->setLayout(splitter);
    // Stretch
    splitter->setStretchFactor(imagebar, 0);
    splitter->setStretchFactor(content, 1);
    // Return
    return widget;
}

void About::initialize()
{
    /*
     * @Initialize
     */
    // Toolbar
    QToolBar *toolbar = new QToolBar(this);
    // Action
    this->_android = new QToolButton(toolbar);
    this->_apkstudio = new QToolButton(toolbar);
    this->_apktool = new QToolButton(toolbar);
    this->_fugue = new QToolButton(toolbar);
    this->_qt = new QToolButton(toolbar);
    this->_ubuntu = new QToolButton(toolbar);
    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    // Stack
    this->_stack =  new QStackedWidget(this);
    // Window
#ifdef Q_OS_LINUX
    QSize size(512, 420);
#else
    QSize size(480, 320);
#endif
    /*
     * @Prepare
     */
    // Action
    this->_android->setCheckable(true);
    this->_android->setIcon(icon("android"));
    this->_android->setMinimumWidth(64);
    this->_android->setText(text("label_android"));
    this->_android->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->_android->setToolTip(text("tooltip_android"));
    this->_apkstudio->setCheckable(true);
    this->_apkstudio->setIcon(icon("apkstudio"));
    this->_apkstudio->setMinimumWidth(64);
    this->_apkstudio->setText(text("label_apkstudio"));
    this->_apkstudio->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->_apkstudio->setToolTip(text("tooltip_apkstudio"));
    this->_apktool->setCheckable(true);
    this->_apktool->setIcon(icon("apktool"));
    this->_apktool->setMinimumWidth(64);
    this->_apktool->setText(text("label_apktool"));
    this->_apktool->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->_apktool->setToolTip(text("tooltip_apktool"));
    this->_fugue->setCheckable(true);
    this->_fugue->setIcon(icon("fugue"));
    this->_fugue->setMinimumWidth(64);
    this->_fugue->setText(text("label_fugue"));
    this->_fugue->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->_fugue->setToolTip(text("tooltip_fugue"));
    this->_qt->setCheckable(true);
    this->_qt->setIcon(icon("qt"));
    this->_qt->setMinimumWidth(64);
    this->_qt->setText(text("label_qt"));
    this->_qt->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->_qt->setToolTip(text("tooltip_qt"));
    this->_ubuntu->setCheckable(true);
    this->_ubuntu->setIcon(icon("ubuntu"));
    this->_ubuntu->setMinimumWidth(64);
    this->_ubuntu->setText(text("label_ubuntu"));
    this->_ubuntu->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->_ubuntu->setToolTip(text("tooltip_ubuntu"));
    // Layout
    layout->setContentsMargins(QMargins(2, 2, 2, 2));
    layout->setSpacing(0);
    // Toolbar
    toolbar->setAcceptDrops(false);
    toolbar->setMovable(false);
    // Window
    this->resize(size);
    this->setMinimumSize(size);
#ifdef Q_OS_WIN
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
#endif
    this->setWindowIcon(icon("window"));
    this->setWindowTitle(text("title_window"));
    /*
     * @Bind
     */
    // Action
    this->connect(this->_android, SIGNAL(toggled(const bool)), this, SLOT(__android()));
    this->connect(this->_apkstudio, SIGNAL(toggled(const bool)), this, SLOT(__apkstudio()));
    this->connect(this->_apktool, SIGNAL(toggled(const bool)), this, SLOT(__apktool()));
    this->connect(this->_fugue, SIGNAL(toggled(const bool)), this, SLOT(__fugue()));
    this->connect(this->_qt, SIGNAL(toggled(const bool)), this, SLOT(__qt()));
    this->connect(this->_ubuntu, SIGNAL(toggled(const bool)), this, SLOT(__ubuntu()));
    /*
     * @Inflate
     */
    // Action
    toolbar->addWidget(this->_apkstudio);
    toolbar->addSeparator();
    toolbar->addWidget(this->_apktool);
    toolbar->addSeparator();
    toolbar->addWidget(this->_qt);
    toolbar->addSeparator();
    toolbar->addWidget(this->_fugue);
    toolbar->addSeparator();
    toolbar->addWidget(this->_android);
    toolbar->addSeparator();
    toolbar->addWidget(this->_ubuntu);
    // Layout
    layout->addWidget(this->_stack);
    layout->addWidget(toolbar);
    // Stack
    this->_stack->addWidget(this->android());
    this->_stack->addWidget(this->apkstudio());
    this->_stack->addWidget(this->apktool());
    this->_stack->addWidget(this->fugue());
    this->_stack->addWidget(this->qt());
    this->_stack->addWidget(this->ubuntu());
    // Window
    this->setLayout(layout);
    /*
     * @Assign
     */
    // Action
    this->_apkstudio->setChecked(true);
    // Stack
    this->_stack->setCurrentIndex(APKSTUDIO);
}

QWidget *About::fugue()
{
    // Intitialize
    QWidget *widget = new QWidget(this);
    QLabel *author = new QLabel(widget);
    QVBoxLayout *content = new QVBoxLayout();
    QLabel *description = new QLabel(widget);
    QLabel *image = new QLabel(widget);
    QVBoxLayout *imagebar = new QVBoxLayout();
    QLabel *label = new QLabel(widget);
    QWidget *left = new QWidget(widget);
    QWidget *right = new QWidget(widget);
    QHBoxLayout *splitter = new QHBoxLayout(widget);
    // Font
    QFont big("Arial", 12, QFont::Bold);
    QFont small("Arial", 8, QFont::Bold);
    // Prepare
    author->setFont(small);
    author->setOpenExternalLinks(true);
    author->setText(text("author_fugue"));
    author->setTextFormat(Qt::RichText);
    author->setTextInteractionFlags(Qt::TextBrowserInteraction);
    content->setContentsMargins(QMargins(0, 0, 0, 0));
    content->setSpacing(0);
    imagebar->setContentsMargins(QMargins(0, 0, 0, 0));
    imagebar->setSpacing(0);
    QMargins margins(description->contentsMargins());
    margins.setTop(4);
    description->setContentsMargins(margins);
    description->setText(text("description_fugue"));
    description->setTextFormat(Qt::RichText);
    description->setWordWrap(true);
    description->setOpenExternalLinks(true);
    image->setPixmap(icon("fugue").pixmap(32, 32));
    label->setFont(big);
    label->setText(text("label_fugue"));
    left->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    right->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitter->setContentsMargins(QMargins(8, 8, 8, 8));
    splitter->setSpacing(8);
    // Inflate
    content->addWidget(label);
    content->addWidget(author);
    content->addWidget(description);
    content->addWidget(right);
    imagebar->addWidget(image);
    imagebar->addWidget(left);
    splitter->addLayout(imagebar);
    splitter->addLayout(content);
    widget->setLayout(splitter);
    // Stretch
    splitter->setStretchFactor(imagebar, 0);
    splitter->setStretchFactor(content, 1);
    // Return
    return widget;
}

QWidget *About::qt()
{
    // Intitialize
    QWidget *widget = new QWidget(this);
    QLabel *author = new QLabel(widget);
    QVBoxLayout *content = new QVBoxLayout();
    QLabel *description = new QLabel(widget);
    QLabel *image = new QLabel(widget);
    QVBoxLayout *imagebar = new QVBoxLayout();
    QLabel *label = new QLabel(widget);
    QWidget *left = new QWidget(widget);
    QWidget *right = new QWidget(widget);
    QHBoxLayout *splitter = new QHBoxLayout(widget);
    // Font
    QFont big("Arial", 12, QFont::Bold);
    QFont small("Arial", 8, QFont::Bold);
    // Prepare
    author->setFont(small);
    author->setOpenExternalLinks(true);
    author->setText(text("author_qt"));
    author->setTextFormat(Qt::RichText);
    author->setTextInteractionFlags(Qt::TextBrowserInteraction);
    content->setContentsMargins(QMargins(0, 0, 0, 0));
    content->setSpacing(0);
    imagebar->setContentsMargins(QMargins(0, 0, 0, 0));
    imagebar->setSpacing(0);
    QMargins margins(description->contentsMargins());
    margins.setTop(4);
    description->setContentsMargins(margins);
    description->setText(text("description_qt"));
    description->setTextFormat(Qt::RichText);
    description->setWordWrap(true);
    description->setOpenExternalLinks(true);
    image->setPixmap(icon("qt").pixmap(32, 32));
    label->setFont(big);
    label->setText(text("label_qt"));
    left->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    right->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitter->setContentsMargins(QMargins(8, 8, 8, 8));
    splitter->setSpacing(8);
    // Inflate
    content->addWidget(label);
    content->addWidget(author);
    content->addWidget(description);
    content->addWidget(right);
    imagebar->addWidget(image);
    imagebar->addWidget(left);
    splitter->addLayout(imagebar);
    splitter->addLayout(content);
    widget->setLayout(splitter);
    // Stretch
    splitter->setStretchFactor(imagebar, 0);
    splitter->setStretchFactor(content, 1);
    // Return
    return widget;
}

QWidget *About::ubuntu()
{
    // Intitialize
    QWidget *widget = new QWidget(this);
    QLabel *author = new QLabel(widget);
    QVBoxLayout *content = new QVBoxLayout();
    QLabel *description = new QLabel(widget);
    QLabel *image = new QLabel(widget);
    QVBoxLayout *imagebar = new QVBoxLayout();
    QLabel *label = new QLabel(widget);
    QWidget *left = new QWidget(widget);
    QWidget *right = new QWidget(widget);
    QHBoxLayout *splitter = new QHBoxLayout(widget);
    // Font
    QFont big("Arial", 12, QFont::Bold);
    QFont small("Arial", 8, QFont::Bold);
    // Prepare
    author->setFont(small);
    author->setOpenExternalLinks(true);
    author->setText(text("author_ubuntu"));
    author->setTextFormat(Qt::RichText);
    author->setTextInteractionFlags(Qt::TextBrowserInteraction);
    content->setContentsMargins(QMargins(0, 0, 0, 0));
    content->setSpacing(0);
    imagebar->setContentsMargins(QMargins(0, 0, 0, 0));
    imagebar->setSpacing(0);
    QMargins margins(description->contentsMargins());
    margins.setTop(4);
    description->setContentsMargins(margins);
    description->setText(text("description_ubuntu"));
    description->setTextFormat(Qt::RichText);
    description->setWordWrap(true);
    description->setOpenExternalLinks(true);
    image->setPixmap(icon("ubuntu").pixmap(32, 32));
    label->setFont(big);
    label->setText(text("label_ubuntu"));
    left->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    right->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitter->setContentsMargins(QMargins(8, 8, 8, 8));
    splitter->setSpacing(8);
    // Inflate
    content->addWidget(label);
    content->addWidget(author);
    content->addWidget(description);
    content->addWidget(right);
    imagebar->addWidget(image);
    imagebar->addWidget(left);
    splitter->addLayout(imagebar);
    splitter->addLayout(content);
    widget->setLayout(splitter);
    // Stretch
    splitter->setStretchFactor(imagebar, 0);
    splitter->setStretchFactor(content, 1);
    // Return
    return widget;
}

} // namespace Dialog
} // namespace APKStudio
} // namespace VPZ
