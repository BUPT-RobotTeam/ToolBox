/********************************************************************************
** Form generated from reading UI file 'pagewelcome.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEWELCOME_H
#define UI_PAGEWELCOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "widgets/imagewidget.h"

QT_BEGIN_NAMESPACE

class Ui_PageWelcome
{
public:
    QVBoxLayout *verticalLayout;
    ImageWidget *bgWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;

    void setupUi(QWidget *PageWelcome)
    {
        if (PageWelcome->objectName().isEmpty())
            PageWelcome->setObjectName(QString::fromUtf8("PageWelcome"));
        PageWelcome->resize(667, 400);
        verticalLayout = new QVBoxLayout(PageWelcome);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        bgWidget = new ImageWidget(PageWelcome);
        bgWidget->setObjectName(QString::fromUtf8("bgWidget"));
        verticalLayout_2 = new QVBoxLayout(bgWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(bgWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setWordWrap(true);

        verticalLayout_2->addWidget(label);

        verticalLayout_2->setStretch(0, 1);

        verticalLayout->addWidget(bgWidget);


        retranslateUi(PageWelcome);

        QMetaObject::connectSlotsByName(PageWelcome);
    } // setupUi

    void retranslateUi(QWidget *PageWelcome)
    {
        PageWelcome->setWindowTitle(QCoreApplication::translate("PageWelcome", "Form", nullptr));
        label->setText(QCoreApplication::translate("PageWelcome", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:26pt; font-weight:600;\">\346\254\242\350\277\216\344\275\277\347\224\250Tool Box</span></p>\n"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:600;\"><br /></span><span style=\" font-size:16pt;\">\345\237\272\344\272\216Benjamin Vedder\347\232\204vesc_tool_1.24\344\277\256\346\224\271\350\200\214\346\235\245</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; m"
                        "argin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt;\">\345\234\250\345\216\237\350\275\257\344\273\266\346\241\206\346\236\266\344\270\213\345\242\236\345\212\240\351\200\232\347\224\250\344\270\262\345\217\243\347\244\272\346\263\242\345\231\250\357\274\214\344\277\235\347\225\231IMU\346\225\260\346\215\256\346\230\276\347\244\272\357\274\214\345\271\266\350\277\233\350\241\214\344\272\206\351\203\250\345\210\206\346\261\211\345\214\226</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:16pt;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt;\">\346\234\254\350\275\257\344\273\266\344\273\205\344\276\233\344\270\252\344\272\272\345\255\246\344\271\240\343\200\201\347\240\224\347\251\266\344\271"
                        "\213\347\224\250</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageWelcome: public Ui_PageWelcome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEWELCOME_H
