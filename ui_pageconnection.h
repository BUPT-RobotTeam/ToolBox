/********************************************************************************
** Form generated from reading UI file 'pageconnection.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGECONNECTION_H
#define UI_PAGECONNECTION_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageConnection
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *serialPortBox;
    QSpinBox *serialBaudBox;
    QPushButton *serialRefreshButton;
    QPushButton *serialDisconnectButton;
    QPushButton *serialConnectButton;
    QSpacerItem *verticalSpacer;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QComboBox *CANbusInterfaceBox;
    QLabel *label_5;
    QComboBox *CANbusTargetIdBox;
    QSpinBox *CANbusBitrateBox;
    QPushButton *CANbusScanButton;
    QPushButton *CANbusDisconnectButton;
    QPushButton *CANbusConnectButton;
    QSpacerItem *verticalSpacer_4;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *tcpServerEdit;
    QSpinBox *tcpPortBox;
    QPushButton *tcpDisconnectButton;
    QPushButton *tcpConnectButton;
    QSpacerItem *verticalSpacer_2;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QComboBox *bleDevBox;
    QPushButton *bleScanButton;
    QPushButton *bleDisconnectButton;
    QPushButton *bleConnectButton;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *bleNameEdit;
    QPushButton *bleSetNameButton;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_6;
    QListWidget *pairedListWidget;
    QVBoxLayout *verticalLayout_5;
    QPushButton *pairConnectedButton;
    QPushButton *addConnectedButton;
    QPushButton *addUuidButton;
    QPushButton *unpairButton;
    QPushButton *deletePairedButton;
    QPushButton *clearPairedButton;
    QSpacerItem *verticalSpacer_3;
    QPushButton *autoConnectButton;
    QLabel *statusLabel;

    void setupUi(QWidget *PageConnection)
    {
        if (PageConnection->objectName().isEmpty())
            PageConnection->setObjectName(QString::fromUtf8("PageConnection"));
        PageConnection->resize(1071, 618);
        verticalLayout = new QVBoxLayout(PageConnection);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(PageConnection);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Triangular);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        serialPortBox = new QComboBox(tab);
        serialPortBox->setObjectName(QString::fromUtf8("serialPortBox"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(serialPortBox->sizePolicy().hasHeightForWidth());
        serialPortBox->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(serialPortBox);

        serialBaudBox = new QSpinBox(tab);
        serialBaudBox->setObjectName(QString::fromUtf8("serialBaudBox"));
        serialBaudBox->setMaximum(3000000);
        serialBaudBox->setValue(115200);

        horizontalLayout->addWidget(serialBaudBox);

        serialRefreshButton = new QPushButton(tab);
        serialRefreshButton->setObjectName(QString::fromUtf8("serialRefreshButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(serialRefreshButton->sizePolicy().hasHeightForWidth());
        serialRefreshButton->setSizePolicy(sizePolicy1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/icons/Refresh-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        serialRefreshButton->setIcon(icon);

        horizontalLayout->addWidget(serialRefreshButton);

        serialDisconnectButton = new QPushButton(tab);
        serialDisconnectButton->setObjectName(QString::fromUtf8("serialDisconnectButton"));
        sizePolicy1.setHeightForWidth(serialDisconnectButton->sizePolicy().hasHeightForWidth());
        serialDisconnectButton->setSizePolicy(sizePolicy1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/icons/Disconnected-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        serialDisconnectButton->setIcon(icon1);

        horizontalLayout->addWidget(serialDisconnectButton);

        serialConnectButton = new QPushButton(tab);
        serialConnectButton->setObjectName(QString::fromUtf8("serialConnectButton"));
        sizePolicy1.setHeightForWidth(serialConnectButton->sizePolicy().hasHeightForWidth());
        serialConnectButton->setSizePolicy(sizePolicy1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/res/icons/Connected-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        serialConnectButton->setIcon(icon2);

        horizontalLayout->addWidget(serialConnectButton);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        tabWidget->addTab(tab, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_7 = new QVBoxLayout(tab_4);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_6 = new QLabel(tab_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_7->addWidget(label_6);

        CANbusInterfaceBox = new QComboBox(tab_4);
        CANbusInterfaceBox->setObjectName(QString::fromUtf8("CANbusInterfaceBox"));
        CANbusInterfaceBox->setEditable(false);

        horizontalLayout_7->addWidget(CANbusInterfaceBox);

        label_5 = new QLabel(tab_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_7->addWidget(label_5);

        CANbusTargetIdBox = new QComboBox(tab_4);
        CANbusTargetIdBox->setObjectName(QString::fromUtf8("CANbusTargetIdBox"));
        sizePolicy.setHeightForWidth(CANbusTargetIdBox->sizePolicy().hasHeightForWidth());
        CANbusTargetIdBox->setSizePolicy(sizePolicy);

        horizontalLayout_7->addWidget(CANbusTargetIdBox);

        CANbusBitrateBox = new QSpinBox(tab_4);
        CANbusBitrateBox->setObjectName(QString::fromUtf8("CANbusBitrateBox"));
        CANbusBitrateBox->setEnabled(false);
        CANbusBitrateBox->setFocusPolicy(Qt::WheelFocus);
        CANbusBitrateBox->setMaximum(1000);
        CANbusBitrateBox->setValue(500);

        horizontalLayout_7->addWidget(CANbusBitrateBox);

        CANbusScanButton = new QPushButton(tab_4);
        CANbusScanButton->setObjectName(QString::fromUtf8("CANbusScanButton"));
        sizePolicy1.setHeightForWidth(CANbusScanButton->sizePolicy().hasHeightForWidth());
        CANbusScanButton->setSizePolicy(sizePolicy1);
        CANbusScanButton->setIcon(icon);

        horizontalLayout_7->addWidget(CANbusScanButton);

        CANbusDisconnectButton = new QPushButton(tab_4);
        CANbusDisconnectButton->setObjectName(QString::fromUtf8("CANbusDisconnectButton"));
        sizePolicy1.setHeightForWidth(CANbusDisconnectButton->sizePolicy().hasHeightForWidth());
        CANbusDisconnectButton->setSizePolicy(sizePolicy1);
        CANbusDisconnectButton->setIcon(icon1);

        horizontalLayout_7->addWidget(CANbusDisconnectButton);

        CANbusConnectButton = new QPushButton(tab_4);
        CANbusConnectButton->setObjectName(QString::fromUtf8("CANbusConnectButton"));
        CANbusConnectButton->setEnabled(true);
        sizePolicy1.setHeightForWidth(CANbusConnectButton->sizePolicy().hasHeightForWidth());
        CANbusConnectButton->setSizePolicy(sizePolicy1);
        CANbusConnectButton->setIcon(icon2);

        horizontalLayout_7->addWidget(CANbusConnectButton);


        verticalLayout_7->addLayout(horizontalLayout_7);

        verticalSpacer_4 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_4);

        tabWidget->addTab(tab_4, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(tab_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        tcpServerEdit = new QLineEdit(tab_2);
        tcpServerEdit->setObjectName(QString::fromUtf8("tcpServerEdit"));

        horizontalLayout_3->addWidget(tcpServerEdit);

        tcpPortBox = new QSpinBox(tab_2);
        tcpPortBox->setObjectName(QString::fromUtf8("tcpPortBox"));
        tcpPortBox->setMaximum(65535);
        tcpPortBox->setValue(65102);

        horizontalLayout_3->addWidget(tcpPortBox);

        tcpDisconnectButton = new QPushButton(tab_2);
        tcpDisconnectButton->setObjectName(QString::fromUtf8("tcpDisconnectButton"));
        sizePolicy1.setHeightForWidth(tcpDisconnectButton->sizePolicy().hasHeightForWidth());
        tcpDisconnectButton->setSizePolicy(sizePolicy1);
        tcpDisconnectButton->setIcon(icon1);

        horizontalLayout_3->addWidget(tcpDisconnectButton);

        tcpConnectButton = new QPushButton(tab_2);
        tcpConnectButton->setObjectName(QString::fromUtf8("tcpConnectButton"));
        sizePolicy1.setHeightForWidth(tcpConnectButton->sizePolicy().hasHeightForWidth());
        tcpConnectButton->setSizePolicy(sizePolicy1);
        tcpConnectButton->setIcon(icon2);

        horizontalLayout_3->addWidget(tcpConnectButton);


        verticalLayout_3->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_4 = new QVBoxLayout(tab_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        bleDevBox = new QComboBox(tab_3);
        bleDevBox->setObjectName(QString::fromUtf8("bleDevBox"));
        sizePolicy.setHeightForWidth(bleDevBox->sizePolicy().hasHeightForWidth());
        bleDevBox->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(bleDevBox);

        bleScanButton = new QPushButton(tab_3);
        bleScanButton->setObjectName(QString::fromUtf8("bleScanButton"));
        sizePolicy1.setHeightForWidth(bleScanButton->sizePolicy().hasHeightForWidth());
        bleScanButton->setSizePolicy(sizePolicy1);
        bleScanButton->setIcon(icon);

        horizontalLayout_4->addWidget(bleScanButton);

        bleDisconnectButton = new QPushButton(tab_3);
        bleDisconnectButton->setObjectName(QString::fromUtf8("bleDisconnectButton"));
        sizePolicy1.setHeightForWidth(bleDisconnectButton->sizePolicy().hasHeightForWidth());
        bleDisconnectButton->setSizePolicy(sizePolicy1);
        bleDisconnectButton->setIcon(icon1);

        horizontalLayout_4->addWidget(bleDisconnectButton);

        bleConnectButton = new QPushButton(tab_3);
        bleConnectButton->setObjectName(QString::fromUtf8("bleConnectButton"));
        sizePolicy1.setHeightForWidth(bleConnectButton->sizePolicy().hasHeightForWidth());
        bleConnectButton->setSizePolicy(sizePolicy1);
        bleConnectButton->setIcon(icon2);

        horizontalLayout_4->addWidget(bleConnectButton);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(tab_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        bleNameEdit = new QLineEdit(tab_3);
        bleNameEdit->setObjectName(QString::fromUtf8("bleNameEdit"));

        horizontalLayout_5->addWidget(bleNameEdit);

        bleSetNameButton = new QPushButton(tab_3);
        bleSetNameButton->setObjectName(QString::fromUtf8("bleSetNameButton"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/res/icons/Ok-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        bleSetNameButton->setIcon(icon3);

        horizontalLayout_5->addWidget(bleSetNameButton);


        verticalLayout_4->addLayout(horizontalLayout_5);

        groupBox_2 = new QGroupBox(tab_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy2);
        verticalLayout_6 = new QVBoxLayout(groupBox_2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        pairedListWidget = new QListWidget(groupBox_2);
        pairedListWidget->setObjectName(QString::fromUtf8("pairedListWidget"));

        horizontalLayout_6->addWidget(pairedListWidget);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        pairConnectedButton = new QPushButton(groupBox_2);
        pairConnectedButton->setObjectName(QString::fromUtf8("pairConnectedButton"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/res/icons/Circled Play-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        pairConnectedButton->setIcon(icon4);

        verticalLayout_5->addWidget(pairConnectedButton);

        addConnectedButton = new QPushButton(groupBox_2);
        addConnectedButton->setObjectName(QString::fromUtf8("addConnectedButton"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/res/icons/Plus Math-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        addConnectedButton->setIcon(icon5);

        verticalLayout_5->addWidget(addConnectedButton);

        addUuidButton = new QPushButton(groupBox_2);
        addUuidButton->setObjectName(QString::fromUtf8("addUuidButton"));
        addUuidButton->setIcon(icon5);
        addUuidButton->setFlat(false);

        verticalLayout_5->addWidget(addUuidButton);

        unpairButton = new QPushButton(groupBox_2);
        unpairButton->setObjectName(QString::fromUtf8("unpairButton"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/res/icons/Restart-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        unpairButton->setIcon(icon6);

        verticalLayout_5->addWidget(unpairButton);

        deletePairedButton = new QPushButton(groupBox_2);
        deletePairedButton->setObjectName(QString::fromUtf8("deletePairedButton"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/res/icons/Delete-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        deletePairedButton->setIcon(icon7);

        verticalLayout_5->addWidget(deletePairedButton);

        clearPairedButton = new QPushButton(groupBox_2);
        clearPairedButton->setObjectName(QString::fromUtf8("clearPairedButton"));
        clearPairedButton->setIcon(icon7);

        verticalLayout_5->addWidget(clearPairedButton);

        verticalSpacer_3 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);


        horizontalLayout_6->addLayout(verticalLayout_5);


        verticalLayout_6->addLayout(horizontalLayout_6);


        verticalLayout_4->addWidget(groupBox_2);

        tabWidget->addTab(tab_3, QString());

        verticalLayout->addWidget(tabWidget);

        autoConnectButton = new QPushButton(PageConnection);
        autoConnectButton->setObjectName(QString::fromUtf8("autoConnectButton"));
        autoConnectButton->setEnabled(false);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/res/icons/Wizard-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        autoConnectButton->setIcon(icon8);
        autoConnectButton->setIconSize(QSize(45, 45));

        verticalLayout->addWidget(autoConnectButton);

        statusLabel = new QLabel(PageConnection);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(statusLabel);


        retranslateUi(PageConnection);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PageConnection);
    } // setupUi

    void retranslateUi(QWidget *PageConnection)
    {
        PageConnection->setWindowTitle(QCoreApplication::translate("PageConnection", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("PageConnection", "Port", nullptr));
#if QT_CONFIG(tooltip)
        serialPortBox->setToolTip(QCoreApplication::translate("PageConnection", "Serial port", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        serialBaudBox->setToolTip(QCoreApplication::translate("PageConnection", "Baudrate", nullptr));
#endif // QT_CONFIG(tooltip)
        serialBaudBox->setSuffix(QCoreApplication::translate("PageConnection", " bps", nullptr));
        serialBaudBox->setPrefix(QCoreApplication::translate("PageConnection", "Baud: ", nullptr));
#if QT_CONFIG(tooltip)
        serialRefreshButton->setToolTip(QCoreApplication::translate("PageConnection", "Refresh serial port list", nullptr));
#endif // QT_CONFIG(tooltip)
        serialRefreshButton->setText(QString());
#if QT_CONFIG(tooltip)
        serialDisconnectButton->setToolTip(QCoreApplication::translate("PageConnection", "Disconnect", nullptr));
#endif // QT_CONFIG(tooltip)
        serialDisconnectButton->setText(QString());
#if QT_CONFIG(tooltip)
        serialConnectButton->setToolTip(QCoreApplication::translate("PageConnection", "Connect", nullptr));
#endif // QT_CONFIG(tooltip)
        serialConnectButton->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("PageConnection", "(USB-)Serial", nullptr));
        label_6->setText(QCoreApplication::translate("PageConnection", "Interface", nullptr));
#if QT_CONFIG(tooltip)
        CANbusInterfaceBox->setToolTip(QCoreApplication::translate("PageConnection", "CAN bus interfaces detected", nullptr));
#endif // QT_CONFIG(tooltip)
        CANbusInterfaceBox->setCurrentText(QString());
        label_5->setText(QCoreApplication::translate("PageConnection", "VESC ID", nullptr));
#if QT_CONFIG(tooltip)
        CANbusTargetIdBox->setToolTip(QCoreApplication::translate("PageConnection", "Discovered VESC nodes in the bus", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        CANbusBitrateBox->setToolTip(QCoreApplication::translate("PageConnection", "This configuration is not supported by the socketcan backend. However it is possible to set the rate when configuring the CAN network interface using the ip link command.", nullptr));
#endif // QT_CONFIG(tooltip)
        CANbusBitrateBox->setSuffix(QCoreApplication::translate("PageConnection", " kbit/s", nullptr));
        CANbusBitrateBox->setPrefix(QCoreApplication::translate("PageConnection", "Bit rate: ", nullptr));
#if QT_CONFIG(tooltip)
        CANbusScanButton->setToolTip(QCoreApplication::translate("PageConnection", "Discover VESC nodes in the CAN bus", nullptr));
#endif // QT_CONFIG(tooltip)
        CANbusScanButton->setText(QCoreApplication::translate("PageConnection", "Scan", nullptr));
#if QT_CONFIG(tooltip)
        CANbusDisconnectButton->setToolTip(QCoreApplication::translate("PageConnection", "Disconnect", nullptr));
#endif // QT_CONFIG(tooltip)
        CANbusDisconnectButton->setText(QString());
#if QT_CONFIG(tooltip)
        CANbusConnectButton->setToolTip(QCoreApplication::translate("PageConnection", "Connect to a VESC node", nullptr));
#endif // QT_CONFIG(tooltip)
        CANbusConnectButton->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("PageConnection", "CAN bus", nullptr));
        label->setText(QCoreApplication::translate("PageConnection", "TCP Server", nullptr));
        tcpServerEdit->setText(QCoreApplication::translate("PageConnection", "127.0.0.1", nullptr));
        tcpPortBox->setPrefix(QCoreApplication::translate("PageConnection", "Port: ", nullptr));
#if QT_CONFIG(tooltip)
        tcpDisconnectButton->setToolTip(QCoreApplication::translate("PageConnection", "Disconnect", nullptr));
#endif // QT_CONFIG(tooltip)
        tcpDisconnectButton->setText(QString());
#if QT_CONFIG(tooltip)
        tcpConnectButton->setToolTip(QCoreApplication::translate("PageConnection", "Connect", nullptr));
#endif // QT_CONFIG(tooltip)
        tcpConnectButton->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("PageConnection", "TCP", nullptr));
        label_3->setText(QCoreApplication::translate("PageConnection", "BLE Device", nullptr));
#if QT_CONFIG(tooltip)
        bleScanButton->setToolTip(QCoreApplication::translate("PageConnection", "Refresh serial port list", nullptr));
#endif // QT_CONFIG(tooltip)
        bleScanButton->setText(QString());
#if QT_CONFIG(tooltip)
        bleDisconnectButton->setToolTip(QCoreApplication::translate("PageConnection", "Disconnect", nullptr));
#endif // QT_CONFIG(tooltip)
        bleDisconnectButton->setText(QString());
#if QT_CONFIG(tooltip)
        bleConnectButton->setToolTip(QCoreApplication::translate("PageConnection", "Connect", nullptr));
#endif // QT_CONFIG(tooltip)
        bleConnectButton->setText(QString());
        label_4->setText(QCoreApplication::translate("PageConnection", "Set Device Name", nullptr));
        bleSetNameButton->setText(QCoreApplication::translate("PageConnection", "Set", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PageConnection", "Paired VESCs", nullptr));
#if QT_CONFIG(tooltip)
        pairConnectedButton->setToolTip(QCoreApplication::translate("PageConnection", "Pair the connected VESC", nullptr));
#endif // QT_CONFIG(tooltip)
        pairConnectedButton->setText(QCoreApplication::translate("PageConnection", "Pair", nullptr));
#if QT_CONFIG(tooltip)
        addConnectedButton->setToolTip(QCoreApplication::translate("PageConnection", "Add the connected VESC without pairing it.", nullptr));
#endif // QT_CONFIG(tooltip)
        addConnectedButton->setText(QCoreApplication::translate("PageConnection", "Add", nullptr));
#if QT_CONFIG(tooltip)
        addUuidButton->setToolTip(QCoreApplication::translate("PageConnection", "Manuallt add UUID to this instance of VESC Tool", nullptr));
#endif // QT_CONFIG(tooltip)
        addUuidButton->setText(QCoreApplication::translate("PageConnection", "Add UUID", nullptr));
#if QT_CONFIG(tooltip)
        unpairButton->setToolTip(QCoreApplication::translate("PageConnection", "Unpair this VESC, and make it possible to connect to it from any VESC Tool instance.", nullptr));
#endif // QT_CONFIG(tooltip)
        unpairButton->setText(QCoreApplication::translate("PageConnection", "Unpair", nullptr));
#if QT_CONFIG(tooltip)
        deletePairedButton->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        deletePairedButton->setText(QCoreApplication::translate("PageConnection", "Delete", nullptr));
        clearPairedButton->setText(QCoreApplication::translate("PageConnection", "Clear", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("PageConnection", "Bluetooth LE", nullptr));
#if QT_CONFIG(tooltip)
        autoConnectButton->setToolTip(QCoreApplication::translate("PageConnection", "Try to automatically connect using the USB connection", nullptr));
#endif // QT_CONFIG(tooltip)
        autoConnectButton->setText(QCoreApplication::translate("PageConnection", "Autoconnect", nullptr));
        statusLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PageConnection: public Ui_PageConnection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGECONNECTION_H
