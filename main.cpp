/**
 * @mainpage ToolBox文档
 * @section intro_sec Introduction
 * 欢迎使用Tool Box;
 * 基于Benjamin Vedder的vesc_tool_1.24修改而来
 * 在原软件框架下增加通用串口示波器，保留IMU数据显示，并进行了部分汉化
 * 本软件仅供个人学习、研究之用
 * @section install_sec Installation
 * 直接下载使用，注意需要申请mosek的学术许可证
 * @subsection install_dependencies Installing Dependencies
 *  Mosek ：我们使用 mosek 来求解二阶锥程序 (SOCP)。要使用 mosek，您应该在此处批准学术许可。
 * 学术许可证是免费的，而且很容易批准。
 * 许可证文件应放在用户主目录下名为“mosek”的文件夹中（$HOME/mosek/mosek.lic 或 %USERPROFILE%@\mosek@\mosek.lic）。\n
 * 在大多数典型情况下，这将是：\n
 *  1. /home/YOUR_USER_NAME/mosek/mosek.lic (Linux)\n
 *  2. /Users/YOUR_USER_NAME/mosek/mosek.lic (OSX)\n
 *  3. C:@\Users@\YOUR_USER_NAME@\mosek@\mosek.lic@\ (Windows)\n

 */

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
