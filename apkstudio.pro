#-------------------------------------------------
#
# Project created by QtCreator 2014-05-21T10:52:57
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = apkstudio
TEMPLATE = app

SOURCES += \
    src/vpz/apkstudio/ui/editors.cpp \
    src/vpz/apkstudio/ui/ide.cpp \
    src/vpz/apkstudio/ui/menubar.cpp \
    src/vpz/apkstudio/ui/projects.cpp \
    src/vpz/apkstudio/ui/toolbar.cpp \
    src/vpz/apkstudio/main.cpp \
    src/vpz/apkstudio/dialog/settings.cpp \
    src/vpz/apkstudio/utility/format.cpp \
    src/vpz/apkstudio/utility/ui.cpp \
    src/vpz/apkstudio/ui/devices.cpp \
    src/vpz/apkstudio/ui/completer.cpp \
    src/vpz/apkstudio/ui/highlighter.cpp \
    src/vpz/apkstudio/ui/coder.cpp \
    src/vpz/apkstudio/ui/statusbar.cpp \
    src/vpz/apkstudio/ui/xmlhighlighter.cpp \
    src/vpz/apkstudio/runtime/screenshot.cpp \
    src/vpz/apkstudio/dialog/project.cpp \
    src/vpz/apkstudio/runtime/refresh.cpp \
    src/vpz/apkstudio/runtime/adb.cpp \
    src/vpz/apkstudio/runtime/decompile.cpp \
    src/vpz/apkstudio/runtime/recompile.cpp \
    src/vpz/apkstudio/runtime/framework.cpp \
    src/vpz/apkstudio/dialog/find.cpp \
    src/vpz/apkstudio/runtime/build.cpp \
    src/vpz/apkstudio/dialog/logcat.cpp \
    src/vpz/apkstudio/runtime/logger.cpp \
    src/vpz/apkstudio/utility/text.cpp \
    src/vpz/apkstudio/dialog/information.cpp \
    src/vpz/apkstudio/runtime/imei.cpp \
    src/vpz/apkstudio/dialog/browser.cpp \
    src/vpz/apkstudio/ui/partitions.cpp \
    src/vpz/apkstudio/ui/files.cpp \
    src/vpz/apkstudio/ui/applications.cpp \
    src/vpz/apkstudio/runtime/package.cpp \
    src/vpz/apkstudio/runtime/partition.cpp \
    src/vpz/apkstudio/runtime/file.cpp \
    src/vpz/apkstudio/runtime/remount.cpp \
    src/vpz/apkstudio/runtime/state.cpp \
    src/vpz/apkstudio/runtime/uninstall.cpp \
    src/vpz/apkstudio/runtime/install.cpp \
    src/vpz/apkstudio/dialog/add.cpp \
    src/vpz/apkstudio/runtime/pull.cpp \
    src/vpz/apkstudio/runtime/chmod.cpp \
    src/vpz/apkstudio/dialog/permissions.cpp \
    src/vpz/apkstudio/runtime/rm.cpp \
    src/vpz/apkstudio/runtime/push.cpp \
    src/vpz/apkstudio/runtime/new.cpp \
    src/vpz/apkstudio/runtime/rename.cpp \
    src/vpz/apkstudio/dialog/about.cpp

HEADERS += \
    src/vpz/apkstudio/bridge/constant.h \
    src/vpz/apkstudio/bridge/variant.h \
    src/vpz/apkstudio/ui/editors.h \
    src/vpz/apkstudio/ui/ide.h \
    src/vpz/apkstudio/ui/menubar.h \
    src/vpz/apkstudio/ui/projects.h \
    src/vpz/apkstudio/ui/toolbar.h \
    src/vpz/apkstudio/dialog/settings.h \
    src/vpz/apkstudio/utility/configuration.h \
    src/vpz/apkstudio/utility/format.h \
    src/vpz/apkstudio/utility/resource.h \
    src/vpz/apkstudio/utility/ui.h \
    src/vpz/apkstudio/ui/devices.h \
    src/vpz/apkstudio/ui/completer.h \
    src/vpz/apkstudio/ui/highlighter.h \
    src/vpz/apkstudio/ui/coder.h \
    src/vpz/apkstudio/ui/statusbar.h \
    src/vpz/apkstudio/ui/xmlhighlighter.h \
    src/vpz/apkstudio/runtime/screenshot.h \
    src/vpz/apkstudio/dialog/project.h \
    src/vpz/apkstudio/runtime/refresh.h \
    src/vpz/apkstudio/runtime/adb.h \
    src/vpz/apkstudio/runtime/decompile.h \
    src/vpz/apkstudio/runtime/recompile.h \
    src/vpz/apkstudio/runtime/framework.h \
    src/vpz/apkstudio/dialog/find.h \
    src/vpz/apkstudio/runtime/build.h \
    src/vpz/apkstudio/dialog/logcat.h \
    src/vpz/apkstudio/runtime/logger.h \
    src/vpz/apkstudio/utility/text.h \
    src/vpz/apkstudio/dialog/information.h \
    src/vpz/apkstudio/runtime/imei.h \
    src/vpz/apkstudio/dialog/browser.h \
    src/vpz/apkstudio/ui/partitions.h \
    src/vpz/apkstudio/ui/files.h \
    src/vpz/apkstudio/ui/applications.h \
    src/vpz/apkstudio/runtime/package.h \
    src/vpz/apkstudio/runtime/partition.h \
    src/vpz/apkstudio/runtime/file.h \
    src/vpz/apkstudio/runtime/remount.h \
    src/vpz/apkstudio/runtime/uninstall.h \
    src/vpz/apkstudio/runtime/install.h \
    src/vpz/apkstudio/dialog/add.h \
    src/vpz/apkstudio/runtime/pull.h \
    src/vpz/apkstudio/runtime/chmod.h \
    src/vpz/apkstudio/dialog/permissions.h \
    src/vpz/apkstudio/runtime/rm.h \
    src/vpz/apkstudio/runtime/push.h \
    src/vpz/apkstudio/runtime/new.h \
    src/vpz/apkstudio/runtime/rename.h \
    src/vpz/apkstudio/dialog/about.h \
    src/vpz/apkstudio/runtime/state.h

RESOURCES += \
    res/icon/icon.qrc \
    res/language/language.qrc \
    res/completion/completion.qrc \
    res/highlight/highlight.qrc \
    res/font/font.qrc

TRANSLATIONS += \
    res/language/en.ts

OTHER_FILES += \
    res/icon/windows.rc

win32:RC_FILE = res/icon/windows.rc
