#ifndef VPZ_APKSTUDIO_DIALOG_ADD_H
#define VPZ_APKSTUDIO_DIALOG_ADD_H

#include <QChar>
#include <QCloseEvent>
#include <QDialogButtonBox>
#include <QDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QFormLayout>
#include <QIcon>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QObject>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QSize>
#include <QStandardPaths>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

#include "../runtime/framework.h"
#include "../utility/resource.h"
#include "../utility/configuration.h"
#include "../utility/ui.h"

namespace VPZ {
namespace APKStudio {
namespace Dialog {

class Add : public QDialog
{
    Q_OBJECT
private:
    // Variable
    bool _status;
    // Button
    QPushButton *_browse;
    QPushButton *_cancel;
    QPushButton *_install;
    // Buttons
    QDialogButtonBox *_buttons;
    // Edit
    QLineEdit *_path;
    QLineEdit *_tag;
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("add", name);
    }
    static const QString path()
    {
        return Utility::Resource::root();
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("add", key);
    }
    // Function
    void install(const QString &);
public:
    // Constructor
    Add(QWidget * = 0);
    // Function
    bool status() const
    {
        return this->_status;
    }
    // Destructor
    ~Add() { }
public slots:
    void __browse();
    void __changed();
    void __framework(const QString &);
    void __install();
};

} // namespace Dialog
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_DIALOG_ADD_H
