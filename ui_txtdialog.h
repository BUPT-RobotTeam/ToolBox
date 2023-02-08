/********************************************************************************
** Form generated from reading UI file 'txtdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TXTDIALOG_H
#define UI_TXTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_txtDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;

    void setupUi(QDialog *txtDialog)
    {
        if (txtDialog->objectName().isEmpty())
            txtDialog->setObjectName(QString::fromUtf8("txtDialog"));
        txtDialog->resize(934, 768);
        verticalLayout = new QVBoxLayout(txtDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textEdit = new QTextEdit(txtDialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setTabStopWidth(80);

        verticalLayout->addWidget(textEdit);


        retranslateUi(txtDialog);

        QMetaObject::connectSlotsByName(txtDialog);
    } // setupUi

    void retranslateUi(QDialog *txtDialog)
    {
        txtDialog->setWindowTitle(QCoreApplication::translate("txtDialog", "Dialog", nullptr));
        textEdit->setHtml(QCoreApplication::translate("txtDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/res/path_image/SBlsw.png\" /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class txtDialog: public Ui_txtDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TXTDIALOG_H
