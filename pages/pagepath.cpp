#include "pagepath.h"
#include "ui_pagepath.h"
#include "ui_txtdialog.h"
#include <QString>
#include <QImage>
#include <QBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <cmath>
#include <QGraphicsEllipseItem>
#include <QPainterPath>

float map_width = 0;
float map_height = 0;
float map_width_pixel = 0;
float map_height_pixel = 0;
double translate_dx = 0;
double translate_dy = 0;
double translate_dangle = 0;
int toggle_x = 1;
int toggle_y = 1;
QPointF *carpos = new QPointF[1000];
int carpos_cnt = 0;
int point_num;
QLabel *nowPointValueLabel;

Bezier *bezier_path = new Bezier[10];
int bezier_num = 1;
int bezier_cnt = 0;
float res_w=0;
float res_h=0;
float width_t=0;
float height_t=0;

/***************************************************************
 *  @brief     主窗口初始化
 *  @param     parent,继承了QWidget类
 *  @note      无
 *  @Sample usage     无
 *  @author    zh
 *  @      2020/2/17
 **************************************************************/
PagePath::PagePath(QWidget *parent) : QWidget(parent),
    ui(new Ui::PagePath)
{

    ui->setupUi(this);
    mVesc = 0;

    img = new QImage;
    img->load(":/res/path_image/ground.png");

    newImg = new QImage;

    translate_dx = ui->Edit_translate_dx->text().toDouble();
    translate_dy = ui->Edit_translate_dy->text().toDouble();
    translate_dangle = ui->Edit_translate_dangle->text().toDouble();

    ui->scrollArea->setWidget(ui->widget);
    ui->widget->setMinimumSize(500,1000);

    init_table_out();
    table_update();

    MyGraphicsView=ui->graphicsView;
    MyGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    MyGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    MyGraphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    pointScene=new MyGraphicsScene(this);
    MyGraphicsView->setScene(pointScene);

    buttonLoadPathClickedNum=0;
    setMouseTracking(true);

    nowPointValueLabel=ui->nowPoint;
}


PagePath::~PagePath()
{
    delete ui;
}

/**
 * @brief 初始化输出表
 *
 */
void PagePath::init_table_out()
{
    model = new QStandardItemModel;
    QStringList headerList;
    headerList << "Num"
               << "X"
               << "Y"
               << "Speed"
               << "Direct"
               << "Angle";
    model->setHorizontalHeaderLabels(headerList);
    ui->table_out->setModel(model);
    ui->table_out->setColumnWidth(0, 50); // 设置列的宽度
    /*ui->table_out->setColumnWidth(1, 50);
    ui->table_out->setColumnWidth(2, 50);
    ui->table_out->setColumnWidth(3, 50);
    ui->table_out->setColumnWidth(4, 50);
    ui->table_out->setColumnWidth(5, 50);*/
}


/**
 * @brief 更新输出表
 *
 */
void PagePath::table_update()
{
    for (int i = 0; i <= bezier_path[bezier_cnt].out_num; i++)
    {
        QString num = QString::asprintf("%d", i);
        aItem = new QStandardItem(num);            // 创建item对象
        aItem->setTextAlignment(Qt::AlignHCenter); // 设置item值，居中对齐
        model->setItem(i, 0, aItem);               // 将item写入model指定位置

        QString x = QString::asprintf("%.3f", bezier_path[bezier_cnt].out_points[i].X);
        aItem = new QStandardItem(x);
        aItem->setTextAlignment(Qt::AlignHCenter);
        model->setItem(i, 1, aItem);
        QString y = QString::asprintf("%.3f", bezier_path[bezier_cnt].out_points[i].Y);
        aItem = new QStandardItem(y);
        aItem->setTextAlignment(Qt::AlignHCenter);
        model->setItem(i, 2, aItem);

        QString speed = QString::asprintf("%d", bezier_path[bezier_cnt].speed[i]);
        aItem = new QStandardItem(speed);
        aItem->setTextAlignment(Qt::AlignHCenter);
        model->setItem(i, 3, aItem);

        QString direct = QString::asprintf("%.3f", bezier_path[bezier_cnt].direct[i]);
        aItem = new QStandardItem(direct);
        aItem->setTextAlignment(Qt::AlignHCenter);
        model->setItem(i, 4, aItem);

        QString angle = QString::asprintf("%.3f", bezier_path[bezier_cnt].angle[i]);
        aItem = new QStandardItem(angle);
        aItem->setTextAlignment(Qt::AlignHCenter);
        model->setItem(i, 5, aItem);
    }

    ui->table_out->setModel(model);
    ui->table_out->verticalHeader()->hide();
}


