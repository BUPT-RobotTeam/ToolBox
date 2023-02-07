#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>
#include <QSettings>
#include <QDesktopWidget>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    // Settings
    QCoreApplication::setOrganizationName("ToolBox");
    QCoreApplication::setOrganizationDomain("none");
    QCoreApplication::setApplicationName("Tool Box");

    // DPI settings
    // TODO: http://www.qcustomplot.com/index.php/support/forum/1344

    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QCoreApplication::setAttribute(Qt::AA_Use96Dpi);

    QSettings set;
    bool scaleAuto = true;
    double scale = 1.0;
    int language_index = 1;

    if (set.contains("app_scale_auto"))
    {
        scaleAuto = set.value("app_scale_auto").toBool();
    }
    else
    {
        set.setValue("app_scale_auto", scaleAuto);
    }

    if (set.contains("language_index"))
    {
        language_index = set.value("language_index").toInt();
    }
    else
    {
        set.setValue("language_index", language_index);
    }

    //Translation
    static QTranslator qtTranslator;
    if (language_index == 1)
        qtTranslator.load("lang_Chinese.qm", "://res//language");
    else
        qtTranslator.load("lang_English.qm", "://res//language");

    //UI scale
    if (scaleAuto)
    {
        QApplication tmp(argc, argv);
        QRect rec = tmp.desktop()->screenGeometry();
        int height = rec.height();
        int width = rec.width();
        double ptFont = tmp.font().pointSizeF();
        if (ptFont < 0.0)
        {
            ptFont = tmp.font().pixelSize();
        }

        if (width > 3000 && height > 1700)
        {
            scale = 1.5;
        }
        else
        {
            if (ptFont > 11.0)
            {
                scale = ptFont / 11.0;
            }
        }

        set.setValue("app_scale_factor", scale);
    }
    else if (set.contains("app_scale_factor"))
    {
        scale = set.value("app_scale_factor").toDouble();
    }

    set.setValue("app_scale_factor", scale);

    if (scale > 1.01)
    {
        qputenv("QT_SCALE_FACTOR", QString::number(scale).toLocal8Bit());
    }

    QApplication a(argc, argv);
    a.installTranslator(&qtTranslator);

    // Fonts
    QFontDatabase::addApplicationFont("://res/fonts/DejaVuSans.ttf");
    QFontDatabase::addApplicationFont("://res/fonts/DejaVuSans-Bold.ttf");
    QFontDatabase::addApplicationFont("://res/fonts/DejaVuSans-BoldOblique.ttf");
    QFontDatabase::addApplicationFont("://res/fonts/DejaVuSans-Oblique.ttf");
    QFontDatabase::addApplicationFont("://res/fonts/DejaVuSansMono.ttf");
    QFontDatabase::addApplicationFont("://res/fonts/DejaVuSansMono-Bold.ttf");
    QFontDatabase::addApplicationFont("://res/fonts/DejaVuSansMono-BoldOblique.ttf");
    QFontDatabase::addApplicationFont("://res/fonts/DejaVuSansMono-Oblique.ttf");

    qApp->setFont(QFont("DejaVu Sans", 11));

    // Style
    a.setStyleSheet("");
    a.setStyle(QStyleFactory::create("Fusion"));

    MainWindow w;
    w.show();

    return a.exec();
}
