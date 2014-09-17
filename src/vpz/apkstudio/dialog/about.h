#ifndef VPZ_APKSTUDIO_DIALOG_ABOUT_H
#define VPZ_APKSTUDIO_DIALOG_ABOUT_H

#include <QAction>
#include <QHBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QMargins>
#include <QObject>
#include <QSize>
#include <QStackedWidget>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

#include "../utility/resource.h"

namespace VPZ {
namespace APKStudio {
namespace Dialog {

class About : public QDialog
{
    Q_OBJECT
private:
    // Action
    QToolButton *_android;
    QToolButton *_apkstudio;
    QToolButton *_apktool;
    QToolButton *_fugue;
    QToolButton *_qt;
    QToolButton *_ubuntu;
    // Function
    void initialize();
    void page(const int index)
    {
        // Block
        this->_android->blockSignals(true);
        this->_apkstudio->blockSignals(true);
        this->_apktool->blockSignals(true);
        this->_fugue->blockSignals(true);
        this->_qt->blockSignals(true);
        this->_ubuntu->blockSignals(true);
        // Toggle
        this->_android->setChecked(false);
        this->_apkstudio->setChecked(false);
        this->_apktool->setChecked(false);
        this->_fugue->setChecked(false);
        this->_qt->setChecked(false);
        this->_ubuntu->setChecked(false);
        switch (index)
        {
        case ANDROID:
            this->_android->setChecked(true);
            this->_stack->setCurrentIndex(ANDROID);
            break;
        case APKSTUDIO:
            this->_apkstudio->setChecked(true);
            this->_stack->setCurrentIndex(APKSTUDIO);
            break;
        case APKTOOL:
            this->_apktool->setChecked(true);
            this->_stack->setCurrentIndex(APKTOOL);
            break;
        case FUGUE:
            this->_fugue->setChecked(true);
            this->_stack->setCurrentIndex(FUGUE);
            break;
        case QT:
            this->_qt->setChecked(true);
            this->_stack->setCurrentIndex(QT);
            break;
        case UBUNTU:
            this->_ubuntu->setChecked(true);
            this->_stack->setCurrentIndex(UBUNTU);
            break;
        default:
            break;
        }
        // Unblock
        this->_android->blockSignals(false);
        this->_apkstudio->blockSignals(false);
        this->_apktool->blockSignals(false);
        this->_fugue->blockSignals(false);
        this->_qt->blockSignals(false);
        this->_ubuntu->blockSignals(false);
    }
    QWidget *android();
    QWidget *apkstudio();
    QWidget *apktool();
    QWidget *fugue();
    QWidget *qt();
    QWidget *ubuntu();
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("about", name);
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("about", key);
    }
    // Stack
    QStackedWidget *_stack;
private slots:
    void __android()
    {
        this->page(ANDROID);
    }
    void __apkstudio()
    {
        this->page(APKSTUDIO);
    }
    void __apktool()
    {
        this->page(APKTOOL);
    }
    void __fugue()
    {
        this->page(FUGUE);
    }
    void __qt()
    {
        this->page(QT);
    }
    void __ubuntu()
    {
        this->page(UBUNTU);
    }
public:
    // Constructor
    About(QWidget *parent = 0)
        : QDialog(parent)
    {
        this->initialize();
    }
    // Enum
    enum Credits {
        ANDROID = 0,
        APKSTUDIO,
        APKTOOL,
        FUGUE,
        QT,
        UBUNTU
    };
    // Destructor
    ~About() { }
};

} // namespace Dialog
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_DIALOG_ABOUT_H
