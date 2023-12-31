/********************************************************************************
** Form generated from reading UI file 'pagesettings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGESETTINGS_H
#define UI_PAGESETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageSettings
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *uiScaleLabel;
    QDoubleSpinBox *uiScaleBox;
    QCheckBox *uiAutoScaleBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lang_label;
    QComboBox *lang_comboBox;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *PageSettings)
    {
        if (PageSettings->objectName().isEmpty())
            PageSettings->setObjectName(QString::fromUtf8("PageSettings"));
        PageSettings->resize(745, 352);
        verticalLayout_2 = new QVBoxLayout(PageSettings);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frame = new QFrame(PageSettings);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Sunken);
        frame->setLineWidth(1);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        uiScaleLabel = new QLabel(frame);
        uiScaleLabel->setObjectName(QString::fromUtf8("uiScaleLabel"));

        horizontalLayout->addWidget(uiScaleLabel);

        uiScaleBox = new QDoubleSpinBox(frame);
        uiScaleBox->setObjectName(QString::fromUtf8("uiScaleBox"));
        uiScaleBox->setMinimum(1.000000000000000);
        uiScaleBox->setMaximum(3.000000000000000);
        uiScaleBox->setSingleStep(0.100000000000000);

        horizontalLayout->addWidget(uiScaleBox);

        uiAutoScaleBox = new QCheckBox(frame);
        uiAutoScaleBox->setObjectName(QString::fromUtf8("uiAutoScaleBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(uiAutoScaleBox->sizePolicy().hasHeightForWidth());
        uiAutoScaleBox->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(uiAutoScaleBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lang_label = new QLabel(frame);
        lang_label->setObjectName(QString::fromUtf8("lang_label"));

        horizontalLayout_3->addWidget(lang_label);

        lang_comboBox = new QComboBox(frame);
        lang_comboBox->addItem(QString());
        lang_comboBox->addItem(QString());
        lang_comboBox->setObjectName(QString::fromUtf8("lang_comboBox"));
        lang_comboBox->setTabletTracking(true);

        horizontalLayout_3->addWidget(lang_comboBox);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_2->addWidget(frame);


        retranslateUi(PageSettings);

        QMetaObject::connectSlotsByName(PageSettings);
    } // setupUi

    void retranslateUi(QWidget *PageSettings)
    {
        PageSettings->setWindowTitle(QCoreApplication::translate("PageSettings", "Form", nullptr));
        uiScaleLabel->setText(QCoreApplication::translate("PageSettings", "UI Scale Factor   (restart required)", nullptr));
#if QT_CONFIG(tooltip)
        uiScaleBox->setToolTip(QCoreApplication::translate("PageSettings", "<html><head/><body><p>Scale the user intefrace with this factor. Useful for high resolution monitors. VESC Tool must be restarted for this setting to take effect.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        uiAutoScaleBox->setToolTip(QCoreApplication::translate("PageSettings", "<html><head/><body><p>Try to determine the scaling factor automatically from the screen resolution and the system font settings. VESC Tool must be restarted for this setting to take effect.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        uiAutoScaleBox->setText(QCoreApplication::translate("PageSettings", "Auto", nullptr));
        lang_label->setText(QCoreApplication::translate("PageSettings", "Language Setting  (restart required)", nullptr));
        lang_comboBox->setItemText(0, QCoreApplication::translate("PageSettings", "English", nullptr));
        lang_comboBox->setItemText(1, QCoreApplication::translate("PageSettings", "\347\256\200\344\275\223\344\270\255\346\226\207", nullptr));

        lang_comboBox->setCurrentText(QCoreApplication::translate("PageSettings", "English", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageSettings: public Ui_PageSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGESETTINGS_H
