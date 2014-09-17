#include "editors.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

Editors::Editors(QWidget *parent) :
    QWidget(parent)
{
    /*
     * @Initialize
     */
    // Toolbar
    this->_toolbar = new QToolBar(this);
    // Action
    this->_close = new QAction(icon("close"), text("label_close"), this->_toolbar);
    this->_first = new QAction(icon("first"), text("label_first"), this->_toolbar);
    this->_last = new QAction(icon("last"), text("label_last"), this->_toolbar);
    this->_next = new QAction(icon("next"), text("label_next"), this->_toolbar);
    this->_previous = new QAction(icon("previous"), text("label_previous"), this->_toolbar);
    this->_revert = new QAction(icon("revert"), text("label_revert"), this->_toolbar);
    this->_save = new QAction(icon("save"), text("label_save"), this->_toolbar);
    // Combo
    this->_combo = new QComboBox(this->_toolbar);
    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    // List
    this->_list = new QList<QString>();
    // Meta
    this->_meta = new QLabel(this->_toolbar);
    // Tabs
    this->_tabs = new QTabWidget(this);
    /*
     * @Prepare
     */
    // Action
    this->reset();
    // Combo
    this->_combo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // Layout
    layout->setContentsMargins(QMargins(2, 2, 2, 2));
    layout->setSpacing(0);
    // Meta
    this->_meta = new QLabel(this->_toolbar);
    this->_meta->setStyleSheet("color: #333333; margin-left: 4px; margin-right: 4px;");
    this->_meta->setText(text("label_meta").arg(0).arg(0));
    // Tabs
    this->_tabs->setTabsClosable(true);
    // Toolbar
    this->_toolbar->setAcceptDrops(false);
    this->_toolbar->setMovable(false);
    // Widget
    this->setMinimumSize(QSize(160, 160));
    /*
     * @Bind
     */
    // Action
    this->connect(this->_close, SIGNAL(triggered()), this, SLOT(__close()));
    this->connect(this->_first, SIGNAL(triggered()), this, SLOT(__first()));
    this->connect(this->_last, SIGNAL(triggered()), this, SLOT(__last()));
    this->connect(this->_next, SIGNAL(triggered()), this, SLOT(__next()));
    this->connect(this->_previous, SIGNAL(triggered()), this, SLOT(__previous()));
    this->connect(this->_revert, SIGNAL(triggered()), this, SLOT(__revert()));
    this->connect(this->_save, SIGNAL(triggered()), this, SLOT(__save()));
    // List
    this->connect(this->_combo, SIGNAL(currentIndexChanged(const int)), this, SLOT(__changed(const int)));
    // Tabs
    this->connect(this->_tabs, SIGNAL(tabCloseRequested(const int)), this, SLOT(__close(int)));
    this->connect(this->_tabs, SIGNAL(currentChanged(const int)), this, SLOT(__changed(const int)));
    /*
     * @Inflate
     */
    // Layout
    layout->addWidget(this->_toolbar);
    layout->addWidget(this->_tabs);
    // Action
    QList<QAction *> navigation;
    navigation << this->_first;
    navigation << this->_previous;
    navigation << this->_next;
    navigation << this->_last;
    QList<QAction *> state;
    state << this->_save;
    state << this->_revert;
    // Toolbar
    this->_toolbar->addActions(navigation);
    this->_toolbar->addSeparator();
    this->_toolbar->addActions(state);
    this->_toolbar->addWidget(this->_combo);
    this->_toolbar->addWidget(this->_meta);
    this->_toolbar->addSeparator();
    this->_toolbar->addAction(this->_close);
    /*
     * @Assign
     */
    // Widget
    this->setLayout(layout);
}

void Editors::close()
{
    if (this->_list->size() < 1)
        return;
    int index = this->_tabs->currentIndex();
    this->close(index);
}

void Editors::close(const QString &project)
{
    if (this->_list->size() < 1)
        return;
    for (int index = 0; index < this->_list->size();) {
        if (this->_list->at(index).startsWith(project))
            this->close(index);
        else
            index++;
    }
}

void Editors::close(const int index)
{
    if (index >= this->_list->size())
        return;
    QWidget *widget = this->_tabs->widget(index);
    Coder *coder = qobject_cast<Coder *>(widget);
    if (coder) {
        this->disconnect(coder, SIGNAL(changed(const int, const int)), this, SLOT(__changed(const int, const int)));
        this->disconnect(coder, SIGNAL(close_()), this, SLOT(__close()));
        this->disconnect(coder, SIGNAL(undoAvailable(bool)), this, SLOT(__undoable(const bool)));
        this->disconnect(coder, SIGNAL(redoAvailable(const bool)), this, SLOT(__redoable(const bool)));
        this->disconnect(coder, SIGNAL(save_()), this, SLOT(__save()));
        this->_combo->removeItem(index);
        this->_list->removeAt(index);
        this->_tabs->removeTab(index);
        this->reset();
    }
}

void Editors::deleted(const QString &path)
{
    int index = this->_list->indexOf(path);
    if (index > -1)
        this->close(index);
}

