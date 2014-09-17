#ifndef VPZ_APKSTUDIO_DIALOG_INFORMATION_H
#define VPZ_APKSTUDIO_DIALOG_INFORMATION_H

#include <QDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QIcon>
#include <QLineEdit>
#include <QObject>
#include <QSize>
#include <QString>
#include <QWidget>

#include "../runtime/build.h"
#include "../runtime/imei.h"
#include "../utility/format.h"
#include "../utility/resource.h"
#include "../utility/text.h"

namespace VPZ {
namespace APKStudio {
namespace Dialog {

class Information : public QDialog
{
    Q_OBJECT
private:
    // Function
    void initialize();
    void retrieve();
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("information", name);
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("information", key);
    }
    // Group
    QGroupBox *_hardware;
    QGroupBox *_network;
    QGroupBox *_software;
    /*
     * @Textbox
     */
    // Hardware
    QLineEdit *_board;
    QLineEdit *_cpu;
    QLineEdit *_imei;
    QLineEdit *_manufacturer;
    QLineEdit *_model;
    QLineEdit *_secure;
    // Network
    QLineEdit *_country;
    QLineEdit *_operator;
    QLineEdit *_timezone;
    QLineEdit *_type;
    // Software
    QLineEdit *_build;
    QLineEdit *_date;
    QLineEdit *_fingerprint;
    QLineEdit *_sdk;
    QLineEdit *_tags;
    QLineEdit *_version;
    // Variable
    QString _device;
private slots:
    void __build(const QMap<QString, QString> &);
    void __imei(const QString &);
public:
    // Constructor
    Information(const QString &device, QWidget *parent = 0)
        : QDialog(parent)
    {
        this->_device = device;
        this->initialize();
        this->retrieve();
    }
    // Destrcutor
    ~Information() { }
};

} // namespace Dialog
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_DIALOG_INFORMATION_H
