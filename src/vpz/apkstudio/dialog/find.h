#ifndef VPZ_APKSTUDIO_DIALOG_FIND_H
#define VPZ_APKSTUDIO_DIALOG_FIND_H

#include <QDialogButtonBox>
#include <QDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QObject>
#include <QPushButton>
#include <QRadioButton>
#include <QRegExp>
#include <QString>
#include <QTextCursor>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "../utility/resource.h"

namespace VPZ {
namespace APKStudio {
namespace Dialog {

class Find : public QDialog
{
    Q_OBJECT
private:
    // Button
    QPushButton *_find;
    QPushButton *_replace;
    QPushButton *_replaceall;
    // Checkbox
    QCheckBox *_case;
    QCheckBox *_regex;
    QCheckBox *_whole;
    // Cursor
    QTextCursor _cursor;
    // Editor
    QPlainTextEdit *_editor;
    // Function
    void find(bool next = true);
    // Input
    QLineEdit *_replaceable;
    QLineEdit *_searchable;
    // Label
    QLabel *_message;
    // Radio
    QRadioButton *_down;
    QRadioButton *_up;
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("find", name);
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("find", key);
    }
private slots:
    void __changed(const QString &);
    void __find();
    void __regex(const bool);
    void __replace();
    void __replaceall();
    void __validate(const QString &);
public:
    // Constructor
    Find(bool replace = false, QWidget *parent = 0);
    // Function
    void initialize();
    QPlainTextEdit *editor()
    {
        return this->_editor;
    }
    void editor(QPlainTextEdit *editor)
    {
        this->_editor = editor;
    }
    // Destructor
    ~Find() { }
};

} // namespace Dialog
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_DIALOG_FIND_H