void Editors::load(const QString &path)
{
    QStringList text;
    text << QString("java");
    text << QString("smali");
    text << QString("txt");
    text << QString("xml");
    text << QString("yml");
    QFileInfo info(path);
    if (info.exists() && info.isFile()) {
        int tab = this->_list->indexOf(path);
        if (tab > -1) {
            this->_tabs->setCurrentIndex(tab);
            return;
        }
        QString extension = info.suffix();
        if (!text.contains(extension))
            return;
        Coder *coder = new Coder(this->_tabs);
        this->connect(coder, SIGNAL(copyAvailable(const bool)), this, SLOT(__cutable(const bool)));
        this->connect(coder, SIGNAL(changed(const int, const int)), this, SLOT(__changed(const int, const int)));
        this->connect(coder, SIGNAL(close_()), this, SLOT(__close()));
        this->connect(coder, SIGNAL(undoAvailable(bool)), this, SLOT(__undoable(const bool)));
        this->connect(coder, SIGNAL(redoAvailable(const bool)), this, SLOT(__redoable(const bool)));
        this->connect(coder, SIGNAL(save_()), this, SLOT(__save()));
        if (info.suffix() == QString("yml"))
            coder->setReadOnly(true);
        coder->read(info.absoluteFilePath());
        QString label = info.fileName();
        if (label.length() > 24)
            label = label.mid(0, 24);
        int index = this->_tabs->addTab(coder, icon(extension.toStdString().c_str()), label);
        this->_list->append(info.absoluteFilePath());
        this->_tabs->setCurrentIndex(index);
        this->_tabs->setTabToolTip(index, info.absoluteFilePath());
        this->_combo->addItem(icon(extension.toStdString().c_str()), label, QVariant(info.absoluteFilePath()));
        this->__changed(index);
    }
}

void Editors::renamed(const QString &current, const QString &previous)
{
    int index = this->_list->indexOf(previous);
    if (index > -1) {
        QFileInfo info(current);
        this->_combo->setItemData(index, QVariant(info.absoluteFilePath()), ROLE_PATH);
        this->_combo->setItemText(index, info.fileName());
        this->_list->replace(index, info.absoluteFilePath());
        this->_tabs->setTabText(index, info.fileName());
        this->_tabs->setTabToolTip(index, info.absoluteFilePath());
        QWidget *widget = this->_tabs->widget(index);
        Coder *coder = qobject_cast<Coder *>(widget);
        if (coder)
            coder->path(info.absoluteFilePath());
    }
}

void Editors::reset()
{
    // Disable
    this->_close->setEnabled(false);
    this->_first->setEnabled(false);
    this->_last->setEnabled(false);
    this->_next->setEnabled(false);
    this->_previous->setEnabled(false);
    this->_revert->setEnabled(false);
    this->_save->setEnabled(false);
    // Current
    int index = this->_tabs->currentIndex();
    // First/Previous
    if (index > 0) {
        this->_first->setEnabled(true);
        this->_previous->setEnabled(true);
    }
    // Last/Next
    if (index < (this->_list->size() - 1)) {
        this->_last->setEnabled(true);
        this->_next->setEnabled(true);
    }
    // Close
    if (index > -1) {
        this->_close->setEnabled(true);
        this->_revert->setEnabled(true);
        this->_save->setEnabled(true);
        Coder *coder = this->coder();
        if (coder) {
            if (coder->document()->availableRedoSteps() < 1)
                emit redoable(false);
            if (coder->document()->availableUndoSteps() < 1)
                emit undoable(false);
            if (coder->selected())
                this->__cutable(true);
            else
                this->__cutable(false);
        }
    }
    emit count(this->_list->count());
}

void Editors::save()
{
    Coder *coder = this->coder();
    if (coder) {
        QString line;
        if (coder->save())
            line = text("message_save");
        else
            line = text("failure_save");
        emit message(line.arg(coder->path()));
    }
}

void Editors::__changed(const int index)
{
    if (index >= this->_list->size())
        return;
    if (this->_combo->currentIndex() != index)
        this->_combo->setCurrentIndex(index);
    if (this->_tabs->currentIndex() != index)
        this->_tabs->setCurrentIndex(index);
    if (index > -1) {
        this->_tabs->currentWidget()->setFocus();
        emit changed();
    }
    this->reset();
}

void Editors::__changed(const int line, const int column)
{
    this->_meta->setText(text("label_meta").arg(line).arg(column));
}

void Editors::__first()
{
    int index = this->_tabs->currentIndex();
    if (this->_list->size() < 2)
        return;
    if (index <= 0)
        return;
    index = 0;
    this->_tabs->setCurrentIndex(index);
    this->__changed(index);
}

void Editors::__last()
{
    int index = this->_tabs->currentIndex();
    if (this->_list->size() < 2)
        return;
    if (index >= (this->_list->size() - 1))
        return;
    index = this->_list->size() - 1;
    this->_tabs->setCurrentIndex(index);
    this->__changed(index);
}

void Editors::__next()
{
    int index = this->_tabs->currentIndex();
    if (this->_list->size() < 2)
        return;
    if (index >= (this->_list->size() - 1))
        return;
    index = index + 1;
    this->_tabs->setCurrentIndex(index);
    this->__changed(index);
}

void Editors::__previous()
{
    int index = this->_tabs->currentIndex();
    if (this->_list->size() < 2)
        return;
    if (index <= 0)
        return;
    index = index - 1;
    this->_tabs->setCurrentIndex(index);
    this->__changed(index);
}

void Editors::__revert()
{
    QString detail = text("message_revert").arg(this->_list->at(this->_tabs->currentIndex()));
    int result = QMessageBox::question(this, text("title_revert"), detail, QMessageBox::Yes, QMessageBox::No);
    if (result == QMessageBox::Yes) {
        Coder *coder = this->coder();
        if (coder) {
            QString text;
            if (coder->revert())
                text.append("Reloaded file contents from %1");
            else
                text.append("Unable to reload %1");
            emit message(text.arg(coder->path()));
        }
    }
}

} // namespace UI
} // namespace APKStudio
} // namespace VPZ
