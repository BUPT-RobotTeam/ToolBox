/********************************************************************************
** Form generated from reading UI file 'pagenone.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGENONE_H
#define UI_PAGENONE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageNone
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_3;
    QPushButton *pushButton;

    void setupUi(QWidget *PageNone)
    {
        if (PageNone->objectName().isEmpty())
            PageNone->setObjectName(QString::fromUtf8("PageNone"));
        PageNone->resize(1111, 601);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PageNone->sizePolicy().hasHeightForWidth());
        PageNone->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(PageNone);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label = new QLabel(PageNone);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(PageNone);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_2 = new QPushButton(PageNone);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        doubleSpinBox = new QDoubleSpinBox(PageNone);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setMinimum(-99.000000000000000);

        horizontalLayout->addWidget(doubleSpinBox);

        label_3 = new QLabel(PageNone);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);


        verticalLayout->addLayout(horizontalLayout);

        pushButton = new QPushButton(PageNone);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(PageNone);

        QMetaObject::connectSlotsByName(PageNone);
    } // setupUi

    void retranslateUi(QWidget *PageNone)
    {
        PageNone->setWindowTitle(QCoreApplication::translate("PageNone", "Form", nullptr));
        label->setText(QCoreApplication::translate("PageNone", "\347\251\272\351\241\265\351\235\242\357\274\214\346\226\271\344\276\277\344\272\214\346\254\241\345\274\200\345\217\221\344\275\277\347\224\250\357\274\214\346\227\240\351\234\200\345\205\263\346\263\250\347\252\227\345\217\243\346\241\206\346\236\266", nullptr));
        label_2->setText(QCoreApplication::translate("PageNone", "test label", nullptr));
        pushButton_2->setText(QCoreApplication::translate("PageNone", "PushButton", nullptr));
        label_3->setText(QCoreApplication::translate("PageNone", "TextLabel", nullptr));
        pushButton->setText(QCoreApplication::translate("PageNone", "Connect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageNone: public Ui_PageNone {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGENONE_H
