/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionDisconnect;
    QAction *actionReconnect;
    QAction *actionRxPControl;
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionKeyboardControl;
    QAction *actionTxPControl;
    QAction *actionSendAlive;
    QAction *actionAboutQt;
    QAction *actionVESCToolChangelog;
    QAction *actionIMU;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *pageLabel;
    QListWidget *pageList;
    QStackedWidget *pageWidget;
    QGridLayout *gridLayout_3;
    QPushButton *cmdSendButton_3;
    QLineEdit *cmdSendEdit_11;
    QLineEdit *cmdSendEdit_1;
    QLabel *label;
    QLineEdit *cmdSendEdit_0;
    QPushButton *cmdSendButton_0;
    QPushButton *cmdSendButton_7;
    QPushButton *cmdSendButton_2;
    QPushButton *cmdSendButton_8;
    QPushButton *cmdSendButton_9;
    QLineEdit *cmdSendEdit_3;
    QLabel *label_5;
    QLabel *label_2;
    QLineEdit *cmdSendEdit_8;
    QPushButton *cmdSendButton_6;
    QLineEdit *cmdSendEdit_12;
    QPushButton *cmdSendButton_12;
    QLabel *label_7;
    QLabel *label_4;
    QLineEdit *cmdSendEdit_7;
    QLineEdit *cmdSendEdit_5;
    QPushButton *cmdSendButton_1;
    QPushButton *cmdSendButton_5;
    QLineEdit *cmdSendEdit_6;
    QLabel *label_3;
    QPushButton *cmdSendButton_4;
    QLabel *label_8;
    QPushButton *cmdSendButton_11;
    QLineEdit *cmdSendEdit_4;
    QLabel *label_6;
    QLineEdit *cmdSendEdit_9;
    QLineEdit *cmdSendEdit_2;
    QLabel *label_9;
    QLabel *label_10;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1054, 642);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/images/v1logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QString::fromUtf8("actionDisconnect"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/icons/Disconnected-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisconnect->setIcon(icon1);
        actionReconnect = new QAction(MainWindow);
        actionReconnect->setObjectName(QString::fromUtf8("actionReconnect"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/res/icons/Connected-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReconnect->setIcon(icon2);
        actionRxPControl = new QAction(MainWindow);
        actionRxPControl->setObjectName(QString::fromUtf8("actionRxPControl"));
        actionRxPControl->setCheckable(true);
        actionRxPControl->setEnabled(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/res/icons/rxp_off.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QString::fromUtf8(":/res/icons/rxp_on.png"), QSize(), QIcon::Normal, QIcon::On);
        actionRxPControl->setIcon(icon3);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/res/icons/Shutdown-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon4);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/res/icons/About-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon5);
        actionKeyboardControl = new QAction(MainWindow);
        actionKeyboardControl->setObjectName(QString::fromUtf8("actionKeyboardControl"));
        actionKeyboardControl->setCheckable(true);
        actionKeyboardControl->setEnabled(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/res/icons/keys_off.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon6.addFile(QString::fromUtf8(":/res/icons/keys_on.png"), QSize(), QIcon::Normal, QIcon::On);
        actionKeyboardControl->setIcon(icon6);
        actionTxPControl = new QAction(MainWindow);
        actionTxPControl->setObjectName(QString::fromUtf8("actionTxPControl"));
        actionTxPControl->setCheckable(true);
        actionTxPControl->setEnabled(true);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/res/icons/txp_off.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon7.addFile(QString::fromUtf8(":/res/icons/txp_on.png"), QSize(), QIcon::Normal, QIcon::On);
        actionTxPControl->setIcon(icon7);
        actionSendAlive = new QAction(MainWindow);
        actionSendAlive->setObjectName(QString::fromUtf8("actionSendAlive"));
        actionSendAlive->setCheckable(true);
        actionSendAlive->setEnabled(false);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/res/icons/alive_off.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon8.addFile(QString::fromUtf8(":/res/icons/alive_on.png"), QSize(), QIcon::Normal, QIcon::On);
        actionSendAlive->setIcon(icon8);
        actionAboutQt = new QAction(MainWindow);
        actionAboutQt->setObjectName(QString::fromUtf8("actionAboutQt"));
        actionAboutQt->setIcon(icon5);
        actionVESCToolChangelog = new QAction(MainWindow);
        actionVESCToolChangelog->setObjectName(QString::fromUtf8("actionVESCToolChangelog"));
        actionVESCToolChangelog->setIcon(icon5);
        actionIMU = new QAction(MainWindow);
        actionIMU->setObjectName(QString::fromUtf8("actionIMU"));
        actionIMU->setCheckable(true);
        actionIMU->setEnabled(false);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/res/icons/imu_off.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon9.addFile(QString::fromUtf8(":/res/icons/imu_on.png"), QSize(), QIcon::Normal, QIcon::On);
        actionIMU->setIcon(icon9);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, -1, -1, 2);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pageLabel = new QLabel(centralWidget);
        pageLabel->setObjectName(QString::fromUtf8("pageLabel"));
        pageLabel->setEnabled(true);
        pageLabel->setMaximumSize(QSize(220, 56));
        pageLabel->setPixmap(QPixmap(QString::fromUtf8(":/res/images/tool_box.png")));
        pageLabel->setScaledContents(true);

        verticalLayout_2->addWidget(pageLabel);

        pageList = new QListWidget(centralWidget);
        pageList->setObjectName(QString::fromUtf8("pageList"));
        pageList->setMinimumSize(QSize(220, 0));
        pageList->setMaximumSize(QSize(220, 16777215));
        pageList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        pageList->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout_2->addWidget(pageList);


        horizontalLayout->addLayout(verticalLayout_2);

        pageWidget = new QStackedWidget(centralWidget);
        pageWidget->setObjectName(QString::fromUtf8("pageWidget"));

        horizontalLayout->addWidget(pageWidget);

        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        cmdSendButton_3 = new QPushButton(centralWidget);
        cmdSendButton_3->setObjectName(QString::fromUtf8("cmdSendButton_3"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/res/icons/Circled Play-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdSendButton_3->setIcon(icon10);
        cmdSendButton_3->setFlat(false);

        gridLayout_3->addWidget(cmdSendButton_3, 0, 10, 1, 1);

        cmdSendEdit_11 = new QLineEdit(centralWidget);
        cmdSendEdit_11->setObjectName(QString::fromUtf8("cmdSendEdit_11"));

        gridLayout_3->addWidget(cmdSendEdit_11, 0, 0, 1, 1);

        cmdSendEdit_1 = new QLineEdit(centralWidget);
        cmdSendEdit_1->setObjectName(QString::fromUtf8("cmdSendEdit_1"));

        gridLayout_3->addWidget(cmdSendEdit_1, 0, 3, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 0, 2, 1, 1);

        cmdSendEdit_0 = new QLineEdit(centralWidget);
        cmdSendEdit_0->setObjectName(QString::fromUtf8("cmdSendEdit_0"));

        gridLayout_3->addWidget(cmdSendEdit_0, 1, 15, 1, 1);

        cmdSendButton_0 = new QPushButton(centralWidget);
        cmdSendButton_0->setObjectName(QString::fromUtf8("cmdSendButton_0"));
        cmdSendButton_0->setIcon(icon10);

        gridLayout_3->addWidget(cmdSendButton_0, 1, 16, 1, 1);

        cmdSendButton_7 = new QPushButton(centralWidget);
        cmdSendButton_7->setObjectName(QString::fromUtf8("cmdSendButton_7"));
        cmdSendButton_7->setIcon(icon10);

        gridLayout_3->addWidget(cmdSendButton_7, 1, 7, 1, 1);

        cmdSendButton_2 = new QPushButton(centralWidget);
        cmdSendButton_2->setObjectName(QString::fromUtf8("cmdSendButton_2"));
        cmdSendButton_2->setIcon(icon10);

        gridLayout_3->addWidget(cmdSendButton_2, 0, 7, 1, 1);

        cmdSendButton_8 = new QPushButton(centralWidget);
        cmdSendButton_8->setObjectName(QString::fromUtf8("cmdSendButton_8"));
        cmdSendButton_8->setIcon(icon10);

        gridLayout_3->addWidget(cmdSendButton_8, 1, 10, 1, 1);

        cmdSendButton_9 = new QPushButton(centralWidget);
        cmdSendButton_9->setObjectName(QString::fromUtf8("cmdSendButton_9"));
        cmdSendButton_9->setIcon(icon10);

        gridLayout_3->addWidget(cmdSendButton_9, 1, 13, 1, 1);

        cmdSendEdit_3 = new QLineEdit(centralWidget);
        cmdSendEdit_3->setObjectName(QString::fromUtf8("cmdSendEdit_3"));

        gridLayout_3->addWidget(cmdSendEdit_3, 0, 9, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 0, 8, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 1, 2, 1, 1);

        cmdSendEdit_8 = new QLineEdit(centralWidget);
        cmdSendEdit_8->setObjectName(QString::fromUtf8("cmdSendEdit_8"));

        gridLayout_3->addWidget(cmdSendEdit_8, 1, 9, 1, 1);

        cmdSendButton_6 = new QPushButton(centralWidget);
        cmdSendButton_6->setObjectName(QString::fromUtf8("cmdSendButton_6"));
        cmdSendButton_6->setIcon(icon10);

        gridLayout_3->addWidget(cmdSendButton_6, 1, 4, 1, 1);

        cmdSendEdit_12 = new QLineEdit(centralWidget);
        cmdSendEdit_12->setObjectName(QString::fromUtf8("cmdSendEdit_12"));

        gridLayout_3->addWidget(cmdSendEdit_12, 1, 0, 1, 1);

        cmdSendButton_12 = new QPushButton(centralWidget);
        cmdSendButton_12->setObjectName(QString::fromUtf8("cmdSendButton_12"));
        cmdSendButton_12->setIcon(icon10);

        gridLayout_3->addWidget(cmdSendButton_12, 1, 1, 1, 1);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_3->addWidget(label_7, 0, 11, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 1, 5, 1, 1);

        cmdSendEdit_7 = new QLineEdit(centralWidget);
        cmdSendEdit_7->setObjectName(QString::fromUtf8("cmdSendEdit_7"));

        gridLayout_3->addWidget(cmdSendEdit_7, 1, 6, 1, 1);

        cmdSendEdit_5 = new QLineEdit(centralWidget);
        cmdSendEdit_5->setObjectName(QString::fromUtf8("cmdSendEdit_5"));

        gridLayout_3->addWidget(cmdSendEdit_5, 0, 15, 1, 1);

        cmdSendButton_1 = new QPushButton(centralWidget);
        cmdSendButton_1->setObjectName(QString::fromUtf8("cmdSendButton_1"));
        cmdSendButton_1->setIcon(icon10);

        gridLayout_3->addWidget(cmdSendButton_1, 0, 4, 1, 1);

        cmdSendButton_5 = new QPushButton(centralWidget);
        cmdSendButton_5->setObjectName(QString::fromUtf8("cmdSendButton_5"));
        cmdSendButton_5->setIcon(icon10);

        gridLayout_3->addWidget(cmdSendButton_5, 0, 16, 1, 1);

        cmdSendEdit_6 = new QLineEdit(centralWidget);
        cmdSendEdit_6->setObjectName(QString::fromUtf8("cmdSendEdit_6"));

        gridLayout_3->addWidget(cmdSendEdit_6, 1, 3, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 0, 5, 1, 1);

        cmdSendButton_4 = new QPushButton(centralWidget);
        cmdSendButton_4->setObjectName(QString::fromUtf8("cmdSendButton_4"));
        cmdSendButton_4->setIcon(icon10);

        gridLayout_3->addWidget(cmdSendButton_4, 0, 13, 1, 1);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_3->addWidget(label_8, 1, 11, 1, 1);

        cmdSendButton_11 = new QPushButton(centralWidget);
        cmdSendButton_11->setObjectName(QString::fromUtf8("cmdSendButton_11"));
        cmdSendButton_11->setIcon(icon10);

        gridLayout_3->addWidget(cmdSendButton_11, 0, 1, 1, 1);

        cmdSendEdit_4 = new QLineEdit(centralWidget);
        cmdSendEdit_4->setObjectName(QString::fromUtf8("cmdSendEdit_4"));

        gridLayout_3->addWidget(cmdSendEdit_4, 0, 12, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 1, 8, 1, 1);

        cmdSendEdit_9 = new QLineEdit(centralWidget);
        cmdSendEdit_9->setObjectName(QString::fromUtf8("cmdSendEdit_9"));

        gridLayout_3->addWidget(cmdSendEdit_9, 1, 12, 1, 1);

        cmdSendEdit_2 = new QLineEdit(centralWidget);
        cmdSendEdit_2->setObjectName(QString::fromUtf8("cmdSendEdit_2"));

        gridLayout_3->addWidget(cmdSendEdit_2, 0, 6, 1, 1);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_3->addWidget(label_9, 0, 14, 1, 1);

        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_3->addWidget(label_10, 1, 14, 1, 1);


        verticalLayout->addLayout(gridLayout_3);

        verticalLayout->setStretch(0, 1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1054, 30));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setMovable(false);
        mainToolBar->setIconSize(QSize(24, 24));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
        mainToolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::RightToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addSeparator();
        menuFile->addSeparator();
        menuFile->addSeparator();
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuHelp->addSeparator();
        menuHelp->addAction(actionVESCToolChangelog);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionAboutQt);
        menuHelp->addSeparator();
        mainToolBar->addAction(actionReconnect);
        mainToolBar->addAction(actionDisconnect);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionRxPControl);
        mainToolBar->addAction(actionTxPControl);
        mainToolBar->addAction(actionKeyboardControl);
        mainToolBar->addAction(actionIMU);
        mainToolBar->addAction(actionSendAlive);

        retranslateUi(MainWindow);

        pageWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Tool Box", nullptr));
        actionDisconnect->setText(QCoreApplication::translate("MainWindow", "disconnect", nullptr));
