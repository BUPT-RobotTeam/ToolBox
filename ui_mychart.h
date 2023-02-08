/********************************************************************************
** Form generated from reading UI file 'mychart.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYCHART_H
#define UI_MYCHART_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qchartview.h"

QT_BEGIN_NAMESPACE

class Ui_Mychart
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QChartView *graphicsView;

    void setupUi(QWidget *Mychart)
    {
        if (Mychart->objectName().isEmpty())
            Mychart->setObjectName(QString::fromUtf8("Mychart"));
        Mychart->resize(980, 738);
        verticalLayout_2 = new QVBoxLayout(Mychart);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        graphicsView = new QChartView(Mychart);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        verticalLayout->addWidget(graphicsView);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(Mychart);

        QMetaObject::connectSlotsByName(Mychart);
    } // setupUi

    void retranslateUi(QWidget *Mychart)
    {
        Mychart->setWindowTitle(QCoreApplication::translate("Mychart", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Mychart: public Ui_Mychart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCHART_H
