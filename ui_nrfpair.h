/********************************************************************************
** Form generated from reading UI file 'nrfpair.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NRFPAIR_H
#define UI_NRFPAIR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NrfPair
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *helpButton;
    QPushButton *startButton;
    QDoubleSpinBox *timeBox;
    QLabel *countLabel;

    void setupUi(QWidget *NrfPair)
    {
        if (NrfPair->objectName().isEmpty())
            NrfPair->setObjectName(QString::fromUtf8("NrfPair"));
        NrfPair->resize(356, 84);
        verticalLayout = new QVBoxLayout(NrfPair);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(NrfPair);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        helpButton = new QPushButton(groupBox);
        helpButton->setObjectName(QString::fromUtf8("helpButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(helpButton->sizePolicy().hasHeightForWidth());
        helpButton->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/icons/Help-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        helpButton->setIcon(icon);

        horizontalLayout->addWidget(helpButton);

        startButton = new QPushButton(groupBox);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        sizePolicy.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/icons/Circled Play-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        startButton->setIcon(icon1);

        horizontalLayout->addWidget(startButton);

        timeBox = new QDoubleSpinBox(groupBox);
        timeBox->setObjectName(QString::fromUtf8("timeBox"));
        timeBox->setDecimals(1);
        timeBox->setValue(10.000000000000000);

        horizontalLayout->addWidget(timeBox);

        countLabel = new QLabel(groupBox);
        countLabel->setObjectName(QString::fromUtf8("countLabel"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        countLabel->setFont(font);
        countLabel->setFrameShape(QFrame::Box);
        countLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(countLabel);


        verticalLayout->addWidget(groupBox);


        retranslateUi(NrfPair);

        QMetaObject::connectSlotsByName(NrfPair);
    } // setupUi

    void retranslateUi(QWidget *NrfPair)
    {
        NrfPair->setWindowTitle(QCoreApplication::translate("NrfPair", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("NrfPair", "NRF Pairing", nullptr));
        helpButton->setText(QString());
#if QT_CONFIG(tooltip)
        startButton->setToolTip(QCoreApplication::translate("NrfPair", "Start Pairing", nullptr));
#endif // QT_CONFIG(tooltip)
        startButton->setText(QString());
#if QT_CONFIG(tooltip)
        timeBox->setToolTip(QCoreApplication::translate("NrfPair", "Stay in pairing mode for this amount of time", nullptr));
#endif // QT_CONFIG(tooltip)
        timeBox->setPrefix(QCoreApplication::translate("NrfPair", "Time: ", nullptr));
        timeBox->setSuffix(QCoreApplication::translate("NrfPair", " s", nullptr));
        countLabel->setText(QCoreApplication::translate("NrfPair", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NrfPair: public Ui_NrfPair {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NRFPAIR_H