#if QT_CONFIG(tooltip)
        actionDisconnect->setToolTip(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
#endif // QT_CONFIG(tooltip)
        actionReconnect->setText(QCoreApplication::translate("MainWindow", "reconnect", nullptr));
#if QT_CONFIG(tooltip)
        actionReconnect->setToolTip(QCoreApplication::translate("MainWindow", "Reconnect last connection", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRxPControl->setText(QCoreApplication::translate("MainWindow", "Rx Protocol Control", nullptr));
#if QT_CONFIG(tooltip)
        actionRxPControl->setToolTip(QCoreApplication::translate("MainWindow", "Enable Rx Protocol Control", nullptr));
#endif // QT_CONFIG(tooltip)
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About Tool Box", nullptr));
        actionKeyboardControl->setText(QCoreApplication::translate("MainWindow", "keyboardControl", nullptr));
#if QT_CONFIG(tooltip)
        actionKeyboardControl->setToolTip(QCoreApplication::translate("MainWindow", "Use arrow keys to control motor", nullptr));
#endif // QT_CONFIG(tooltip)
        actionTxPControl->setText(QCoreApplication::translate("MainWindow", "Tx Protocol Control", nullptr));
#if QT_CONFIG(tooltip)
        actionTxPControl->setToolTip(QCoreApplication::translate("MainWindow", "Enable Tx Protocol Control", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSendAlive->setText(QCoreApplication::translate("MainWindow", "Send Alive Commands", nullptr));
#if QT_CONFIG(tooltip)
        actionSendAlive->setToolTip(QCoreApplication::translate("MainWindow", "Send alive packets periodically to prevent timeout", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAboutQt->setText(QCoreApplication::translate("MainWindow", "About Qt", nullptr));
#if QT_CONFIG(tooltip)
        actionAboutQt->setToolTip(QCoreApplication::translate("MainWindow", "Show the Qt library's About box", nullptr));
#endif // QT_CONFIG(tooltip)
        actionVESCToolChangelog->setText(QCoreApplication::translate("MainWindow", "Tool Box Changelog", nullptr));
        actionIMU->setText(QCoreApplication::translate("MainWindow", "IMU", nullptr));
#if QT_CONFIG(tooltip)
        actionIMU->setToolTip(QCoreApplication::translate("MainWindow", "Activate IMU Sampling", nullptr));
#endif // QT_CONFIG(tooltip)
        pageLabel->setText(QString());
#if QT_CONFIG(tooltip)
        cmdSendButton_3->setToolTip(QCoreApplication::translate("MainWindow", "Send", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        cmdSendButton_3->setWhatsThis(QCoreApplication::translate("MainWindow", "Send", nullptr));
#endif // QT_CONFIG(whatsthis)
        cmdSendButton_3->setText(QString());
#if QT_CONFIG(whatsthis)
        cmdSendEdit_1->setWhatsThis(QCoreApplication::translate("MainWindow", "0", nullptr));
#endif // QT_CONFIG(whatsthis)
        label->setText(QCoreApplication::translate("MainWindow", "1:", nullptr));
#if QT_CONFIG(tooltip)
        cmdSendButton_0->setToolTip(QCoreApplication::translate("MainWindow", "Send", nullptr));
#endif // QT_CONFIG(tooltip)
        cmdSendButton_0->setText(QString());
#if QT_CONFIG(tooltip)
        cmdSendButton_7->setToolTip(QCoreApplication::translate("MainWindow", "Send", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        cmdSendButton_7->setWhatsThis(QCoreApplication::translate("MainWindow", "Send", nullptr));
#endif // QT_CONFIG(whatsthis)
        cmdSendButton_7->setText(QString());
#if QT_CONFIG(tooltip)
        cmdSendButton_2->setToolTip(QCoreApplication::translate("MainWindow", "Send", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        cmdSendButton_2->setWhatsThis(QCoreApplication::translate("MainWindow", "Send", nullptr));
#endif // QT_CONFIG(whatsthis)
        cmdSendButton_2->setText(QString());
#if QT_CONFIG(tooltip)
        cmdSendButton_8->setToolTip(QCoreApplication::translate("MainWindow", "Send", nullptr));
#endif // QT_CONFIG(tooltip)
        cmdSendButton_8->setText(QString());
#if QT_CONFIG(tooltip)
        cmdSendButton_9->setToolTip(QCoreApplication::translate("MainWindow", "Send", nullptr));
#endif // QT_CONFIG(tooltip)
        cmdSendButton_9->setText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "3:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "6:", nullptr));
#if QT_CONFIG(tooltip)
        cmdSendButton_6->setToolTip(QCoreApplication::translate("MainWindow", "Send", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        cmdSendButton_6->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(whatsthis)
        cmdSendButton_6->setWhatsThis(QCoreApplication::translate("MainWindow", "Send", nullptr));
#endif // QT_CONFIG(whatsthis)
        cmdSendButton_6->setText(QString());
#if QT_CONFIG(tooltip)
        cmdSendButton_12->setToolTip(QCoreApplication::translate("MainWindow", "Send", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        cmdSendButton_12->setWhatsThis(QCoreApplication::translate("MainWindow", "Send", nullptr));
#endif // QT_CONFIG(whatsthis)
        cmdSendButton_12->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "4:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "7:", nullptr));
#if QT_CONFIG(tooltip)
        cmdSendButton_1->setToolTip(QCoreApplication::translate("MainWindow", "Send", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        cmdSendButton_1->setWhatsThis(QCoreApplication::translate("MainWindow", "Send", nullptr));
#endif // QT_CONFIG(whatsthis)
        cmdSendButton_1->setText(QString());
#if QT_CONFIG(shortcut)
        cmdSendButton_1->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+2", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        cmdSendButton_5->setToolTip(QCoreApplication::translate("MainWindow", "Send", nullptr));
#endif // QT_CONFIG(tooltip)
        cmdSendButton_5->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "2:", nullptr));
#if QT_CONFIG(tooltip)
        cmdSendButton_4->setToolTip(QCoreApplication::translate("MainWindow", "Send", nullptr));
#endif // QT_CONFIG(tooltip)
        cmdSendButton_4->setText(QString());
        label_8->setText(QCoreApplication::translate("MainWindow", "9:", nullptr));
#if QT_CONFIG(tooltip)
        cmdSendButton_11->setToolTip(QCoreApplication::translate("MainWindow", "Send", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        cmdSendButton_11->setWhatsThis(QCoreApplication::translate("MainWindow", "Send", nullptr));
#endif // QT_CONFIG(whatsthis)
        cmdSendButton_11->setText(QString());
        label_6->setText(QCoreApplication::translate("MainWindow", "8:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "5:", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "0:", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
