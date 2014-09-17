#include "toolbar.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

Toolbar::Toolbar(QWidget *parent) :
    QToolBar(parent)
{
    /*
     * @Initialize
     */
    // Action
    this->_apk = new QAction(icon("apk"), text("label_apk"), this);
    this->_build = new QAction(icon("build"), text("label_build"), this);
    this->_directory = new QAction(icon("directory"), text("label_directory"), this);
    this->_print = new QAction(icon("print"), text("label_print"), this);
    this->_save = new QAction(icon("save"), text("label_save"), this);
    this->_shell = new QAction(icon("shell"), text("label_shell"), this);
    /*
     * @Prepare
     */
    // Action
    this->reset();
    /*
     * @Bind
     */
    // Action
    this->connect(this->_apk, SIGNAL(triggered()), this, SLOT(__apk()));
    this->connect(this->_build, SIGNAL(triggered()), this, SLOT(__build()));
    this->connect(this->_directory, SIGNAL(triggered()), this, SLOT(__directory()));
    this->connect(this->_print, SIGNAL(triggered()), this, SLOT(__print()));
    this->connect(this->_save, SIGNAL(triggered()), this, SLOT(__save()));
    this->connect(this->_shell, SIGNAL(triggered()), this, SLOT(__shell()));
    /*
     * @Inflate
     */
    // Action
    this->addAction(this->_apk);
    this->addAction(this->_directory);
    this->addSeparator();
    this->addAction(this->_print);
    this->addAction(this->_save);
    this->addSeparator();
    this->addAction(this->_build);
    this->addSeparator();
    this->addAction(this->_shell);
    /*
     * @Assign
     */
    this->setAcceptDrops(false);
    this->setMovable(false);
}

void Toolbar::disable(const int action, const bool block)
{
    QAction *pointer = this->get(action);
    if (pointer != 0) {
        if (block)
            this->blockSignals(true);
        pointer->setEnabled(false);
        if (block)
            this->blockSignals(false);
    }
}

void Toolbar::enable(const int action, const bool block)
{
    QAction *pointer = this->get(action);
    if (pointer != 0) {
        if (block)
            this->blockSignals(true);
        pointer->setEnabled(true);
        if (block)
            this->blockSignals(false);
    }
}

QAction *Toolbar::get(const int action)
{
    switch (action)
    {
    case APK:
        return this->_apk;
    case BUILD:
        return this->_build;
    case DIRECTORY:
        return this->_directory;
    case PRINT:
        return this->_print;
    case SAVE:
        return this->_save;
    case SHELL:
        return this->_shell;
    default:
        return 0;
    }
}

void Toolbar::reset()
{
    this->_build->setEnabled(false);
    this->_print->setEnabled(false);
    this->_save->setEnabled(false);
}

void Toolbar::toggle(const int action, const bool check, const bool block)
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

} // namespace UI
} // namespace APKStudio
} // namespace VPZ