VescInterface *PagePath::vesc() const
{
    return mVesc;
}


void PagePath::setVesc(VescInterface *vesc)
{
    mVesc = vesc;
    if (mVesc)
    {
        connect(mVesc->commands(), SIGNAL(drawpos(float, float)),
                this, SLOT(drawpos(float, float)));
    }
}


/**
 * @brief 打印轨迹点
 *
 * @param x
 * @param y
 */
void PagePath::drawpos(float x, float y)
{
    carpos[carpos_cnt++].setX(x);
    carpos[carpos_cnt++].setY(y);
    QString pos_ = "";
    pos_.sprintf("%.3f", x);
    ui->Edit_posx->setText(pos_);
    pos_.sprintf("%.3f", y);
    ui->Edit_posy->setText(pos_);
}


/**
 * @brief 点击输入曲线数量按钮
 *
 */
void PagePath::on_Button_bezier_num_clicked()
{
    if (ui->Edit_bezier_num->text().isEmpty())
    {
        QMessageBox::warning(NULL, "贝塞尔曲线数量不能为0", "请输入正确的数目", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    bezier_num = ui->Edit_bezier_num->text().toInt();
}


QPointF PagePath::cal_rotate_point(float x,float y)
{
    if(translate_dangle==0)
    {
        return QPointF((translate_dy+toggle_x*x)*width_t,(translate_dx+toggle_y*y)*height_t);
    }
    else
    {
        float x_val=x*cos(translate_dangle * M_PI / 180.0) - y*sin(translate_dangle * M_PI / 180.0);
        float y_val=y*cos(translate_dangle * M_PI / 180.0) + x*sin(translate_dangle * M_PI / 180.0);
        return  QPointF((translate_dy+toggle_x*x_val)*width_t, (translate_dx+toggle_y*y_val)*height_t);
    }
}

/**
 * @brief 点击加载曲线按钮
 *
 */
void PagePath::on_Button_load_path_clicked()
{
    if(buttonLoadPathClickedNum!=0)
    {
        return;
    }
    buttonLoadPathClickedNum++;
    pointScene->clear();
    translate_dx=ui->Edit_translate_dx->text().toDouble();
    translate_dy=ui->Edit_translate_dy->text().toDouble();
    toggle_x=ui->Edit_x_toggle->text().toInt();
    toggle_y=ui->Edit_y_toggle->text().toInt();

    map_width=ui->Edit_map_width->text().toFloat();
    map_height=ui->Edit_map_heigh->text().toFloat();
    map_width_pixel=img->width();
    map_height_pixel=img->height();
    res_w=ui->graphicsView->width();
    res_h=res_w*(map_height_pixel/map_width_pixel);
    MyGraphicsView->resize(res_w,res_h);
    MyGraphicsView->setFixedSize(res_w,res_h);
    pointScene->setSceneRect(0,0,res_w,res_h);
    width_t=float(res_w)/map_width;
    height_t=res_h/map_height;
    *newImg=img->scaled(res_w,res_h);
    pointScene->addPixmap(QPixmap::fromImage(*newImg));

    // 绘制坐标系
    // 绘制箭头
    QVector<QPointF> xAxisArrowheadPolygon(3);
    QVector<QPointF> yAxisArrowheadPolygon(3);
    xAxisArrowheadPolygon[0].setX(cal_rotate_point(2,0.1).x());
    xAxisArrowheadPolygon[0].setY(cal_rotate_point(2,0.1).y());
    xAxisArrowheadPolygon[1].setX(cal_rotate_point(2,-0.1).x());
    xAxisArrowheadPolygon[1].setY(cal_rotate_point(2,-0.1).y());
    xAxisArrowheadPolygon[2].setX(cal_rotate_point(2.2,0).x());
    xAxisArrowheadPolygon[2].setY(cal_rotate_point(2.2,0).y());

    yAxisArrowheadPolygon[0].setX(cal_rotate_point(0.1,2).x());
    yAxisArrowheadPolygon[0].setY(cal_rotate_point(0.1,2).y());
    yAxisArrowheadPolygon[1].setX(cal_rotate_point(-0.1,2).x());
    yAxisArrowheadPolygon[1].setY(cal_rotate_point(-0.1,2).y());
    yAxisArrowheadPolygon[2].setX(cal_rotate_point(0,2.2).x());
    yAxisArrowheadPolygon[2].setY(cal_rotate_point(0,2.2).y());

    QPolygonF xAxisArrowhead=QPolygonF(xAxisArrowheadPolygon);
    QPolygonF yAxisArrowhead=QPolygonF(yAxisArrowheadPolygon);
    pointScene->addPolygon(xAxisArrowhead,QPen(QBrush(Qt::blue), 1), QBrush(Qt::blue));
    pointScene->addPolygon(yAxisArrowhead,QPen(QBrush(Qt::blue), 1), QBrush(Qt::blue));

    // 绘制坐标轴标签
    QPainterPath xAixs;
    QPainterPath yAixs;
    QFont axisFont;
    axisFont.setPixelSize(16);
    axisFont.setBold(false);
    xAixs.addText(cal_rotate_point(2.5,0).x(),cal_rotate_point(2.5,0).y(),axisFont,"X");
    yAixs.addText(cal_rotate_point(0,2.5).x(),cal_rotate_point(0,2.5).y(),axisFont,"Y");
    pointScene->addPath(xAixs,QPen(QBrush(Qt::blue), 1), QBrush(Qt::blue));
    pointScene->addPath(yAixs,QPen(QBrush(Qt::blue), 1), QBrush(Qt::blue));

    // 绘制坐标轴
    pointScene->addLine(cal_rotate_point(0,0).x(),cal_rotate_point(0,0).y(),cal_rotate_point(2,0).x(),cal_rotate_point(2,0).y(),QPen(QBrush(Qt::blue), 3));
    pointScene->addLine(cal_rotate_point(0,0).x(),cal_rotate_point(0,0).y(),cal_rotate_point(0,2).x(),cal_rotate_point(0,2).y(),QPen(QBrush(Qt::blue), 3));

    // 绘制点
    for(int i=0;i<=bezier_path[bezier_cnt].out_num;i++)
    {
        QPointF point;
        point.setX(cal_rotate_point(bezier_path[bezier_cnt].out_points[i].X,bezier_path[bezier_cnt].out_points[i].Y).x());
        point.setY(cal_rotate_point(bezier_path[bezier_cnt].out_points[i].X,bezier_path[bezier_cnt].out_points[i].Y).y());
        MyGraphicsItem *pointItem;
        if(i%bezier_path[bezier_cnt].num_btw_two==0)
        {
            pointItem=new MyGraphicsItem(QColor(Qt::red));
        }
        else
        {
            pointItem=new MyGraphicsItem(QColor(Qt::green));
        }

        pointItem->setRect(0,0,4,4);
        pointItem->setPos(point.x(),point.y());
        qDebug()<<point.x()<<point.y();
        pointScene->addItem(pointItem);
        MyGraphicsView->show();
    }
}


/**
 * @brief 点击“输入下一条”按钮
 *
 *
 */
void PagePath::on_Button_add_bezier_clicked()
{
    bezier_cnt = (bezier_cnt + 1) % bezier_num;
    ui->Edit_bezier_cnt->clear();
    QString cnt = "";
    cnt.sprintf("%d", bezier_cnt);
    ui->Edit_bezier_cnt->setText(cnt);

    QMessageBox::information(NULL, "提示", "请输入过程点",
                             QMessageBox::Yes, QMessageBox::Yes);
}


/**
 * @brief 点击“确定”按钮
 *
 */
void PagePath::on_Button_create_path_clicked()
{
    buttonLoadPathClickedNum=0;
    // 获取坐标系旋转角度
    translate_dangle = ui->Edit_translate_dangle->text().toDouble();


    // 获取路径点
    bezier_path[bezier_cnt].input_num = 0;
    bezier_path[bezier_cnt].num_btw_two = ui->Edit_num_btw_two->text().toInt();
    bezier_path[bezier_cnt].k_speed = ui->Slider_kspeed->value();
    bezier_path[bezier_cnt].max_speed = ui->Edit_max_speed->text().toInt();
    bezier_path[bezier_cnt].now_angle = ui->Edit_now_angle->text().toFloat();
    bezier_path[bezier_cnt].target_angle = ui->Edit_target_angle->text().toFloat();

    for(int i=0;i<point_num;i++)
    {
        QString p_name = "point" + QString::number(i);
        QWidget *p = ui->groupBox_2->findChild<QWidget *>(p_name);
        QList<QLineEdit *> items = p->findChildren<QLineEdit *>();
        if(!items[0]->text().isEmpty() && !items[1]->text().isEmpty())
        {
            bezier_path[bezier_cnt].input_points[i].X =items[0]->text().toFloat();
            bezier_path[bezier_cnt].input_points[i].Y =items[1]->text().toFloat();
            bezier_path[bezier_cnt].input_num++;
        }

    }

    if (bezier_path[bezier_cnt].input_num==0)
    {
        QMessageBox::warning(NULL, "过程点数量不能为0", "请输入正确的过程点", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }

    // 路径规划
    bezier_path[bezier_cnt].out_num = (bezier_path[bezier_cnt].input_num - 1) * bezier_path[bezier_cnt].num_btw_two;

    bezier_path[bezier_cnt].ctrlpoints_get();

    bezier_path[bezier_cnt].outpoints_get();

    bezier_path[bezier_cnt].calculate_length();

    bezier_path[bezier_cnt].direct_planning();

    bezier_path[bezier_cnt].angle_planning();

    // 速度规划
    if (bezier_path[bezier_cnt].input_num == 2)
    {
        bezier_path[bezier_cnt].strghtline_speed_plan();
    }
    else if (bezier_path[bezier_cnt].input_num > 2 && bezier_path[bezier_cnt].input_num < 7)
    {
        bezier_path[bezier_cnt].speed_planning();
    }
    else if (bezier_path[bezier_cnt].input_num == 7)
    {
        bezier_path[bezier_cnt].strghtline_speed_plan();
    }

    /*输入点提醒*/
    ui->plainTextEdit_input->clear();
    QString input_warning = "";
    input_warning.sprintf("第%d条贝塞尔曲线\r\n", bezier_cnt);
    ui->plainTextEdit_input->insertPlainText(input_warning);
    for (int i = 0; i < bezier_path[bezier_cnt].input_num; i++)
    {
        input_warning.sprintf("第%d个点,(%.3f,%.3f)\r\n", i, bezier_path[bezier_cnt].input_points[i].X, bezier_path[bezier_cnt].input_points[i].Y);
        ui->plainTextEdit_input->insertPlainText(input_warning);
    }

    /*输出点个数*/
    ui->Edit_point_num->clear();
    QString bezier_num = "";
    bezier_num.sprintf("%d", bezier_path[bezier_cnt].out_num + 1);
    ui->Edit_point_num->setText(bezier_num);

    /*路径长度*/
    ui->Edit_bezier_length->clear();
    QString bezier_length = "";
    bezier_length.sprintf("%.3f", bezier_path[bezier_cnt].length);
    ui->Edit_bezier_length->setText(bezier_length);

    /*输出点提醒*/
    init_table_out();
    table_update();
}


/**
 * @brief 点击“生成文件”按钮
 *
 */
void PagePath::on_Button_create_file_clicked()
{
    if (ui->Edit_file_location->text().isEmpty())
    {
        QMessageBox::warning(NULL, "无路径", "请输入生成文件路径", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }

    /*保存文件*/
    QString address = ui->Edit_file_location->text();
    QFile file(address);
    if (file.open(QFile::WriteOnly | QFile::Truncate | QIODevice::Text | QIODevice::Append))
    {
        char *ch;
        QString code;
        QByteArray ba = "#include<point.h>\r\n";
        ba.append("/*X    Y   SPEED   DIRECT  ANGLE*/ \r\n");

        for (int i = 0; i < bezier_num; i++)
        {
            code.sprintf("/*No.%d Bezier path has %d points in total.*/", i, bezier_path[i].out_num + 1);
            code.append("\r\n");
            ba.append(code);
            code.sprintf("const Points points_pos[%d]{\r\n", i);
            ba.append(code);
            for (int j = 0; j <= bezier_path[i].out_num; j++)
            {
                code.sprintf("{%f,     %f,     %d,     %f,     %f},",
                             bezier_path[i].out_points[j].X, bezier_path[i].out_points[j].Y,
                             bezier_path[i].speed[j], bezier_path[i].direct[j], bezier_path[i].angle[j]);
                ba.append(code);
                code.sprintf("      /*point ranks %d*/", j);
                code.append("\r\n");
                ba.append(code);
            }
            code.sprintf("};\r\n");
            ba.append(code);
        }

        ch = ba.data();
        file.write(ch);
        file.close();
    }

    /*检验文件是否创建成功*/
    if (!file.open(QFile::ReadOnly))
    {
        QMessageBox::information(NULL, "warning", "保存文件失败，请检查路径",
                                 QMessageBox::Yes, QMessageBox::Yes);
        return;
    }

    /*通过dialog输出*/
    QString displaystr;
    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        displaystr.append(line);
    }
    QApplication::setOverrideCursor(Qt::WaitCursor);
    txtdialog = new txtDialog(this);
    txtdialog->setModal(false);
    txtdialog->ui->textEdit->setPlainText(displaystr);
    QApplication::restoreOverrideCursor();
    txtdialog->show();
    QMessageBox::information(NULL, "提示", "保存点成功",
                             QMessageBox::Yes, QMessageBox::Yes);
}


/**
 * @brief 点击“清空”按钮
 *
 */
void PagePath::on_Button_clear_clicked()
{
    init_table_out();
    ui->plainTextEdit_input->clear();
    ui->Edit_bezier_length->clear();
    ui->Edit_point_num->clear();

    for(int i=0;i<point_num;i++)
    {
        QString p_name = "point" + QString::number(i);
        QWidget *p = ui->groupBox_2->findChild<QWidget *>(p_name);
        QList<QLineEdit *> items = p->findChildren<QLineEdit *>();
        for (QLineEdit *item : items)
        {
            item->clear();
        }
    }

    ui->Edit_bezier_cnt->setText("0");
    if (bezier_path)
    {
        delete bezier_path;
        Bezier *bezier_path = new Bezier[10];
    }
    bezier_cnt = 0;
    bezier_num = 1;
}


/**
 * @brief 点击“选择文件保存路径”图标
 *
 */
void PagePath::on_Button_open_folder_clicked()
{
    QString tempDir = QFileDialog::getExistingDirectory(this,
                                                        "Choose directory", "/");
    if (!tempDir.isEmpty())
    {
        tempDir.append('/');
        QString file_type = ui->File_type->currentText();
        tempDir.append(file_type);
        ui->Edit_file_location->setText(tempDir);
    }
    else
    {
        QMessageBox::information(NULL, "error", "No Directory",
                                 QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
}


/**
 * @brief 点击“选择图片”图标
 *
 */
void PagePath::on_Button_load_img_clicked()
{
    QString tempFilename = QFileDialog::getOpenFileName(this,
                                                        "Choose picture", "/",
                                                        "Image Files(*.jpg *.png *.bmp *.jpeg *.gif *.tga)");
    if (!tempFilename.isEmpty())
    {
        ui->Edit_file_location->setText(tempFilename);
    }
    else
    {
        QMessageBox::information(NULL, "error", "No such file",
                                 QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    ui->Edit_img_location->setText(tempFilename);
    img->load(tempFilename);

    pointScene->clear();
    map_width=ui->Edit_map_width->text().toFloat();
    map_height=ui->Edit_map_heigh->text().toFloat();
    map_width_pixel=img->width();
    map_height_pixel=img->height();
    res_w=ui->graphicsView->width();
    res_h=res_w*(map_height_pixel/map_width_pixel);
    MyGraphicsView->resize(res_w,res_h);
    MyGraphicsView->setFixedSize(res_w,res_h);
    pointScene->setSceneRect(0,0,res_w,res_h);
    width_t=float(res_w)/map_width;
    height_t=res_h/map_height;
    *newImg=img->scaled(res_w,res_h);
    pointScene->addPixmap(QPixmap::fromImage(*newImg));
}


/**
 * @brief PagePath::on_Button_add_point_clicked 点击“加点”按钮
 */
void PagePath::on_Button_add_point_clicked()
{
    point_line = new QHBoxLayout();
    point_line->setMargin(0);

    xy = new QLabel();
    xy->setText("x" + QString::number(point_num) + ":");
    point_line->addWidget(xy);
    point = new QLineEdit();
    point->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    point_line->addWidget(point);

    xy = new QLabel();
    xy->setText("y" + QString::number(point_num) + ":");
    point_line->addWidget(xy);
    point = new QLineEdit();
    point->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    point_line->addWidget(point);

    QWidget *p = new QWidget;
    p->setObjectName("point" + QString::number(point_num));
    p->setLayout(point_line);
    ui->point_area_3->addWidget(p);
    point_num++;
}


/**
 * @brief PagePath::on_Button_delete_point_clicked  点击删点按钮
 */
void PagePath::on_Button_delete_point_clicked()
{
    if (point_num > 0)
    {
        QString p_name = "point" + QString::number(point_num - 1);
        QWidget *p = ui->groupBox_2->findChild<QWidget *>(p_name);
        QList<QWidget *> items = p->findChildren<QWidget *>();
        for (QWidget *item : items)
        {
            delete item;
        }
        delete p;
        point_num--;
    }
}


/**
 * @brief PagePath::on_Sampple_time_clicked 勾选采样时间槽函数
 * @param checked
 */
void PagePath::on_Sampple_time_clicked(bool checked)
{
    if(checked)
    {
        ui->Sample_distance->setCheckState(Qt::CheckState::Unchecked);
    }

}


/**
 * @brief PagePath::on_Sample_distance_clicked 勾选采样距离槽函数
 * @param checked
 */
void PagePath::on_Sample_distance_clicked(bool checked)
{
    if(checked)
    {
        ui->Sampple_time->setCheckState(Qt::CheckState::Unchecked);
    }
    ui->Sampple_time->setCheckState(Qt::CheckState::Unchecked);
}


/**
 * @brief PagePath::on_Button_update_point_clicked 点击更新按钮
 */
void PagePath::on_Button_update_point_clicked()
{
    init_table_out();
    table_update();
}

