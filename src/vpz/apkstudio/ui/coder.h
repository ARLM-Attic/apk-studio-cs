#ifndef VPZ_APKSTUDIO_UI_CODER_H
#define VPZ_APKSTUDIO_UI_CODER_H

#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QApplication>
#include <QClipboard>
#include <QCompleter>
#include <QFile>
#include <QFileInfo>
#include <QFocusEvent>
#include <QFont>
#include <QFontMetrics>
#include <QObject>
#include <QMenu>
#include <QMouseEvent>
#include <QPalette>
#include <QPainter>
#include <QPaintEvent>
#include <QPair>
#include <QPlainTextEdit>
#include <QPoint>
#include <QScrollBar>
#include <QString>
#include <QStandardItemModel>
#include <QTextDocumentFragment>
#include <QTextStream>

#include "completer.h"
#include "highlighter.h"
#include "xmlhighlighter.h"
#include "../bridge/constant.h"
#include "../utility/configuration.h"
#include "../utility/resource.h"

namespace VPZ {
namespace APKStudio {
namespace UI {

class Coder : public QPlainTextEdit
{
    Q_OBJECT
private:
    // Action
    QAction *_close;
    QAction *_copy;
    QAction *_cut;
    QAction *_paste;
    QAction *_save;
    QAction *_select_all;
    // Pair
    QPair<int, int> _cache;
    Completer *_completer;
    QWidget *_liner;
    QMenu *_menu;
    QString _path;
    QString cursored();
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("editors", name);
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("editors", key);
    }
private slots:
    void highlight();
    void complete(const QString &);
    void updateLinerArea(const QRect &, const int);
    void updateLinerAreaWidth(const int);
    void __menu(const QPoint &point);
protected:
    void focusInEvent(QFocusEvent *);
    void keyPressEvent(QKeyEvent *);
    void resizeEvent(QResizeEvent *);
public:
    Coder(QWidget * = 0);
    QString path();
    void path(const QString &);
    void read(const QString &);
    bool revert();
    bool save();
    bool selected();
public slots:
    int linerAreaWidth();
    void linerPaintEvent(QPaintEvent *);
    void __close()
    {
        emit close_();
    }
    void __copy()
    {
        this->copy();
    }
    void __cut()
    {
        this->cut();
    }
    void __paste()
    {
        this->paste();
    }
    void __save()
    {
        emit save_();
    }
    void __select_all()
    {
        this->selectAll();
    }
signals:
    void changed(const int, const int);
    void close_();
    void save_();
};

class Liner : public QWidget
{
private:
    Coder *_coder;
protected:
    void paintEvent(QPaintEvent *event) {
        this->_coder->linerPaintEvent(event);
    }
public:
    Liner(Coder *coder) : QWidget(coder) {
        this->_coder = coder;
    }
    QSize sizeHint() const {
        return QSize(this->_coder->linerAreaWidth(), 0);
    }
};

} // namespace UI
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_UI_CODER_H
