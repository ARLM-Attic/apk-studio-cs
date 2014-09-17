#ifndef VPZ_APKSTUDIO_UI_EDITORS_H
#define VPZ_APKSTUDIO_UI_EDITORS_H

#include <QDebug>

#include <QAction>
#include <QComboBox>
#include <QFileInfo>
#include <QIcon>
#include <QLabel>
#include <QList>
#include <QMessageBox>
#include <QObject>
#include <QTabWidget>
#include <QString>
#include <QStringList>
#include <QStringRef>
#include <QToolBar>
#include <QVariant>
#include <QVBoxLayout>
#include <QWidget>

#include "coder.h"
#include "../bridge/constant.h"
#include "../utility/resource.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

class Editors : public QWidget
{
    Q_OBJECT
private:
    // Action
    QAction *_close;
    QAction *_first;
    QAction *_last;
    QAction *_next;
    QAction *_previous;
    QAction *_revert;
    QAction *_save;
    // Combo
    QComboBox *_combo;
    // Function
    void reset();
    // Label
    QLabel *_meta;
    // Map
    QList<QString> *_list;
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("editors" ,name);
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("editors", key);
    }
    // Tabs
    QTabWidget *_tabs;
    // Toolbar
    QToolBar *_toolbar;
public:
    // Constructor
    Editors(QWidget * = 0);
    // Function
    Coder *coder()
    {
        if (this->_tabs->currentIndex() > -1)
            return qobject_cast<Coder *>(this->_tabs->currentWidget());
        return 0;
    }
    void copy()
    {
        Coder *coder = this->coder();
        if (coder)
            coder->copy();
    }
    void cut()
    {
        Coder *coder = this->coder();
        if (coder)
            coder->cut();
    }
    void deleted(const QString &);
    void load(const QString &);
    void paste()
    {
        Coder *coder = this->coder();
        if (coder)
            coder->paste();
    }
    void redo()
    {
        Coder *coder = this->coder();
        if (coder)
            coder->redo();
    }
    void renamed(const QString &, const QString &);
    void selectAll()
    {
        Coder *coder = this->coder();
        if (coder)
            coder->selectAll();
    }
    void close();
    void close(const QString &);
    void close(const int);
    void save();
    void saveall()
    {
        if (this->_list->size() == 1)
            this->save();
        else if (this->_list->size() > 1) {
            for (int index = 0; index < this->_list->size(); index++) {
                Coder *coder = qobject_cast<Coder *>(this->_tabs->widget(index));
                if (coder)
                    coder->save();
            }
            emit message(text("message_save_all").arg(this->_list->size()));
        }
    }
    void undo()
    {
        Coder *coder = this->coder();
        if (coder)
            coder->undo();
    }
signals:
    void changed();
    void cutable(const bool);
    void count(const int);
    void message(const QString &);
    void progress(const int);
    void redoable(const bool);
    void undoable(const bool);
private slots:
    // Index
    void __changed(const int);
    // Change
    void __changed(const int, const int);
    // Action
    void __close()
    {
        this->close();
    }
    void __close(const int index)
    {
        this->close(index);
    }
    void __first();
    void __last();
    void __next();
    void __previous();
    void __revert();
    void __save()
    {
        this->save();
    }
    // Menubar
    void __cutable(const bool yes)
    {
        emit cutable(yes);
    }
    void __redoable(const bool yes)
    {
        emit redoable(yes);
    }
    void __undoable(const bool yes)
    {
        emit undoable(yes);
    }
};

} // namespace UI
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_UI_EDITORS_H
