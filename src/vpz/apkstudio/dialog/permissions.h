#ifndef VPZ_APKSTUDIO_DIALOG_PERMISSIONS_H
#define VPZ_APKSTUDIO_DIALOG_PERMISSIONS_H

#include <QCheckBox>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QDialog>
#include <QObject>
#include <QPushButton>
#include <QSize>
#include <QVBoxLayout>
#include <QWidget>

#include "../bridge/variant.h"
#include "../utility/resource.h"

namespace VPZ {
namespace APKStudio {
namespace Dialog {

class Permissions : public QDialog
{
    Q_OBJECT
private:
    // Buttons
    QPushButton *_cancel;
    QPushButton *_change;
    // Checkbox
    QCheckBox *_gr;
    QCheckBox *_gw;
    QCheckBox *_gx;
    QCheckBox *_or;
    QCheckBox *_ow;
    QCheckBox *_ox;
    QCheckBox *_recursive;
    QCheckBox *_wr;
    QCheckBox *_ww;
    QCheckBox *_wx;
    // Function
    void initialize();
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("permissions", name);
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("permissions", key);
    }
    // Variable
    Bridge::File _file;
    QString _mode;
    bool _recurse;
private slots:
    void __accept()
    {
        this->_mode.clear();
        this->_mode.append("0");
        // Owner
        bool or_ = this->_or->isChecked();
        bool ow = this->_ow->isChecked();
        bool ox = this->_ox->isChecked();
        if (or_ && ow && ox)
            this->_mode.append("7");
        else if (or_ && ow)
            this->_mode.append("6");
        else if (or_ && ox)
            this->_mode.append("5");
        else if (or_)
            this->_mode.append("4");
        else if (ow && ox)
            this->_mode.append("3");
        else if (ow)
            this->_mode.append("2");
        else if (ox)
            this->_mode.append("1");
        else
            this->_mode.append("0");
        // Group
        bool gr = this->_gr->isChecked();
        bool gw = this->_gw->isChecked();
        bool gx = this->_gx->isChecked();
        if (gr && gw && gx)
            this->_mode.append("7");
        else if (gr && gw)
            this->_mode.append("6");
        else if (gr && gx)
            this->_mode.append("5");
        else if (gr)
            this->_mode.append("4");
        else if (gw && gx)
            this->_mode.append("3");
        else if (gw)
            this->_mode.append("2");
        else if (gx)
            this->_mode.append("1");
        else
            this->_mode.append("0");
        // World
        bool wr = this->_wr->isChecked();
        bool ww = this->_ww->isChecked();
        bool wx = this->_wx->isChecked();
        if (wr && ww && wx)
            this->_mode.append("7");
        else if (wr && ww)
            this->_mode.append("6");
        else if (wr && wx)
            this->_mode.append("5");
        else if (wr)
            this->_mode.append("4");
        else if (ww && wx)
            this->_mode.append("3");
        else if (ww)
            this->_mode.append("2");
        else if (wx)
            this->_mode.append("1");
        else
            this->_mode.append("0");
        this->_recurse = this->_recursive->isChecked();
        this->accept();
    }
public:
    // Constructor
    Permissions(Bridge::File &file, QWidget *parent = 0)
        : QDialog(parent)
    {
        this->_file = file;
        this->_mode = QString("NNNN");
        this->_recurse = false;
        this->initialize();
    }
    // Function
    QString mode()
    {
        return this->_mode;
    }
    bool recursive()
    {
        return this->_recurse;
    }
    // Destructor
    ~Permissions() { }
};

} // namespace Dialog
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_DIALOG_PERMISSIONS_H
