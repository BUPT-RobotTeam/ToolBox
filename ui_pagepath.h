/********************************************************************************
** Form generated from reading UI file 'pagepath.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEPATH_H
#define UI_PAGEPATH_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PagePath
{
public:
    QVBoxLayout *verticalLayout_9;
    QTabWidget *tabWidget;
    QWidget *tabPath;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label;
    QLabel *nowPoint;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_14;
    QDoubleSpinBox *Edit_map_width;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_15;
    QDoubleSpinBox *Edit_map_heigh;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_12;
    QSpinBox *Edit_x_toggle;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_22;
    QSpinBox *Edit_y_toggle;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_30;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_33;
    QDoubleSpinBox *Edit_translate_dx;
    QLabel *label_31;
    QDoubleSpinBox *Edit_translate_dy;
    QLabel *label_32;
    QDoubleSpinBox *Edit_translate_dangle;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *EditPathConfig;
    QPushButton *ButtonBrowsePathConfig;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *Edit_img_location;
    QPushButton *Button_load_img;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_19;
    QDoubleSpinBox *Edit_now_angle;
    QFrame *line;
    QDoubleSpinBox *Edit_target_angle;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_20;
    QDoubleSpinBox *Edit_max_speed;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_29;
    QDoubleSpinBox *Edit_max_acceleration;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_37;
    QDoubleSpinBox *Edit_max_jerk;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton_PointNumMode;
    QRadioButton *radioButton_TimeIntervalMode;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QDoubleSpinBox *Edit_sampleTime;
    QHBoxLayout *horizontalLayout_30;
    QLabel *label_38;
    QDoubleSpinBox *Sample_interval;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *Edit_file_location;
    QComboBox *File_type;
    QPushButton *Button_open_folder;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_26;
    QPushButton *Button_add_point;
    QPushButton *Button_delete_point;
    QPushButton *Button_clear;
    QHBoxLayout *horizontalLayout_21;
    QPushButton *Button_create_path;
    QPushButton *Button_create_file;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *ButtonNewPathConfig;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *ButtonSavePathConfigAs;
    QPushButton *ButtonSavePathConfig;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_27;
    QTableView *table_input;
    QLabel *label_28;
    QTableView *table_out;
    QButtonGroup *buttonGroup_outputMode;

    void setupUi(QWidget *PagePath)
    {
        if (PagePath->objectName().isEmpty())
            PagePath->setObjectName(QString::fromUtf8("PagePath"));
        PagePath->resize(1222, 771);
        verticalLayout_9 = new QVBoxLayout(PagePath);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        tabWidget = new QTabWidget(PagePath);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setTabShape(QTabWidget::Triangular);
        tabPath = new QWidget();
        tabPath->setObjectName(QString::fromUtf8("tabPath"));
        sizePolicy.setHeightForWidth(tabPath->sizePolicy().hasHeightForWidth());
        tabPath->setSizePolicy(sizePolicy);
        horizontalLayout_8 = new QHBoxLayout(tabPath);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setSizeConstraint(QLayout::SetFixedSize);
        label = new QLabel(tabPath);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(16777215, 60));

        horizontalLayout_11->addWidget(label);

        nowPoint = new QLabel(tabPath);
        nowPoint->setObjectName(QString::fromUtf8("nowPoint"));
        nowPoint->setMaximumSize(QSize(16777215, 60));

        horizontalLayout_11->addWidget(nowPoint);

        horizontalLayout_11->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout_11);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetMinimumSize);
        label_14 = new QLabel(tabPath);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMaximumSize(QSize(16777215, 37));

        verticalLayout_4->addWidget(label_14);

        Edit_map_width = new QDoubleSpinBox(tabPath);
        Edit_map_width->setObjectName(QString::fromUtf8("Edit_map_width"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Edit_map_width->sizePolicy().hasHeightForWidth());
        Edit_map_width->setSizePolicy(sizePolicy1);
        Edit_map_width->setMinimum(2.000000000000000);
        Edit_map_width->setValue(10.000000000000000);

        verticalLayout_4->addWidget(Edit_map_width);


        horizontalLayout_9->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetMinimumSize);
        label_15 = new QLabel(tabPath);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setMaximumSize(QSize(16777215, 37));

        verticalLayout_5->addWidget(label_15);

        Edit_map_heigh = new QDoubleSpinBox(tabPath);
        Edit_map_heigh->setObjectName(QString::fromUtf8("Edit_map_heigh"));
        sizePolicy1.setHeightForWidth(Edit_map_heigh->sizePolicy().hasHeightForWidth());
        Edit_map_heigh->setSizePolicy(sizePolicy1);
        Edit_map_heigh->setMinimum(2.000000000000000);
        Edit_map_heigh->setValue(10.000000000000000);

        verticalLayout_5->addWidget(Edit_map_heigh);


        horizontalLayout_9->addLayout(verticalLayout_5);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setSizeConstraint(QLayout::SetMinimumSize);
        label_12 = new QLabel(tabPath);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMaximumSize(QSize(16777215, 37));

        verticalLayout_7->addWidget(label_12);

        Edit_x_toggle = new QSpinBox(tabPath);
        Edit_x_toggle->setObjectName(QString::fromUtf8("Edit_x_toggle"));
        sizePolicy1.setHeightForWidth(Edit_x_toggle->sizePolicy().hasHeightForWidth());
        Edit_x_toggle->setSizePolicy(sizePolicy1);
        Edit_x_toggle->setMinimum(-1);
        Edit_x_toggle->setMaximum(1);
        Edit_x_toggle->setSingleStep(2);
        Edit_x_toggle->setValue(1);

        verticalLayout_7->addWidget(Edit_x_toggle);


        horizontalLayout_9->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setSizeConstraint(QLayout::SetMinimumSize);
        label_22 = new QLabel(tabPath);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy2);
        label_22->setMaximumSize(QSize(16777215, 37));

        verticalLayout_8->addWidget(label_22);

        Edit_y_toggle = new QSpinBox(tabPath);
        Edit_y_toggle->setObjectName(QString::fromUtf8("Edit_y_toggle"));
        sizePolicy1.setHeightForWidth(Edit_y_toggle->sizePolicy().hasHeightForWidth());
        Edit_y_toggle->setSizePolicy(sizePolicy1);
        Edit_y_toggle->setMinimum(-1);
        Edit_y_toggle->setMaximum(1);
        Edit_y_toggle->setSingleStep(2);
        Edit_y_toggle->setValue(1);

        verticalLayout_8->addWidget(Edit_y_toggle);


        horizontalLayout_9->addLayout(verticalLayout_8);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(7);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setSizeConstraint(QLayout::SetFixedSize);
        label_30 = new QLabel(tabPath);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setEnabled(true);

        verticalLayout_6->addWidget(label_30, 0, Qt::AlignVCenter);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        label_33 = new QLabel(tabPath);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setMaximumSize(QSize(16777215, 37));

        horizontalLayout_2->addWidget(label_33, 0, Qt::AlignVCenter);

        Edit_translate_dx = new QDoubleSpinBox(tabPath);
        Edit_translate_dx->setObjectName(QString::fromUtf8("Edit_translate_dx"));
        sizePolicy1.setHeightForWidth(Edit_translate_dx->sizePolicy().hasHeightForWidth());
        Edit_translate_dx->setSizePolicy(sizePolicy1);
        Edit_translate_dx->setSingleStep(0.100000000000000);

        horizontalLayout_2->addWidget(Edit_translate_dx, 0, Qt::AlignVCenter);

        label_31 = new QLabel(tabPath);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setMaximumSize(QSize(16777215, 37));

        horizontalLayout_2->addWidget(label_31, 0, Qt::AlignVCenter);

        Edit_translate_dy = new QDoubleSpinBox(tabPath);
        Edit_translate_dy->setObjectName(QString::fromUtf8("Edit_translate_dy"));
        sizePolicy1.setHeightForWidth(Edit_translate_dy->sizePolicy().hasHeightForWidth());
        Edit_translate_dy->setSizePolicy(sizePolicy1);
        Edit_translate_dy->setSingleStep(0.100000000000000);

        horizontalLayout_2->addWidget(Edit_translate_dy, 0, Qt::AlignVCenter);

        label_32 = new QLabel(tabPath);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setMaximumSize(QSize(16777215, 37));

        horizontalLayout_2->addWidget(label_32, 0, Qt::AlignVCenter);

        Edit_translate_dangle = new QDoubleSpinBox(tabPath);
        Edit_translate_dangle->setObjectName(QString::fromUtf8("Edit_translate_dangle"));
        sizePolicy1.setHeightForWidth(Edit_translate_dangle->sizePolicy().hasHeightForWidth());
        Edit_translate_dangle->setSizePolicy(sizePolicy1);
        Edit_translate_dangle->setMinimum(-90.000000000000000);
        Edit_translate_dangle->setMaximum(90.000000000000000);
        Edit_translate_dangle->setValue(0.000000000000000);

        horizontalLayout_2->addWidget(Edit_translate_dangle, 0, Qt::AlignVCenter);


        verticalLayout_6->addLayout(horizontalLayout_2);


        horizontalLayout_9->addLayout(verticalLayout_6);


        verticalLayout_3->addLayout(horizontalLayout_9);


        horizontalLayout_8->addLayout(verticalLayout_3);

        groupBox_2 = new QGroupBox(tabPath);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(360, 16777215));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        EditPathConfig = new QLineEdit(groupBox_2);
        EditPathConfig->setObjectName(QString::fromUtf8("EditPathConfig"));
        EditPathConfig->setReadOnly(true);

        horizontalLayout_6->addWidget(EditPathConfig);

        ButtonBrowsePathConfig = new QPushButton(groupBox_2);
        ButtonBrowsePathConfig->setObjectName(QString::fromUtf8("ButtonBrowsePathConfig"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/icons/Open Folder-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonBrowsePathConfig->setIcon(icon);

        horizontalLayout_6->addWidget(ButtonBrowsePathConfig);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        Edit_img_location = new QLineEdit(groupBox_2);
        Edit_img_location->setObjectName(QString::fromUtf8("Edit_img_location"));
        Edit_img_location->setReadOnly(true);

        horizontalLayout_7->addWidget(Edit_img_location);

        Button_load_img = new QPushButton(groupBox_2);
        Button_load_img->setObjectName(QString::fromUtf8("Button_load_img"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/path_image/ground.png"), QSize(), QIcon::Normal, QIcon::Off);
        Button_load_img->setIcon(icon1);

        horizontalLayout_7->addWidget(Button_load_img);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        horizontalLayout_5->addWidget(label_19);

        Edit_now_angle = new QDoubleSpinBox(groupBox_2);
        Edit_now_angle->setObjectName(QString::fromUtf8("Edit_now_angle"));
        Edit_now_angle->setMinimum(-180.000000000000000);
        Edit_now_angle->setMaximum(180.000000000000000);
        Edit_now_angle->setValue(90.000000000000000);

        horizontalLayout_5->addWidget(Edit_now_angle);

        line = new QFrame(groupBox_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_5->addWidget(line);

        Edit_target_angle = new QDoubleSpinBox(groupBox_2);
        Edit_target_angle->setObjectName(QString::fromUtf8("Edit_target_angle"));
        Edit_target_angle->setMinimum(-180.000000000000000);
        Edit_target_angle->setMaximum(180.000000000000000);
        Edit_target_angle->setValue(90.000000000000000);

        horizontalLayout_5->addWidget(Edit_target_angle);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        horizontalLayout_13->addWidget(label_20);

        Edit_max_speed = new QDoubleSpinBox(groupBox_2);
        Edit_max_speed->setObjectName(QString::fromUtf8("Edit_max_speed"));
        Edit_max_speed->setSingleStep(0.100000000000000);
        Edit_max_speed->setValue(1.000000000000000);

        horizontalLayout_13->addWidget(Edit_max_speed);


        verticalLayout->addLayout(horizontalLayout_13);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        label_29 = new QLabel(groupBox_2);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        horizontalLayout_25->addWidget(label_29);

        Edit_max_acceleration = new QDoubleSpinBox(groupBox_2);
        Edit_max_acceleration->setObjectName(QString::fromUtf8("Edit_max_acceleration"));
        Edit_max_acceleration->setSingleStep(0.100000000000000);
        Edit_max_acceleration->setValue(1.000000000000000);

        horizontalLayout_25->addWidget(Edit_max_acceleration);


        verticalLayout->addLayout(horizontalLayout_25);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        label_37 = new QLabel(groupBox_2);
        label_37->setObjectName(QString::fromUtf8("label_37"));

        horizontalLayout_27->addWidget(label_37);

        Edit_max_jerk = new QDoubleSpinBox(groupBox_2);
        Edit_max_jerk->setObjectName(QString::fromUtf8("Edit_max_jerk"));
        Edit_max_jerk->setSingleStep(0.100000000000000);
        Edit_max_jerk->setValue(1.000000000000000);

        horizontalLayout_27->addWidget(Edit_max_jerk);


        verticalLayout->addLayout(horizontalLayout_27);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioButton_PointNumMode = new QRadioButton(groupBox_2);
        buttonGroup_outputMode = new QButtonGroup(PagePath);
        buttonGroup_outputMode->setObjectName(QString::fromUtf8("buttonGroup_outputMode"));
        buttonGroup_outputMode->setExclusive(true);
        buttonGroup_outputMode->addButton(radioButton_PointNumMode);
        radioButton_PointNumMode->setObjectName(QString::fromUtf8("radioButton_PointNumMode"));
        radioButton_PointNumMode->setChecked(true);

        horizontalLayout->addWidget(radioButton_PointNumMode);

        radioButton_TimeIntervalMode = new QRadioButton(groupBox_2);
        buttonGroup_outputMode->addButton(radioButton_TimeIntervalMode);
        radioButton_TimeIntervalMode->setObjectName(QString::fromUtf8("radioButton_TimeIntervalMode"));

        horizontalLayout->addWidget(radioButton_TimeIntervalMode);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        Edit_sampleTime = new QDoubleSpinBox(groupBox_2);
        Edit_sampleTime->setObjectName(QString::fromUtf8("Edit_sampleTime"));
        Edit_sampleTime->setEnabled(true);
        Edit_sampleTime->setReadOnly(true);
        Edit_sampleTime->setMaximum(2.000000000000000);
        Edit_sampleTime->setSingleStep(0.010000000000000);
        Edit_sampleTime->setValue(0.010000000000000);

        horizontalLayout_3->addWidget(Edit_sampleTime);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        label_38 = new QLabel(groupBox_2);
        label_38->setObjectName(QString::fromUtf8("label_38"));

        horizontalLayout_30->addWidget(label_38);

        Sample_interval = new QDoubleSpinBox(groupBox_2);
        Sample_interval->setObjectName(QString::fromUtf8("Sample_interval"));
        Sample_interval->setDecimals(2);
        Sample_interval->setMaximum(1.000000000000000);
        Sample_interval->setSingleStep(0.010000000000000);
        Sample_interval->setValue(0.100000000000000);

        horizontalLayout_30->addWidget(Sample_interval);


        verticalLayout->addLayout(horizontalLayout_30);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        Edit_file_location = new QLineEdit(groupBox_2);
        Edit_file_location->setObjectName(QString::fromUtf8("Edit_file_location"));
        Edit_file_location->setReadOnly(true);

        horizontalLayout_4->addWidget(Edit_file_location);

        File_type = new QComboBox(groupBox_2);
        File_type->addItem(QString());
        File_type->addItem(QString());
        File_type->addItem(QString());
        File_type->setObjectName(QString::fromUtf8("File_type"));

        horizontalLayout_4->addWidget(File_type);

        Button_open_folder = new QPushButton(groupBox_2);
        Button_open_folder->setObjectName(QString::fromUtf8("Button_open_folder"));
        Button_open_folder->setIcon(icon);

        horizontalLayout_4->addWidget(Button_open_folder);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 80, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        Button_add_point = new QPushButton(groupBox_2);
        Button_add_point->setObjectName(QString::fromUtf8("Button_add_point"));

        horizontalLayout_26->addWidget(Button_add_point);

        Button_delete_point = new QPushButton(groupBox_2);
        Button_delete_point->setObjectName(QString::fromUtf8("Button_delete_point"));

        horizontalLayout_26->addWidget(Button_delete_point);

        Button_clear = new QPushButton(groupBox_2);
        Button_clear->setObjectName(QString::fromUtf8("Button_clear"));

        horizontalLayout_26->addWidget(Button_clear);


        verticalLayout->addLayout(horizontalLayout_26);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        Button_create_path = new QPushButton(groupBox_2);
        Button_create_path->setObjectName(QString::fromUtf8("Button_create_path"));

        horizontalLayout_21->addWidget(Button_create_path);

        Button_create_file = new QPushButton(groupBox_2);
        Button_create_file->setObjectName(QString::fromUtf8("Button_create_file"));

        horizontalLayout_21->addWidget(Button_create_file);


        verticalLayout->addLayout(horizontalLayout_21);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        ButtonNewPathConfig = new QPushButton(groupBox_2);
        ButtonNewPathConfig->setObjectName(QString::fromUtf8("ButtonNewPathConfig"));

        horizontalLayout_12->addWidget(ButtonNewPathConfig);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        ButtonSavePathConfigAs = new QPushButton(groupBox_2);
        ButtonSavePathConfigAs->setObjectName(QString::fromUtf8("ButtonSavePathConfigAs"));

        horizontalLayout_10->addWidget(ButtonSavePathConfigAs);

        ButtonSavePathConfig = new QPushButton(groupBox_2);
        ButtonSavePathConfig->setObjectName(QString::fromUtf8("ButtonSavePathConfig"));

        horizontalLayout_10->addWidget(ButtonSavePathConfig);


        verticalLayout->addLayout(horizontalLayout_10);


        horizontalLayout_8->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(tabPath);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_27 = new QLabel(groupBox_3);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        verticalLayout_2->addWidget(label_27);

        table_input = new QTableView(groupBox_3);
        table_input->setObjectName(QString::fromUtf8("table_input"));
        table_input->setContextMenuPolicy(Qt::CustomContextMenu);
        table_input->setAutoFillBackground(true);
        table_input->horizontalHeader()->setDefaultSectionSize(60);

        verticalLayout_2->addWidget(table_input);

        label_28 = new QLabel(groupBox_3);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        verticalLayout_2->addWidget(label_28);

        table_out = new QTableView(groupBox_3);
        table_out->setObjectName(QString::fromUtf8("table_out"));
        table_out->setContextMenuPolicy(Qt::CustomContextMenu);
        table_out->setAutoFillBackground(true);
        table_out->horizontalHeader()->setDefaultSectionSize(60);

        verticalLayout_2->addWidget(table_out);


        horizontalLayout_8->addWidget(groupBox_3);

        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Path_image/ground.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabPath, icon2, QString());

        verticalLayout_9->addWidget(tabWidget);

        QWidget::setTabOrder(Edit_map_width, Edit_map_heigh);
        QWidget::setTabOrder(Edit_map_heigh, Edit_x_toggle);
        QWidget::setTabOrder(Edit_x_toggle, Edit_y_toggle);
        QWidget::setTabOrder(Edit_y_toggle, Edit_translate_dx);
        QWidget::setTabOrder(Edit_translate_dx, Edit_translate_dy);
        QWidget::setTabOrder(Edit_translate_dy, Edit_translate_dangle);
        QWidget::setTabOrder(Edit_translate_dangle, Edit_img_location);
        QWidget::setTabOrder(Edit_img_location, Button_load_img);
        QWidget::setTabOrder(Button_load_img, Edit_file_location);
        QWidget::setTabOrder(Edit_file_location, Button_open_folder);
        QWidget::setTabOrder(Button_open_folder, Edit_now_angle);
        QWidget::setTabOrder(Edit_now_angle, Edit_target_angle);
        QWidget::setTabOrder(Edit_target_angle, Edit_max_speed);
        QWidget::setTabOrder(Edit_max_speed, tabWidget);

        retranslateUi(PagePath);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PagePath);
    } // setupUi

    void retranslateUi(QWidget *PagePath)
    {
        PagePath->setWindowTitle(QCoreApplication::translate("PagePath", "Form", nullptr));
        label->setText(QCoreApplication::translate("PagePath", "\345\275\223\345\211\215\345\235\220\346\240\207\347\202\271(\347\264\242\345\274\225\344\273\2160\345\274\200\345\247\213)", nullptr));
        nowPoint->setText(QString());
        label_14->setText(QCoreApplication::translate("PagePath", "\346\260\264\345\271\263\351\225\277\345\272\246", nullptr));
        label_15->setText(QCoreApplication::translate("PagePath", "\347\253\226\347\233\264\351\225\277\345\272\246", nullptr));
        label_12->setText(QCoreApplication::translate("PagePath", "X\350\275\264\346\226\271\345\220\221", nullptr));
        label_22->setText(QCoreApplication::translate("PagePath", "Y\350\275\264\346\226\271\345\220\221", nullptr));
        label_30->setText(QCoreApplication::translate("PagePath", "\345\271\263\347\247\273\343\200\201\346\227\213\350\275\254\345\235\220\346\240\207\347\263\273(\351\200\206\346\227\266\351\222\210\344\270\272\346\227\213\350\275\254\346\255\243\346\226\271\345\220\221)", nullptr));
        label_33->setText(QCoreApplication::translate("PagePath", "dX", nullptr));
        label_31->setText(QCoreApplication::translate("PagePath", "dY", nullptr));
        label_32->setText(QCoreApplication::translate("PagePath", "d\302\260", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PagePath", "Initialization", nullptr));
        EditPathConfig->setText(QString());
        EditPathConfig->setPlaceholderText(QCoreApplication::translate("PagePath", "\350\267\257\345\276\204\351\205\215\347\275\256\357\274\214\344\276\213:D:/path1.json", nullptr));
#if QT_CONFIG(tooltip)
        ButtonBrowsePathConfig->setToolTip(QCoreApplication::translate("PagePath", "\347\202\271\344\277\235\345\255\230\350\267\257\345\276\204", nullptr));
#endif // QT_CONFIG(tooltip)
        ButtonBrowsePathConfig->setText(QString());
        Edit_img_location->setText(QString());
        Edit_img_location->setPlaceholderText(QCoreApplication::translate("PagePath", "\345\234\260\345\233\276\346\226\207\344\273\266\357\274\214\344\276\213:D:/ground.png", nullptr));
        Button_load_img->setText(QString());
        label_19->setText(QCoreApplication::translate("PagePath", "\350\247\222\345\272\246:", nullptr));
        Edit_now_angle->setSuffix(QCoreApplication::translate("PagePath", "\302\260", nullptr));
        Edit_target_angle->setSuffix(QCoreApplication::translate("PagePath", "\302\260", nullptr));
        label_20->setText(QCoreApplication::translate("PagePath", "\346\234\200\345\244\247\351\200\237\345\272\246(m/s):", nullptr));
        label_29->setText(QCoreApplication::translate("PagePath", "\346\234\200\345\244\247\345\212\240\351\200\237\345\272\246(m/s\302\262)\357\274\232", nullptr));
        label_37->setText(QCoreApplication::translate("PagePath", "\346\234\200\345\244\247\345\212\240\345\212\240\351\200\237\345\272\246(m/s\302\263):", nullptr));
        radioButton_PointNumMode->setText(QCoreApplication::translate("PagePath", "\346\216\247\345\210\266\350\276\223\345\207\272\347\202\271\346\225\260", nullptr));
        radioButton_TimeIntervalMode->setText(QCoreApplication::translate("PagePath", "\346\216\247\345\210\266\350\276\223\345\207\272\346\227\266\351\227\264\351\227\264\351\232\224", nullptr));
        label_2->setText(QCoreApplication::translate("PagePath", "<html><head/><body><p>\346\227\266\351\227\264\351\227\264\351\232\224\357\274\210s\357\274\211\357\274\232</p></body></html>", nullptr));
        Edit_sampleTime->setSuffix(QCoreApplication::translate("PagePath", "s", nullptr));
        label_38->setText(QCoreApplication::translate("PagePath", "d_s(m):", nullptr));
        Edit_file_location->setText(QString());
        Edit_file_location->setPlaceholderText(QCoreApplication::translate("PagePath", "\350\276\223\345\207\272\347\202\271\351\233\206\347\233\256\345\275\225", nullptr));
        File_type->setItemText(0, QCoreApplication::translate("PagePath", "trace.txt", nullptr));
        File_type->setItemText(1, QCoreApplication::translate("PagePath", "trace.c", nullptr));
        File_type->setItemText(2, QCoreApplication::translate("PagePath", "trace.doc", nullptr));

#if QT_CONFIG(tooltip)
        Button_open_folder->setToolTip(QCoreApplication::translate("PagePath", "\347\202\271\344\277\235\345\255\230\350\267\257\345\276\204", nullptr));
#endif // QT_CONFIG(tooltip)
        Button_open_folder->setText(QString());
        Button_add_point->setText(QCoreApplication::translate("PagePath", "\345\212\240\347\202\271", nullptr));
        Button_delete_point->setText(QCoreApplication::translate("PagePath", "\345\210\240\347\202\271", nullptr));
        Button_clear->setText(QCoreApplication::translate("PagePath", "\346\270\205\347\251\272", nullptr));
        Button_create_path->setText(QCoreApplication::translate("PagePath", "\347\224\237\346\210\220\350\267\257\345\276\204", nullptr));
        Button_create_file->setText(QCoreApplication::translate("PagePath", "\347\224\237\346\210\220\346\225\260\347\273\204", nullptr));
        ButtonNewPathConfig->setText(QCoreApplication::translate("PagePath", "\346\226\260\345\273\272\351\205\215\347\275\256", nullptr));
        ButtonSavePathConfigAs->setText(QCoreApplication::translate("PagePath", "\345\217\246\345\255\230\344\270\272\351\205\215\347\275\256", nullptr));
        ButtonSavePathConfig->setText(QCoreApplication::translate("PagePath", "\344\277\235\345\255\230\351\205\215\347\275\256", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("PagePath", "Other Functions", nullptr));
        label_27->setText(QCoreApplication::translate("PagePath", "\350\276\223\345\205\245", nullptr));
        label_28->setText(QCoreApplication::translate("PagePath", "\350\276\223\345\207\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabPath), QCoreApplication::translate("PagePath", "tabPath", nullptr));
#if QT_CONFIG(tooltip)
        tabWidget->setTabToolTip(tabWidget->indexOf(tabPath), QCoreApplication::translate("PagePath", "\350\267\257\345\276\204\350\247\204\345\210\222", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class PagePath: public Ui_PagePath {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEPATH_H
