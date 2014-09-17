#ifndef VPZ_APKSTUDIO_DIALOG_LOGCAT_H
#define VPZ_APKSTUDIO_DIALOG_LOGCAT_H

#include <QAction>
#include <QApplication>
#include <QChar>
#include <QClipboard>
#include <QCloseEvent>
#include <QColor>
#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QIcon>
#include <QList>
#include <QMenu>
#include <QMessageBox>
#include <QObject>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>

#include "../bridge/constant.h"
#include "../bridge/variant.h"
#include "../runtime/logger.h"
#include "../utility/resource.h"
#include "../utility/text.h"

namespace VPZ {
namespace APKStudio {
namespace Dialog {

class Logcat : public QDialog
{
    Q_OBJECT
private:
    // Action
    QAction *_clear;
    QAction *_copy;
    QAction *_debug;
    QAction *_error;
    QAction *_info;
    QAction *_load;
    QAction *_remove;
    QAction *_save;
    QAction *_scroll;
    QAction *_start;
    QAction *_stop;
    QAction *_verbose;
    QAction *_warning;
    // Function
    void initialize();
    // Layout
    QVBoxLayout *_layout;
    // Menu
    QMenu *_menu;
    // Logger
    Runtime::Logger *_logger;
    // Regex
    QRegularExpression _regex;
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("logcat", name);
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("logcat", key);
    }
    // Tree
    QTreeWidget *_tree;
    // Toolbar
    QToolBar *_toolbar;
    // Variable
    QString _device;
private slots:
    void __clear();
    void __copy();
    void __load();
    void __logcat(const QString &);
    void __menu(const QPoint &);
    void __remove();
    void __save();
    void __start();
    void __status(const bool);
    void __stop();
    void __update();
public:
    // Constructor
    Logcat(const QString &device, QWidget *parent = 0)
        : QDialog(parent)
    {
        this->_device = device;
        this->_regex = QRegularExpression(QString(REGEX_LOGCAT));
        // Initialize
        this->initialize();
    }
    // Event
    void closeEvent(QCloseEvent *);
    // Desctructor
    ~Logcat() { }
};

} // namespace Dialog
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_DIALOG_LOGCAT_H
