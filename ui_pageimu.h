/********************************************************************************
** Form generated from reading UI file 'pageimu.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEIMU_H
#define UI_PAGEIMU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "widgets/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_PageImu
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QCustomPlot *rpyPlot;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter;
    QCustomPlot *accelPlot;
    QCustomPlot *gyroPlot;
    QCustomPlot *magPlot;
    QWidget *tab_3;
    QVBoxLayout *layout3d;
    QCheckBox *useYawBox;

    void setupUi(QWidget *PageImu)
    {
        if (PageImu->objectName().isEmpty())
            PageImu->setObjectName(QString::fromUtf8("PageImu"));
        PageImu->resize(964, 658);
        verticalLayout = new QVBoxLayout(PageImu);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(PageImu);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        rpyPlot = new QCustomPlot(tab);
        rpyPlot->setObjectName(QString::fromUtf8("rpyPlot"));

        verticalLayout_2->addWidget(rpyPlot);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        splitter = new QSplitter(tab_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        accelPlot = new QCustomPlot(splitter);
        accelPlot->setObjectName(QString::fromUtf8("accelPlot"));
        splitter->addWidget(accelPlot);
        gyroPlot = new QCustomPlot(splitter);
        gyroPlot->setObjectName(QString::fromUtf8("gyroPlot"));
        splitter->addWidget(gyroPlot);
        magPlot = new QCustomPlot(splitter);
        magPlot->setObjectName(QString::fromUtf8("magPlot"));
        splitter->addWidget(magPlot);

        verticalLayout_3->addWidget(splitter);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        layout3d = new QVBoxLayout(tab_3);
        layout3d->setObjectName(QString::fromUtf8("layout3d"));
        useYawBox = new QCheckBox(tab_3);
        useYawBox->setObjectName(QString::fromUtf8("useYawBox"));

        layout3d->addWidget(useYawBox);

        tabWidget->addTab(tab_3, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(PageImu);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PageImu);
    } // setupUi

    void retranslateUi(QWidget *PageImu)
    {
        PageImu->setWindowTitle(QCoreApplication::translate("PageImu", "Form", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("PageImu", "Roll/Pitch/Yaw", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("PageImu", "Accel/Gyro/Mag", nullptr));
        useYawBox->setText(QCoreApplication::translate("PageImu", "Use Yaw (will drift)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("PageImu", "3D Plot", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageImu: public Ui_PageImu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEIMU_H
