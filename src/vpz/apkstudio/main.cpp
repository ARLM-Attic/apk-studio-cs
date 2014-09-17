#include <QApplication>
#include <QCoreApplication>
#include <QFontDatabase>
#include <QStyleFactory>
#include <QTimer>
#include <QTranslator>

#include "bridge/constant.h"
#include "ui/ide.h"
#include "utility/configuration.h"
#include "utility/resource.h"

using namespace VPZ::APKStudio;

int main(int count, char *arguments[])
{
    // Settings
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QCoreApplication::setOrganizationDomain(APPLICATION_DOMAIN);
    QCoreApplication::setOrganizationName(APPLICATION_ORGANIZATION);
    // Application
    QApplication qtapp(count, arguments);
    // Icon
    qtapp.setWindowIcon(Utility::Resource::icon("application", "common"));
/*
#ifdef Q_OS_LINUX
    qtapp.setStyle(QStyleFactory::create("gtk+"));
#endif
*/
    // Translator
    QTranslator translator;
    translator.load("en", PATH_LANGUAGE);
    qtapp.installTranslator(&translator);
    // Fonts
    QFontDatabase::addApplicationFont(QString(PATH_FONT).append("sourcecodepro-regular.ttf"));
    QFontDatabase::addApplicationFont(QString(PATH_FONT).append("sourcecodepro-bold.ttf"));
    // Workbench
    UI::IDE ide;
    ide.show();
    QTimer::singleShot(0, &ide, SLOT(__initialize()));
    // Return
    return qtapp.exec();
}
