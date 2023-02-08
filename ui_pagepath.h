/********************************************************************************
** Form generated from reading UI file 'pagepath.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEPATH_H
#define UI_PAGEPATH_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "widgets/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_PagePath
{
public:
    QHBoxLayout *horizontalLayout_8;
    QTabWidget *tabWidget;
    QWidget *tabPath;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_3;
    QCustomPlot *customPlot;
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
    QHBoxLayout *horizontalLayout;
    QLabel *label_21;
    QSpinBox *Edit_bezier_num;
    QPushButton *Button_bezier_num;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *Edit_img_location;
    QPushButton *Button_load_img;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *Edit_file_location;
    QComboBox *File_type;
    QPushButton *Button_open_folder;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_19;
    QDoubleSpinBox *Edit_now_angle;
    QFrame *line;
    QDoubleSpinBox *Edit_target_angle;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_13;
    QSpinBox *Edit_num_btw_two;
    QHBoxLayout *horizontalLayout_29;
    QCheckBox *Sampple_time;
    QCheckBox *Sample_distance;
    QHBoxLayout *horizontalLayout_30;
    QLabel *label_38;
    QDoubleSpinBox *Sample_interval;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_16;
    QSpinBox *spinBox_kspeed;
    QSlider *Slider_kspeed;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_20;
    QDoubleSpinBox *Edit_max_speed;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_29;
    QDoubleSpinBox *Edit_max_acceleration;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_37;
    QDoubleSpinBox *Edit_max_jerk;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_34;
    QLineEdit *Edit_bezier_cnt;
    QLabel *label_35;
    QWidget *point_area_2;
    QVBoxLayout *point_area;
    QScrollArea *scrollArea;
    QWidget *widget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *point_area_3;
    QHBoxLayout *horizontalLayout_26;
    QPushButton *Button_add_point;
    QPushButton *Button_delete_point;
    QHBoxLayout *horizontalLayout_21;
    QPushButton *Button_create_path;
    QPushButton *Button_load_path;
    QHBoxLayout *horizontalLayout_22;
    QPushButton *Button_add_bezier;
    QPushButton *Button_create_file;
    QHBoxLayout *horizontalLayout_23;
    QPushButton *Button_clear;
    QPushButton *Button_cmp;
    QPushButton *Button_update_point;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_17;
    QLineEdit *Edit_bezier_length;
    QLabel *label_18;
    QLineEdit *Edit_point_num;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_23;
    QLineEdit *Edit_posx;
    QLabel *label_24;
    QLineEdit *Edit_posy;
    QLabel *label_27;
    QPlainTextEdit *plainTextEdit_input;
    QLabel *label_28;
    QTableView *table_out;

    void setupUi(QWidget *PagePath)
    {
        if (PagePath->objectName().isEmpty())
            PagePath->setObjectName(QString::fromUtf8("PagePath"));
        PagePath->resize(1216, 915);
        horizontalLayout_8 = new QHBoxLayout(PagePath);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
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
        horizontalLayout_11 = new QHBoxLayout(tabPath);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        customPlot = new QCustomPlot(tabPath);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        sizePolicy.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
        customPlot->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(customPlot);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetMinimumSize);
        label_14 = new QLabel(tabPath);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        verticalLayout_4->addWidget(label_14);

        Edit_map_width = new QDoubleSpinBox(tabPath);
        Edit_map_width->setObjectName(QString::fromUtf8("Edit_map_width"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Edit_map_width->sizePolicy().hasHeightForWidth());
        Edit_map_width->setSizePolicy(sizePolicy1);
        Edit_map_width->setValue(13.300000000000001);

        verticalLayout_4->addWidget(Edit_map_width);


        horizontalLayout_9->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetMinimumSize);
        label_15 = new QLabel(tabPath);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        verticalLayout_5->addWidget(label_15);

        Edit_map_heigh = new QDoubleSpinBox(tabPath);
        Edit_map_heigh->setObjectName(QString::fromUtf8("Edit_map_heigh"));
        sizePolicy1.setHeightForWidth(Edit_map_heigh->sizePolicy().hasHeightForWidth());
        Edit_map_heigh->setSizePolicy(sizePolicy1);
        Edit_map_heigh->setValue(10.000000000000000);

        verticalLayout_5->addWidget(Edit_map_heigh);


        horizontalLayout_9->addLayout(verticalLayout_5);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setSizeConstraint(QLayout::SetMinimumSize);
        label_12 = new QLabel(tabPath);
        label_12->setObjectName(QString::fromUtf8("label_12"));

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
        verticalLayout_6->setSizeConstraint(QLayout::SetMinimumSize);
        label_30 = new QLabel(tabPath);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_30->sizePolicy().hasHeightForWidth());
        label_30->setSizePolicy(sizePolicy3);

        verticalLayout_6->addWidget(label_30);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        label_33 = new QLabel(tabPath);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        horizontalLayout_2->addWidget(label_33);

        Edit_translate_dx = new QDoubleSpinBox(tabPath);
        Edit_translate_dx->setObjectName(QString::fromUtf8("Edit_translate_dx"));
        sizePolicy1.setHeightForWidth(Edit_translate_dx->sizePolicy().hasHeightForWidth());
        Edit_translate_dx->setSizePolicy(sizePolicy1);
        Edit_translate_dx->setSingleStep(0.100000000000000);

        horizontalLayout_2->addWidget(Edit_translate_dx);

        label_31 = new QLabel(tabPath);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        horizontalLayout_2->addWidget(label_31);

        Edit_translate_dy = new QDoubleSpinBox(tabPath);
        Edit_translate_dy->setObjectName(QString::fromUtf8("Edit_translate_dy"));
        sizePolicy1.setHeightForWidth(Edit_translate_dy->sizePolicy().hasHeightForWidth());
        Edit_translate_dy->setSizePolicy(sizePolicy1);
        Edit_translate_dy->setSingleStep(0.100000000000000);

        horizontalLayout_2->addWidget(Edit_translate_dy);

        label_32 = new QLabel(tabPath);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        horizontalLayout_2->addWidget(label_32);

        Edit_translate_dangle = new QDoubleSpinBox(tabPath);
        Edit_translate_dangle->setObjectName(QString::fromUtf8("Edit_translate_dangle"));
        sizePolicy1.setHeightForWidth(Edit_translate_dangle->sizePolicy().hasHeightForWidth());
        Edit_translate_dangle->setSizePolicy(sizePolicy1);
        Edit_translate_dangle->setMinimum(-360.000000000000000);
        Edit_translate_dangle->setMaximum(360.000000000000000);
        Edit_translate_dangle->setValue(0.000000000000000);

        horizontalLayout_2->addWidget(Edit_translate_dangle);


        verticalLayout_6->addLayout(horizontalLayout_2);


        horizontalLayout_9->addLayout(verticalLayout_6);


        verticalLayout_3->addLayout(horizontalLayout_9);


        horizontalLayout_11->addLayout(verticalLayout_3);

        groupBox_2 = new QGroupBox(tabPath);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        horizontalLayout->addWidget(label_21);

        Edit_bezier_num = new QSpinBox(groupBox_2);
        Edit_bezier_num->setObjectName(QString::fromUtf8("Edit_bezier_num"));
        Edit_bezier_num->setMinimum(1);
        Edit_bezier_num->setMaximum(10);
        Edit_bezier_num->setValue(1);

        horizontalLayout->addWidget(Edit_bezier_num);

        Button_bezier_num = new QPushButton(groupBox_2);
        Button_bezier_num->setObjectName(QString::fromUtf8("Button_bezier_num"));

        horizontalLayout->addWidget(Button_bezier_num);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        Edit_img_location = new QLineEdit(groupBox_2);
        Edit_img_location->setObjectName(QString::fromUtf8("Edit_img_location"));
        Edit_img_location->setReadOnly(true);

        horizontalLayout_7->addWidget(Edit_img_location);

        Button_load_img = new QPushButton(groupBox_2);
        Button_load_img->setObjectName(QString::fromUtf8("Button_load_img"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/path_image/ground.png"), QSize(), QIcon::Normal, QIcon::Off);
        Button_load_img->setIcon(icon);

        horizontalLayout_7->addWidget(Button_load_img);


        verticalLayout->addLayout(horizontalLayout_7);

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
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/icons/Open Folder-96.png"), QSize(), QIcon::Normal, QIcon::Off);
        Button_open_folder->setIcon(icon1);

        horizontalLayout_4->addWidget(Button_open_folder);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        horizontalLayout_5->addWidget(label_19);

        Edit_now_angle = new QDoubleSpinBox(groupBox_2);
        Edit_now_angle->setObjectName(QString::fromUtf8("Edit_now_angle"));
        Edit_now_angle->setMinimum(-180.000000000000000);
        Edit_now_angle->setMaximum(180.000000000000000);

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

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_12->addWidget(label_13);

        Edit_num_btw_two = new QSpinBox(groupBox_2);
        Edit_num_btw_two->setObjectName(QString::fromUtf8("Edit_num_btw_two"));
        Edit_num_btw_two->setMinimum(1);
        Edit_num_btw_two->setMaximum(200);
        Edit_num_btw_two->setValue(40);

        horizontalLayout_12->addWidget(Edit_num_btw_two);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        Sampple_time = new QCheckBox(groupBox_2);
        Sampple_time->setObjectName(QString::fromUtf8("Sampple_time"));

        horizontalLayout_29->addWidget(Sampple_time);

        Sample_distance = new QCheckBox(groupBox_2);
        Sample_distance->setObjectName(QString::fromUtf8("Sample_distance"));

        horizontalLayout_29->addWidget(Sample_distance);


        verticalLayout->addLayout(horizontalLayout_29);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        label_38 = new QLabel(groupBox_2);
        label_38->setObjectName(QString::fromUtf8("label_38"));

        horizontalLayout_30->addWidget(label_38);

        Sample_interval = new QDoubleSpinBox(groupBox_2);
        Sample_interval->setObjectName(QString::fromUtf8("Sample_interval"));
        Sample_interval->setSingleStep(0.100000000000000);

        horizontalLayout_30->addWidget(Sample_interval);


        verticalLayout->addLayout(horizontalLayout_30);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_6->addWidget(label_16);

        spinBox_kspeed = new QSpinBox(groupBox_2);
        spinBox_kspeed->setObjectName(QString::fromUtf8("spinBox_kspeed"));
        spinBox_kspeed->setMaximum(1200);
        spinBox_kspeed->setValue(400);

        horizontalLayout_6->addWidget(spinBox_kspeed);

        Slider_kspeed = new QSlider(groupBox_2);
        Slider_kspeed->setObjectName(QString::fromUtf8("Slider_kspeed"));
        Slider_kspeed->setMaximum(1200);
        Slider_kspeed->setValue(400);
        Slider_kspeed->setSliderPosition(400);
        Slider_kspeed->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(Slider_kspeed);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        horizontalLayout_13->addWidget(label_20);

        Edit_max_speed = new QDoubleSpinBox(groupBox_2);
        Edit_max_speed->setObjectName(QString::fromUtf8("Edit_max_speed"));
        Edit_max_speed->setSingleStep(0.100000000000000);

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

        horizontalLayout_27->addWidget(Edit_max_jerk);


        verticalLayout->addLayout(horizontalLayout_27);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_34 = new QLabel(groupBox_2);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        horizontalLayout_14->addWidget(label_34);

        Edit_bezier_cnt = new QLineEdit(groupBox_2);
        Edit_bezier_cnt->setObjectName(QString::fromUtf8("Edit_bezier_cnt"));
        Edit_bezier_cnt->setReadOnly(true);

        horizontalLayout_14->addWidget(Edit_bezier_cnt);

        label_35 = new QLabel(groupBox_2);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        horizontalLayout_14->addWidget(label_35);


        verticalLayout->addLayout(horizontalLayout_14);

        point_area_2 = new QWidget(groupBox_2);
        point_area_2->setObjectName(QString::fromUtf8("point_area_2"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(point_area_2->sizePolicy().hasHeightForWidth());
        point_area_2->setSizePolicy(sizePolicy4);
        point_area = new QVBoxLayout(point_area_2);
        point_area->setObjectName(QString::fromUtf8("point_area"));
        scrollArea = new QScrollArea(point_area_2);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setWidgetResizable(true);
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 233, 255));
        sizePolicy4.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy4);
        verticalLayoutWidget = new QWidget(widget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 231, 80));
        point_area_3 = new QVBoxLayout(verticalLayoutWidget);
        point_area_3->setSpacing(6);
        point_area_3->setObjectName(QString::fromUtf8("point_area_3"));
        point_area_3->setSizeConstraint(QLayout::SetMinimumSize);
        point_area_3->setContentsMargins(0, 0, 0, 0);
        scrollArea->setWidget(widget);

        point_area->addWidget(scrollArea);


        verticalLayout->addWidget(point_area_2);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        Button_add_point = new QPushButton(groupBox_2);
        Button_add_point->setObjectName(QString::fromUtf8("Button_add_point"));

        horizontalLayout_26->addWidget(Button_add_point);

        Button_delete_point = new QPushButton(groupBox_2);
        Button_delete_point->setObjectName(QString::fromUtf8("Button_delete_point"));

        horizontalLayout_26->addWidget(Button_delete_point);


        verticalLayout->addLayout(horizontalLayout_26);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        Button_create_path = new QPushButton(groupBox_2);
        Button_create_path->setObjectName(QString::fromUtf8("Button_create_path"));

        horizontalLayout_21->addWidget(Button_create_path);

        Button_load_path = new QPushButton(groupBox_2);
        Button_load_path->setObjectName(QString::fromUtf8("Button_load_path"));

        horizontalLayout_21->addWidget(Button_load_path);


        verticalLayout->addLayout(horizontalLayout_21);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        Button_add_bezier = new QPushButton(groupBox_2);
        Button_add_bezier->setObjectName(QString::fromUtf8("Button_add_bezier"));

        horizontalLayout_22->addWidget(Button_add_bezier);

        Button_create_file = new QPushButton(groupBox_2);
        Button_create_file->setObjectName(QString::fromUtf8("Button_create_file"));

        horizontalLayout_22->addWidget(Button_create_file);


        verticalLayout->addLayout(horizontalLayout_22);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        Button_clear = new QPushButton(groupBox_2);
        Button_clear->setObjectName(QString::fromUtf8("Button_clear"));

        horizontalLayout_23->addWidget(Button_clear);

        Button_cmp = new QPushButton(groupBox_2);
        Button_cmp->setObjectName(QString::fromUtf8("Button_cmp"));

        horizontalLayout_23->addWidget(Button_cmp);


        verticalLayout->addLayout(horizontalLayout_23);

        Button_update_point = new QPushButton(groupBox_2);
        Button_update_point->setObjectName(QString::fromUtf8("Button_update_point"));

        verticalLayout->addWidget(Button_update_point);


        horizontalLayout_11->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(tabPath);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_17 = new QLabel(groupBox_3);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        horizontalLayout_3->addWidget(label_17);

        Edit_bezier_length = new QLineEdit(groupBox_3);
        Edit_bezier_length->setObjectName(QString::fromUtf8("Edit_bezier_length"));
        Edit_bezier_length->setReadOnly(true);

        horizontalLayout_3->addWidget(Edit_bezier_length);

        label_18 = new QLabel(groupBox_3);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        horizontalLayout_3->addWidget(label_18);

        Edit_point_num = new QLineEdit(groupBox_3);
        Edit_point_num->setObjectName(QString::fromUtf8("Edit_point_num"));
        Edit_point_num->setReadOnly(true);

        horizontalLayout_3->addWidget(Edit_point_num);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_23 = new QLabel(groupBox_3);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        horizontalLayout_10->addWidget(label_23);

        Edit_posx = new QLineEdit(groupBox_3);
        Edit_posx->setObjectName(QString::fromUtf8("Edit_posx"));
        Edit_posx->setReadOnly(true);

        horizontalLayout_10->addWidget(Edit_posx);

        label_24 = new QLabel(groupBox_3);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        horizontalLayout_10->addWidget(label_24);

        Edit_posy = new QLineEdit(groupBox_3);
        Edit_posy->setObjectName(QString::fromUtf8("Edit_posy"));
        Edit_posy->setReadOnly(true);

        horizontalLayout_10->addWidget(Edit_posy);


        verticalLayout_2->addLayout(horizontalLayout_10);

        label_27 = new QLabel(groupBox_3);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        verticalLayout_2->addWidget(label_27);

        plainTextEdit_input = new QPlainTextEdit(groupBox_3);
        plainTextEdit_input->setObjectName(QString::fromUtf8("plainTextEdit_input"));
        plainTextEdit_input->setReadOnly(true);

        verticalLayout_2->addWidget(plainTextEdit_input);

        label_28 = new QLabel(groupBox_3);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        verticalLayout_2->addWidget(label_28);

        table_out = new QTableView(groupBox_3);
        table_out->setObjectName(QString::fromUtf8("table_out"));
        table_out->setContextMenuPolicy(Qt::DefaultContextMenu);
        table_out->setAutoFillBackground(true);
        table_out->horizontalHeader()->setDefaultSectionSize(60);

        verticalLayout_2->addWidget(table_out);


        horizontalLayout_11->addWidget(groupBox_3);

        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Path_image/ground.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabPath, icon2, QString());

        horizontalLayout_8->addWidget(tabWidget);

#if QT_CONFIG(shortcut)
        label_16->setBuddy(Slider_kspeed);
        label_17->setBuddy(Edit_bezier_length);
        label_18->setBuddy(Edit_point_num);
        label_27->setBuddy(plainTextEdit_input);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(Edit_map_width, Edit_map_heigh);
        QWidget::setTabOrder(Edit_map_heigh, Edit_x_toggle);
        QWidget::setTabOrder(Edit_x_toggle, Edit_y_toggle);
        QWidget::setTabOrder(Edit_y_toggle, Edit_translate_dx);
        QWidget::setTabOrder(Edit_translate_dx, Edit_translate_dy);
        QWidget::setTabOrder(Edit_translate_dy, Edit_translate_dangle);
        QWidget::setTabOrder(Edit_translate_dangle, Edit_bezier_num);
        QWidget::setTabOrder(Edit_bezier_num, Button_bezier_num);
        QWidget::setTabOrder(Button_bezier_num, Edit_img_location);
        QWidget::setTabOrder(Edit_img_location, Button_load_img);
        QWidget::setTabOrder(Button_load_img, Edit_file_location);
        QWidget::setTabOrder(Edit_file_location, Button_open_folder);
        QWidget::setTabOrder(Button_open_folder, Edit_now_angle);
        QWidget::setTabOrder(Edit_now_angle, Edit_target_angle);
        QWidget::setTabOrder(Edit_target_angle, Edit_num_btw_two);
        QWidget::setTabOrder(Edit_num_btw_two, spinBox_kspeed);
        QWidget::setTabOrder(spinBox_kspeed, Slider_kspeed);
        QWidget::setTabOrder(Slider_kspeed, Edit_max_speed);
        QWidget::setTabOrder(Edit_max_speed, Edit_bezier_cnt);
        QWidget::setTabOrder(Edit_bezier_cnt, Button_create_path);
        QWidget::setTabOrder(Button_create_path, Button_load_path);
        QWidget::setTabOrder(Button_load_path, Button_add_bezier);
        QWidget::setTabOrder(Button_add_bezier, Button_create_file);
        QWidget::setTabOrder(Button_create_file, Button_clear);
        QWidget::setTabOrder(Button_clear, Edit_bezier_length);
        QWidget::setTabOrder(Edit_bezier_length, Edit_point_num);
        QWidget::setTabOrder(Edit_point_num, plainTextEdit_input);
        QWidget::setTabOrder(plainTextEdit_input, tabWidget);

        retranslateUi(PagePath);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PagePath);
    } // setupUi

    void retranslateUi(QWidget *PagePath)
    {
        PagePath->setWindowTitle(QCoreApplication::translate("PagePath", "Form", nullptr));
        label_14->setText(QCoreApplication::translate("PagePath", "\346\260\264\345\271\263\351\225\277\345\272\246", nullptr));
        label_15->setText(QCoreApplication::translate("PagePath", "\347\253\226\347\233\264\351\225\277\345\272\246", nullptr));
        label_12->setText(QCoreApplication::translate("PagePath", "X\350\275\264\346\226\271\345\220\221", nullptr));
        label_22->setText(QCoreApplication::translate("PagePath", "Y\350\275\264\346\226\271\345\220\221", nullptr));
        label_30->setText(QCoreApplication::translate("PagePath", "\345\271\263\347\247\273\343\200\201\346\227\213\350\275\254\345\235\220\346\240\207\347\263\273(\351\241\272\346\227\266\351\222\210\344\270\272\346\227\213\350\275\254\346\255\243\346\226\271\345\220\221)", nullptr));
        label_33->setText(QCoreApplication::translate("PagePath", "dX", nullptr));
        label_31->setText(QCoreApplication::translate("PagePath", "dY", nullptr));
        label_32->setText(QCoreApplication::translate("PagePath", "d\302\260", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PagePath", "Initialization", nullptr));
        label_21->setText(QCoreApplication::translate("PagePath", "\350\276\223\345\205\245\346\233\262\347\272\277\346\225\260\351\207\217:", nullptr));
        Button_bezier_num->setText(QCoreApplication::translate("PagePath", "\347\241\256\345\256\232", nullptr));
        Edit_img_location->setText(QCoreApplication::translate("PagePath", "\344\276\213:D:/ground.png", nullptr));
        Button_load_img->setText(QString());
        Edit_file_location->setText(QCoreApplication::translate("PagePath", "\344\276\213:D:/trace.txt", nullptr));
        File_type->setItemText(0, QCoreApplication::translate("PagePath", "trace.txt", nullptr));
        File_type->setItemText(1, QCoreApplication::translate("PagePath", "trace.c", nullptr));
        File_type->setItemText(2, QCoreApplication::translate("PagePath", "trace.doc", nullptr));

#if QT_CONFIG(tooltip)
        Button_open_folder->setToolTip(QCoreApplication::translate("PagePath", "\347\202\271\344\277\235\345\255\230\350\267\257\345\276\204", nullptr));
#endif // QT_CONFIG(tooltip)
        Button_open_folder->setText(QString());
        label_19->setText(QCoreApplication::translate("PagePath", "\350\247\222\345\272\246:", nullptr));
        label_13->setText(QCoreApplication::translate("PagePath", "\344\270\244\347\202\271\344\271\213\351\227\264\347\202\271\346\225\260:", nullptr));
        Sampple_time->setText(QCoreApplication::translate("PagePath", "\347\255\211\346\227\266\351\207\207\346\240\267", nullptr));
        Sample_distance->setText(QCoreApplication::translate("PagePath", "\347\255\211\350\267\235\351\207\207\346\240\267", nullptr));
        label_38->setText(QCoreApplication::translate("PagePath", "\351\207\207\346\240\267\346\227\266\351\227\264(ms)/\350\267\235\347\246\273(m):", nullptr));
#if QT_CONFIG(tooltip)
        label_16->setToolTip(QCoreApplication::translate("PagePath", "\345\217\252\346\230\257\344\273\243\350\241\250\345\277\253\346\205\242\347\250\213\345\272\246\357\274\214\345\271\266\351\235\236\345\256\236\351\231\205\345\244\247\345\260\217", nullptr));
#endif // QT_CONFIG(tooltip)
        label_16->setText(QCoreApplication::translate("PagePath", "\351\200\237\345\272\246\345\277\253\346\205\242:", nullptr));
#if QT_CONFIG(tooltip)
        spinBox_kspeed->setToolTip(QCoreApplication::translate("PagePath", "\345\217\252\346\230\257\344\273\243\350\241\250\345\277\253\346\205\242\347\250\213\345\272\246\357\274\214\345\271\266\351\235\236\345\256\236\351\231\205\345\244\247\345\260\217", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        Slider_kspeed->setToolTip(QCoreApplication::translate("PagePath", "\345\217\252\346\230\257\344\273\243\350\241\250\345\277\253\346\205\242\347\250\213\345\272\246\357\274\214\345\271\266\351\235\236\345\256\236\351\231\205\345\244\247\345\260\217", nullptr));
#endif // QT_CONFIG(tooltip)
        label_20->setText(QCoreApplication::translate("PagePath", "\346\234\200\345\244\247\351\200\237\345\272\246(m/s):", nullptr));
        label_29->setText(QCoreApplication::translate("PagePath", "\346\234\200\345\244\247\345\212\240\351\200\237\345\272\246(m^2/s)\357\274\232", nullptr));
        label_37->setText(QCoreApplication::translate("PagePath", "\346\234\200\345\244\247\345\212\240\345\212\240\351\200\237\345\272\246(m^3/s):", nullptr));
        label_34->setText(QCoreApplication::translate("PagePath", "NO.", nullptr));
#if QT_CONFIG(tooltip)
        Edit_bezier_cnt->setToolTip(QCoreApplication::translate("PagePath", "\346\233\262\347\272\277\350\256\241\346\225\260(\344\270\215\345\217\257\347\274\226\350\276\221)", nullptr));
#endif // QT_CONFIG(tooltip)
        Edit_bezier_cnt->setText(QCoreApplication::translate("PagePath", "0", nullptr));
        label_35->setText(QCoreApplication::translate("PagePath", "\347\254\254\345\207\240\346\235\241Bezier\346\233\262\347\272\277", nullptr));
        Button_add_point->setText(QCoreApplication::translate("PagePath", "\345\212\240\347\202\271", nullptr));
        Button_delete_point->setText(QCoreApplication::translate("PagePath", "\345\210\240\347\202\271", nullptr));
        Button_create_path->setText(QCoreApplication::translate("PagePath", "\347\241\256\345\256\232", nullptr));
        Button_load_path->setText(QCoreApplication::translate("PagePath", "\345\212\240\350\275\275\346\233\262\347\272\277", nullptr));
        Button_add_bezier->setText(QCoreApplication::translate("PagePath", "\350\276\223\345\205\245\344\270\213\344\270\200\346\235\241", nullptr));
        Button_create_file->setText(QCoreApplication::translate("PagePath", "\347\224\237\346\210\220\346\226\207\344\273\266", nullptr));
        Button_clear->setText(QCoreApplication::translate("PagePath", "\346\270\205\347\251\272", nullptr));
        Button_cmp->setText(QCoreApplication::translate("PagePath", "\346\233\262\347\272\277\346\257\224\345\257\271", nullptr));
        Button_update_point->setText(QCoreApplication::translate("PagePath", "\346\233\264\346\226\260\350\276\223\345\207\272", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("PagePath", "Other Functions", nullptr));
        label_17->setText(QCoreApplication::translate("PagePath", "\350\275\250\350\277\271\346\200\273\351\225\277", nullptr));
#if QT_CONFIG(tooltip)
        Edit_bezier_length->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_18->setText(QCoreApplication::translate("PagePath", "\350\275\250\350\277\271\347\202\271\346\225\260", nullptr));
        label_23->setText(QCoreApplication::translate("PagePath", "carposX:", nullptr));
        label_24->setText(QCoreApplication::translate("PagePath", "carposY:", nullptr));
        label_27->setText(QCoreApplication::translate("PagePath", "\350\276\223\345\205\245", nullptr));
        plainTextEdit_input->setDocumentTitle(QCoreApplication::translate("PagePath", "input_points", nullptr));
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
