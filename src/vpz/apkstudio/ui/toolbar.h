#ifndef VPZ_APKSTUDIO_UI_TOOLBAR_H
#define VPZ_APKSTUDIO_UI_TOOLBAR_H

#include <QAction>
#include <QIcon>
#include <QObject>
#include <QToolBar>
#include <QWidget>

#include "../utility/resource.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

class Toolbar : public QToolBar
{
    Q_OBJECT
private:
    // Action
    QAction *_apk;
    QAction *_build;
    QAction *_directory;
    QAction *_print;
    QAction *_save;
    QAction *_shell;
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("toolbar", name);
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("toolbar", key);
    }
private slots:
    void __apk()
    {
        emit action(APK);
    }
    void __build()
    {
        emit action(BUILD);
    }
    void __directory()
    {
        emit action(DIRECTORY);
    }
    void __print()
    {
        emit action(PRINT);
    }
    void __save()
    {
        emit action(SAVE);
    }
    void __shell()
    {
        emit action(SHELL);
    }
public:
    // Constructor
    Toolbar(QWidget *parent = 0);
    // Destructor
    ~Toolbar() { }
    // Enum
    enum Action {
        APK = 30,
        BUILD,
        DIRECTORY,
        PRINT,
        SAVE,
        SHELL
    };
    // Function
    void enable(const int, const bool);
    void disable(const int, const bool);
    QAction * get(const int);
    void reset();
    void toggle(const int, const bool, const bool = false);
signals:
    void action(int);
};

} // namespace UI
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_UI_TOOLBAR_H
