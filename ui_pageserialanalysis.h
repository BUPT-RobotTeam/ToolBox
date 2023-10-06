/********************************************************************************
** Form generated from reading UI file 'pageserialanalysis.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGESERIALANALYSIS_H
#define UI_PAGESERIALANALYSIS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "widgets/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_PageSerialAnalysis
{
public:
    QVBoxLayout *verticalLayout_7;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTextBrowser *cmdBrowser;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QCustomPlot *generalPlot;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_25;
    QGridLayout *gridLayout;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_6;
    QLabel *CH1_dataLabel;
    QLabel *CH5_dataLabel;
    QLabel *CH7_dataLabel;
    QCheckBox *checkBox_4;
    QLabel *CH6_dataLabel;
    QLabel *CH0_dataLabel;
    QCheckBox *checkBox_1;
    QLabel *CH4_dataLabel;
    QCheckBox *checkBox_5;
    QLabel *CH3_dataLabel;
    QCheckBox *checkBox_0;
    QCheckBox *checkBox_3;
    QLabel *CH2_dataLabel;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *rescaleButton;
    QPushButton *zoomVButton;
    QPushButton *zoomHButton;
    QPushButton *autoScaleButton;
    QPushButton *plotStopButton;
    QPushButton *legendVisibleButton;
    QPushButton *plotClearButton;
    QPushButton *cmdBrowserClearButton;
    QSpacerItem *horizontalSpacer;
    QDoubleSpinBox *xAxisStepDoubleSpinBox;
    QSpinBox *maxPointsSpinBox;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_11;
    QLineEdit *csvFileEdit;
    QPushButton *csvChooseDirButton;
    QCheckBox *csvEnableLogBox;
    QPushButton *newDataFile;
    QPushButton *loadDataButton;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_13;

    void setupUi(QWidget *PageSerialAnalysis)
    {
        if (PageSerialAnalysis->objectName().isEmpty())
            PageSerialAnalysis->setObjectName(QString::fromUtf8("PageSerialAnalysis"));
        PageSerialAnalysis->resize(1433, 506);
        verticalLayout_7 = new QVBoxLayout(PageSerialAnalysis);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(PageSerialAnalysis);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Triangular);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_6 = new QVBoxLayout(tab);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        splitter_2 = new QSplitter(tab);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy);
        splitter_2->setFrameShadow(QFrame::Plain);
        splitter_2->setOrientation(Qt::Horizontal);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(200);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy1);
        splitter->setOrientation(Qt::Vertical);
        splitter->setHandleWidth(2);
        verticalLayoutWidget = new QWidget(splitter);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        cmdBrowser = new QTextBrowser(verticalLayoutWidget);
        cmdBrowser->setObjectName(QString::fromUtf8("cmdBrowser"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cmdBrowser->sizePolicy().hasHeightForWidth());
        cmdBrowser->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(cmdBrowser);

        splitter->addWidget(verticalLayoutWidget);
        verticalLayoutWidget_2 = new QWidget(splitter);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        generalPlot = new QCustomPlot(verticalLayoutWidget_2);
        generalPlot->setObjectName(QString::fromUtf8("generalPlot"));
        sizePolicy2.setHeightForWidth(generalPlot->sizePolicy().hasHeightForWidth());
        generalPlot->setSizePolicy(sizePolicy2);

        verticalLayout_2->addWidget(generalPlot);

        splitter->addWidget(verticalLayoutWidget_2);
        splitter_2->addWidget(splitter);
        verticalLayoutWidget_3 = new QWidget(splitter_2);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        splitter_2->addWidget(verticalLayoutWidget_3);

        verticalLayout_4->addWidget(splitter_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        checkBox_2 = new QCheckBox(tab);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setChecked(true);

        gridLayout->addWidget(checkBox_2, 0, 3, 1, 1);

        checkBox_7 = new QCheckBox(tab);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));
        checkBox_7->setChecked(true);

        gridLayout->addWidget(checkBox_7, 0, 8, 1, 1);

        checkBox_6 = new QCheckBox(tab);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));
        checkBox_6->setChecked(true);

        gridLayout->addWidget(checkBox_6, 0, 7, 1, 1);

        CH1_dataLabel = new QLabel(tab);
        CH1_dataLabel->setObjectName(QString::fromUtf8("CH1_dataLabel"));
        CH1_dataLabel->setFrameShape(QFrame::Box);

        gridLayout->addWidget(CH1_dataLabel, 1, 2, 1, 1);

        CH5_dataLabel = new QLabel(tab);
        CH5_dataLabel->setObjectName(QString::fromUtf8("CH5_dataLabel"));
        CH5_dataLabel->setFrameShape(QFrame::Box);
        CH5_dataLabel->setFrameShadow(QFrame::Plain);

        gridLayout->addWidget(CH5_dataLabel, 1, 6, 1, 1);

        CH7_dataLabel = new QLabel(tab);
        CH7_dataLabel->setObjectName(QString::fromUtf8("CH7_dataLabel"));
        CH7_dataLabel->setFrameShape(QFrame::Box);

        gridLayout->addWidget(CH7_dataLabel, 1, 8, 1, 1);

        checkBox_4 = new QCheckBox(tab);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setChecked(true);

        gridLayout->addWidget(checkBox_4, 0, 5, 1, 1);

        CH6_dataLabel = new QLabel(tab);
        CH6_dataLabel->setObjectName(QString::fromUtf8("CH6_dataLabel"));
        CH6_dataLabel->setFrameShape(QFrame::Box);

        gridLayout->addWidget(CH6_dataLabel, 1, 7, 1, 1);

        CH0_dataLabel = new QLabel(tab);
        CH0_dataLabel->setObjectName(QString::fromUtf8("CH0_dataLabel"));
        CH0_dataLabel->setFrameShape(QFrame::Box);

        gridLayout->addWidget(CH0_dataLabel, 1, 1, 1, 1);

        checkBox_1 = new QCheckBox(tab);
        checkBox_1->setObjectName(QString::fromUtf8("checkBox_1"));
        checkBox_1->setChecked(true);

        gridLayout->addWidget(checkBox_1, 0, 2, 1, 1);

        CH4_dataLabel = new QLabel(tab);
        CH4_dataLabel->setObjectName(QString::fromUtf8("CH4_dataLabel"));
        CH4_dataLabel->setFrameShape(QFrame::Box);

        gridLayout->addWidget(CH4_dataLabel, 1, 5, 1, 1);

        checkBox_5 = new QCheckBox(tab);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setChecked(true);

        gridLayout->addWidget(checkBox_5, 0, 6, 1, 1);

        CH3_dataLabel = new QLabel(tab);
        CH3_dataLabel->setObjectName(QString::fromUtf8("CH3_dataLabel"));
        CH3_dataLabel->setFrameShape(QFrame::Box);

        gridLayout->addWidget(CH3_dataLabel, 1, 4, 1, 1);

        checkBox_0 = new QCheckBox(tab);
        checkBox_0->setObjectName(QString::fromUtf8("checkBox_0"));
        checkBox_0->setLayoutDirection(Qt::LeftToRight);
        checkBox_0->setChecked(true);

        gridLayout->addWidget(checkBox_0, 0, 1, 1, 1);

        checkBox_3 = new QCheckBox(tab);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setChecked(true);

        gridLayout->addWidget(checkBox_3, 0, 4, 1, 1);

        CH2_dataLabel = new QLabel(tab);
        CH2_dataLabel->setObjectName(QString::fromUtf8("CH2_dataLabel"));
        CH2_dataLabel->setFrameShape(QFrame::Box);

        gridLayout->addWidget(CH2_dataLabel, 1, 3, 1, 1);


        horizontalLayout_25->addLayout(gridLayout);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        rescaleButton = new QPushButton(tab);
        rescaleButton->setObjectName(QString::fromUtf8("rescaleButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/icons/Process-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        rescaleButton->setIcon(icon);

        horizontalLayout_2->addWidget(rescaleButton);

        zoomVButton = new QPushButton(tab);
        zoomVButton->setObjectName(QString::fromUtf8("zoomVButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/icons/expand_v_off.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/res/icons/expand_v_on.png"), QSize(), QIcon::Normal, QIcon::On);
        zoomVButton->setIcon(icon1);
        zoomVButton->setCheckable(true);
        zoomVButton->setChecked(true);

        horizontalLayout_2->addWidget(zoomVButton);

        zoomHButton = new QPushButton(tab);
        zoomHButton->setObjectName(QString::fromUtf8("zoomHButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/res/icons/expand_off.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/res/icons/expand_on.png"), QSize(), QIcon::Normal, QIcon::On);
        zoomHButton->setIcon(icon2);
        zoomHButton->setCheckable(true);
        zoomHButton->setChecked(true);

        horizontalLayout_2->addWidget(zoomHButton);

        autoScaleButton = new QPushButton(tab);
        autoScaleButton->setObjectName(QString::fromUtf8("autoScaleButton"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/res/icons/size_off.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QString::fromUtf8(":/res/icons/size_on.png"), QSize(), QIcon::Normal, QIcon::On);
        autoScaleButton->setIcon(icon3);
        autoScaleButton->setCheckable(true);
        autoScaleButton->setChecked(true);

        horizontalLayout_2->addWidget(autoScaleButton);

        plotStopButton = new QPushButton(tab);
        plotStopButton->setObjectName(QString::fromUtf8("plotStopButton"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/res/icons/rt_off.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon4.addFile(QString::fromUtf8(":/res/icons/rt_on.png"), QSize(), QIcon::Normal, QIcon::On);
        plotStopButton->setIcon(icon4);
        plotStopButton->setCheckable(true);
        plotStopButton->setChecked(true);

        horizontalLayout_2->addWidget(plotStopButton);

        legendVisibleButton = new QPushButton(tab);
        legendVisibleButton->setObjectName(QString::fromUtf8("legendVisibleButton"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/res/icons/alive_off.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon5.addFile(QString::fromUtf8(":/res/icons/alive_on.png"), QSize(), QIcon::Normal, QIcon::On);
        legendVisibleButton->setIcon(icon5);
        legendVisibleButton->setCheckable(true);
        legendVisibleButton->setChecked(true);

        horizontalLayout_2->addWidget(legendVisibleButton);

        plotClearButton = new QPushButton(tab);
        plotClearButton->setObjectName(QString::fromUtf8("plotClearButton"));
        plotClearButton->setEnabled(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/res/icons/Restart-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        plotClearButton->setIcon(icon6);

        horizontalLayout_2->addWidget(plotClearButton);

        cmdBrowserClearButton = new QPushButton(tab);
        cmdBrowserClearButton->setObjectName(QString::fromUtf8("cmdBrowserClearButton"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/res/icons/Delete-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdBrowserClearButton->setIcon(icon7);

        horizontalLayout_2->addWidget(cmdBrowserClearButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        xAxisStepDoubleSpinBox = new QDoubleSpinBox(tab);
        xAxisStepDoubleSpinBox->setObjectName(QString::fromUtf8("xAxisStepDoubleSpinBox"));
        xAxisStepDoubleSpinBox->setDecimals(3);
        xAxisStepDoubleSpinBox->setMaximum(100.000000000000000);
        xAxisStepDoubleSpinBox->setSingleStep(0.005000000000000);
        xAxisStepDoubleSpinBox->setValue(0.005000000000000);

        horizontalLayout_2->addWidget(xAxisStepDoubleSpinBox);

        maxPointsSpinBox = new QSpinBox(tab);
        maxPointsSpinBox->setObjectName(QString::fromUtf8("maxPointsSpinBox"));
        maxPointsSpinBox->setMinimum(100);
        maxPointsSpinBox->setMaximum(10000);
        maxPointsSpinBox->setSingleStep(100);
        maxPointsSpinBox->setValue(1000);

        horizontalLayout_2->addWidget(maxPointsSpinBox);

        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setIconSize(QSize(12, 12));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_11 = new QLabel(tab);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_3->addWidget(label_11);

        csvFileEdit = new QLineEdit(tab);
        csvFileEdit->setObjectName(QString::fromUtf8("csvFileEdit"));

        horizontalLayout_3->addWidget(csvFileEdit);

        csvChooseDirButton = new QPushButton(tab);
        csvChooseDirButton->setObjectName(QString::fromUtf8("csvChooseDirButton"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/res/icons/Open Folder-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        csvChooseDirButton->setIcon(icon8);

        horizontalLayout_3->addWidget(csvChooseDirButton);

        csvEnableLogBox = new QCheckBox(tab);
        csvEnableLogBox->setObjectName(QString::fromUtf8("csvEnableLogBox"));

        horizontalLayout_3->addWidget(csvEnableLogBox);

        newDataFile = new QPushButton(tab);
        newDataFile->setObjectName(QString::fromUtf8("newDataFile"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/res/icons/Plus Math-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        newDataFile->setIcon(icon9);

        horizontalLayout_3->addWidget(newDataFile);

        loadDataButton = new QPushButton(tab);
        loadDataButton->setObjectName(QString::fromUtf8("loadDataButton"));

        horizontalLayout_3->addWidget(loadDataButton);


        verticalLayout_5->addLayout(horizontalLayout_3);


        horizontalLayout_25->addLayout(verticalLayout_5);


        horizontalLayout->addLayout(horizontalLayout_25);


        verticalLayout_4->addLayout(horizontalLayout);


        verticalLayout_6->addLayout(verticalLayout_4);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_8 = new QVBoxLayout(tab_2);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));

        verticalLayout_8->addLayout(verticalLayout_13);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_7->addWidget(tabWidget);


        retranslateUi(PageSerialAnalysis);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PageSerialAnalysis);
    } // setupUi

    void retranslateUi(QWidget *PageSerialAnalysis)
    {
        PageSerialAnalysis->setWindowTitle(QCoreApplication::translate("PageSerialAnalysis", "Form", nullptr));
        checkBox_2->setText(QCoreApplication::translate("PageSerialAnalysis", "CH_2", nullptr));
        checkBox_7->setText(QCoreApplication::translate("PageSerialAnalysis", "CH_7", nullptr));
        checkBox_6->setText(QCoreApplication::translate("PageSerialAnalysis", "CH_6", nullptr));
        CH1_dataLabel->setText(QCoreApplication::translate("PageSerialAnalysis", "0", nullptr));
        CH5_dataLabel->setText(QCoreApplication::translate("PageSerialAnalysis", "0", nullptr));
        CH7_dataLabel->setText(QCoreApplication::translate("PageSerialAnalysis", "0", nullptr));
        checkBox_4->setText(QCoreApplication::translate("PageSerialAnalysis", "CH_4", nullptr));
        CH6_dataLabel->setText(QCoreApplication::translate("PageSerialAnalysis", "0", nullptr));
        CH0_dataLabel->setText(QCoreApplication::translate("PageSerialAnalysis", "0", nullptr));
        checkBox_1->setText(QCoreApplication::translate("PageSerialAnalysis", "CH_1", nullptr));
        CH4_dataLabel->setText(QCoreApplication::translate("PageSerialAnalysis", "0", nullptr));
        checkBox_5->setText(QCoreApplication::translate("PageSerialAnalysis", "CH_5", nullptr));
        CH3_dataLabel->setText(QCoreApplication::translate("PageSerialAnalysis", "0", nullptr));
        checkBox_0->setText(QCoreApplication::translate("PageSerialAnalysis", "CH_0", nullptr));
        checkBox_3->setText(QCoreApplication::translate("PageSerialAnalysis", "CH_3", nullptr));
        CH2_dataLabel->setText(QCoreApplication::translate("PageSerialAnalysis", "0", nullptr));
#if QT_CONFIG(tooltip)
        rescaleButton->setToolTip(QCoreApplication::translate("PageSerialAnalysis", "Rescale plot to fit", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        rescaleButton->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        rescaleButton->setText(QString());
#if QT_CONFIG(tooltip)
        zoomVButton->setToolTip(QCoreApplication::translate("PageSerialAnalysis", "Enable vertical zoom", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        zoomVButton->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        zoomVButton->setText(QString());
#if QT_CONFIG(tooltip)
        zoomHButton->setToolTip(QCoreApplication::translate("PageSerialAnalysis", "Enable Horizontal zoom", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        zoomHButton->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        zoomHButton->setText(QString());
#if QT_CONFIG(tooltip)
        autoScaleButton->setToolTip(QCoreApplication::translate("PageSerialAnalysis", "Autoscale plots with incoming samples", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        autoScaleButton->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        autoScaleButton->setText(QString());
#if QT_CONFIG(tooltip)
        plotStopButton->setToolTip(QCoreApplication::translate("PageSerialAnalysis", "Realtime display", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        plotStopButton->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        plotStopButton->setText(QString());
#if QT_CONFIG(tooltip)
        legendVisibleButton->setToolTip(QCoreApplication::translate("PageSerialAnalysis", "Legend", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        legendVisibleButton->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        legendVisibleButton->setText(QString());
#if QT_CONFIG(tooltip)
        plotClearButton->setToolTip(QCoreApplication::translate("PageSerialAnalysis", "Clear Plot", nullptr));
#endif // QT_CONFIG(tooltip)
        plotClearButton->setText(QString());
        cmdBrowserClearButton->setText(QString());
#if QT_CONFIG(tooltip)
        xAxisStepDoubleSpinBox->setToolTip(QCoreApplication::translate("PageSerialAnalysis", "X\350\275\264\347\273\230\347\202\271\351\227\264\351\232\224\357\274\2140\350\241\250\347\244\272\344\270\272\345\256\236\346\227\266\346\227\266\351\227\264\357\274\214\345\234\250\346\233\262\347\272\277\350\277\236\347\273\255\346\200\247\345\267\256\346\227\266\350\207\252\345\256\232\344\271\211\350\257\245\351\227\264\351\232\224\345\217\257\344\274\230\345\214\226\346\233\262\347\272\277", nullptr));
#endif // QT_CONFIG(tooltip)
        xAxisStepDoubleSpinBox->setPrefix(QCoreApplication::translate("PageSerialAnalysis", "T:", nullptr));
        xAxisStepDoubleSpinBox->setSuffix(QCoreApplication::translate("PageSerialAnalysis", "s", nullptr));
#if QT_CONFIG(tooltip)
        maxPointsSpinBox->setToolTip(QCoreApplication::translate("PageSerialAnalysis", "Displayed point num in plot", nullptr));
#endif // QT_CONFIG(tooltip)
        maxPointsSpinBox->setSuffix(QString());
        maxPointsSpinBox->setPrefix(QCoreApplication::translate("PageSerialAnalysis", "P:", nullptr));
#if QT_CONFIG(tooltip)
        pushButton->setToolTip(QCoreApplication::translate("PageSerialAnalysis", "Apply displayed point num and xAxis step", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton->setText(QCoreApplication::translate("PageSerialAnalysis", "Apply", nullptr));
        label_11->setText(QCoreApplication::translate("PageSerialAnalysis", "CSV", nullptr));
        csvChooseDirButton->setText(QString());
        csvEnableLogBox->setText(QCoreApplication::translate("PageSerialAnalysis", "SaveData", nullptr));
#if QT_CONFIG(tooltip)
        newDataFile->setToolTip(QCoreApplication::translate("PageSerialAnalysis", "Add new data file", nullptr));
#endif // QT_CONFIG(tooltip)
        newDataFile->setText(QString());
        loadDataButton->setText(QCoreApplication::translate("PageSerialAnalysis", "LoadData", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("PageSerialAnalysis", "Plot Assistant", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("PageSerialAnalysis", "Unknow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageSerialAnalysis: public Ui_PageSerialAnalysis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGESERIALANALYSIS_H
