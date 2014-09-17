#ifndef VPZ_APKSTUDIO_UI_STATUSBAR_H
#define VPZ_APKSTUDIO_UI_STATUSBAR_H

#include <QAction>
#include <QDesktopServices>
#include <QIcon>
#include <QLabel>
#include <QMenu>
#include <QObject>
#include <QProgressBar>
#include <QString>
#include <QToolBar>
#include <QToolButton>
#include <QUrl>
#include <QWidget>

#include "../utility/resource.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

class Statusbar : public QToolBar
{
    Q_OBJECT
private:
    // Action
    QAction *_sidebar;
    // Button
    QToolButton *_button;
    // Social
    QAction *_facebook;
    QAction *_github;
    QAction *_googleplus;
    QAction *_linkedin;
    QAction *_mail;
    QAction *_paypal;
    QAction *_twitter;
    QAction *_website;
    QAction *_youtube;
    // Label
    QLabel *_message;
    // Progress
    QProgressBar *_progress;
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("statusbar", name);
    }
    void open(const QString &url)
    {
        QDesktopServices::openUrl(QUrl(url));
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("statusbar", key);
    }
private slots:
    // Action
    void __sidebar(const bool checked)
    {
        emit toggled(SIDEBAR, checked);
    }
    // Social
    void __facebook()
    {
        this->open(text("url_facebook"));
    }
    void __github()
    {
        this->open(text("url_github"));
    }
    void __googleplus()
    {
        this->open(text("url_googleplus"));
    }
    void __linkedin()
    {
        this->open(text("url_linkedin"));
    }
    void __mail()
    {
        this->open(text("url_mail"));
    }
    void __paypal()
    {
        this->open(text("url_paypal"));
    }
    void __twitter()
    {
        this->open(text("url_twitter"));
    }
    void __website()
    {
        this->open(text("url_website"));
    }
    void __youtube()
    {
        this->open(text("url_youtube"));
    }
public:
    // Constructor
    Statusbar(QWidget *parent = 0);
    // Enum
    enum Action {
        SIDEBAR = 40
    };
    // Function
    QAction * get(const int);
    void message(const QString &);
    void progress(const int);
    void toggle(const int, const bool, const bool = false);
    // Destructor
    ~Statusbar() { }
signals:
    void toggled(const int, const bool);
};

} // namespace UI
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_UI_STATUSBAR_H
