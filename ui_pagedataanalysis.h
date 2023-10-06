/********************************************************************************
** Form generated from reading UI file 'pagedataanalysis.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEDATAANALYSIS_H
#define UI_PAGEDATAANALYSIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "widgets/vtextbrowser.h"

QT_BEGIN_NAMESPACE

class Ui_PageDataAnalysis
{
public:
    QVBoxLayout *verticalLayout;
    VTextBrowser *textEdit;

    void setupUi(QWidget *PageDataAnalysis)
    {
        if (PageDataAnalysis->objectName().isEmpty())
            PageDataAnalysis->setObjectName(QString::fromUtf8("PageDataAnalysis"));
        PageDataAnalysis->resize(400, 300);
        verticalLayout = new QVBoxLayout(PageDataAnalysis);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textEdit = new VTextBrowser(PageDataAnalysis);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);


        retranslateUi(PageDataAnalysis);

        QMetaObject::connectSlotsByName(PageDataAnalysis);
    } // setupUi

    void retranslateUi(QWidget *PageDataAnalysis)
    {
        PageDataAnalysis->setWindowTitle(QCoreApplication::translate("PageDataAnalysis", "Form", nullptr));
        textEdit->setHtml(QCoreApplication::translate("PageDataAnalysis", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:600;\">\346\225\260\346\215\256\345\210\206\346\236\220</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:20pt; font-weight:600;\"><br /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:20pt; font-weight:600;\"><br /></p>\n"
"<p align=\"center\""
                        " style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">\344\270\262\345\217\243\347\244\272\346\263\242\345\231\250\357\274\232\347\252\227\345\217\243\345\244\247\345\260\217\345\217\257\350\260\203\346\225\264\357\274\214\346\224\257\346\214\20110\351\200\232\351\201\223\344\270\262\345\217\243\346\225\260\346\215\256\346\230\276\347\244\272\357\274\214\346\263\242\345\275\242\350\207\252\345\212\250\350\260\203\346\225\264\357\274\214\345\217\257\345\257\274\345\207\272/\345\257\274\345\205\245\346\225\260\346\215\256\343\200\202</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">\346\203\257\346\200\247\346\265\213\351\207\217\345\215\225\345\205\203\346\225\260\346\215\256\357\274\232\346\224\257\346\214\201\345\257\271\346\203\257\346\200\247\346"
                        "\265\213\351\207\217\345\215\225\345\205\203\347\232\204\346\263\242\345\275\242\346\230\276\347\244\272\350\276\223\345\207\272\357\274\214\345\220\214\346\227\266\350\277\233\350\241\2143D\344\273\277\347\234\237\343\200\202</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageDataAnalysis: public Ui_PageDataAnalysis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEDATAANALYSIS_H
