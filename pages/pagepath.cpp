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
#include <QVector>
#include <QSizePolicy>
#include <time_optimizer/trajectory_generator.h>


double map_width = 0;
double map_height = 0;
double map_width_pixel = 0;
double map_height_pixel = 0;
double translate_dx = 0;
double translate_dy = 0;
double translate_dangle = 0;
int toggle_x = 1;
int toggle_y = 1;
QPointF *carpos = new QPointF[1000];
int carpos_cnt = 0;
int point_num;
QLabel *nowPointValueLabel;

Bezier *bezier_path = new Bezier[1];

int traj_num = 1;
int traj_Edit_idx = 0;
int bezier_num = 1;
int bezier_cnt = 0;
double res_w=0;
double res_h=0;
double width_t=0;
double height_t=0;

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
    mVesc = nullptr;
    //加载场地图
    img = new QImage;
    img->load(":/res/path_image/ground.png");

    newImg = new QImage;
    //初始化坐标变换
    translate_dx = ui->Edit_translate_dx->text().toDouble();
    translate_dy = ui->Edit_translate_dy->text().toDouble();
    translate_dangle = ui->Edit_translate_dangle->text().toDouble();

    ui->scrollArea->setWidget(ui->widget);
    ui->widget->setMinimumSize(500,1000);
    traj_generator.reset(new TimeOptimizerTraj( ui->Edit_max_speed->text().toDouble(),
                                                ui->Edit_max_acceleration->text().toDouble()));
    model = new QStandardItemModel();
    init_table_out();
    table_update();

    trajPlotView = new TrajectoryPlotGraphicsView(this);
    trajPlotView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    trajPlotView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    trajPlotView->setAlignment(Qt::AlignLeft | Qt::AlignTop );
    trajPlotView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->verticalLayout_3->insertWidget(0,trajPlotView,2);
    //widget has not been painted in constructor. to get right size, override showevent and get them.



    buttonLoadPathClickedNum=0;
    setMouseTracking(true);

    nowPointValueLabel=ui->nowPoint;


}


PagePath::~PagePath()
{
    plotKeyPt.clear();
    plotWayPt.clear();
    trajPlotView->scene()->clear();
    delete trajPlotView;
    delete ui;
//    delete txtdialog;

}

/**
 * @brief 初始化输出表
 *
 */
void PagePath::init_table_out()
{
    model->clear();
//    model->setRowCount(1);
    QStringList headerList;
    headerList << "Time"
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
//    if( !traj_Edit_idx ) {return;}
    if(!traj_generator->isHasTraj()){return;}
    int rowcnt=0;
    QStringList headerList;
    for (int segment = 0; segment < generated_ptsSegList.size(); segment++)
    {
        for (auto ctrlCmd: generated_ptsSegList[segment]) {
            // 将item写入model指定位置
            QList<QStandardItem*> rowList;
            headerList.append( QString::number(rowcnt));

            QString time = QString::asprintf("%.3f",ctrlCmd.time);
            aItem = new QStandardItem(time);
            aItem->setTextAlignment(Qt::AlignHCenter);
            rowList.push_back(aItem);

            QString x = QString::asprintf("%.3f", ctrlCmd.pos.x());
            aItem = new QStandardItem(x);
            aItem->setTextAlignment(Qt::AlignHCenter);
            rowList.push_back(aItem);

            QString y = QString::asprintf("%.3f", ctrlCmd.pos.y());
            aItem = new QStandardItem(y);
            aItem->setTextAlignment(Qt::AlignHCenter);
            rowList.push_back(aItem);

            QString speed = QString::asprintf("%.3f", ctrlCmd.speed);
            aItem = new QStandardItem(speed);
            aItem->setTextAlignment(Qt::AlignHCenter);
            rowList.push_back(aItem);

            QString direct = QString::asprintf("%.3f", ctrlCmd.dir);
            aItem = new QStandardItem(direct);
            aItem->setTextAlignment(Qt::AlignHCenter);
            rowList.push_back(aItem);

            QString angle = QString::asprintf("%.3f",ctrlCmd.angle);
            aItem = new QStandardItem(angle);
            aItem->setTextAlignment(Qt::AlignHCenter);
            rowList.push_back(aItem);

            model->appendRow(rowList);
            rowcnt++;
        }

    }

    ui->table_out->setModel(model);
//    ui->table_out->verticalHeader()->hide();
}


VescInterface *PagePath::vesc() const
{
    return mVesc;
}


void PagePath::setVesc(VescInterface *vesc)
{
    mVesc = vesc;
//    if (mVesc)
//    {
//        connect(mVesc->commands(), SIGNAL(drawCarPos(float, float)),
//                this, SLOT(drawCarPos(float, float)));
//    }
}


/**
 * @brief 打印小车轨迹点
 *
 * @param x
 * @param y
 */
void PagePath::drawCarPos(float x, float y)
{
//    carpos[carpos_cnt++].setX(x);
//    carpos[carpos_cnt++].setY(y);
//    QString pos_ = "";
//    pos_=QString::asprintf("%.3f", x);
//    ui->Edit_posx->setText(pos_);
//    pos_=QString::asprintf("%.3f", y);
//    ui->Edit_posy->setText(pos_);
}


QPointF cal_rotate_point(double x,double y,double dangle,double dx,double dy,int toggle_x,int toggle_y,double w,double h)
{
    if(dangle==0)
    {
        return {(dx+toggle_x*x)*w,(dy+toggle_y*y)*h};
    }
    else
    {
        float x_val=x*cos(dangle * M_PI / 180.0) - y*sin(dangle * M_PI / 180.0);
        float y_val=y*cos(dangle * M_PI / 180.0) + x*sin(dangle * M_PI / 180.0);
        return  {(dx+toggle_x*x_val)*w, (dy+toggle_y*y_val)*h};
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
    trajPlotView->scene()->clear();
    plotKeyPt.clear();plotWayPt.clear();
    translate_dx=ui->Edit_translate_dx->text().toDouble();
    translate_dy=ui->Edit_translate_dy->text().toDouble();
    toggle_x=ui->Edit_x_toggle->text().toInt();
    toggle_y=ui->Edit_y_toggle->text().toInt();

    map_width=ui->Edit_map_width->text().toFloat();
    map_height=ui->Edit_map_heigh->text().toFloat();


    // 绘制坐标系
    // 绘制箭头
    QVector<QPointF> xAxisArrowheadPolygon(3);
    QVector<QPointF> yAxisArrowheadPolygon(3);
    xAxisArrowheadPolygon[0]=(cal_rotate_point(2,0.1,translate_dangle,translate_dx,translate_dy,
                                               toggle_x,toggle_y,width_t,height_t));
    xAxisArrowheadPolygon[1]=(cal_rotate_point(2,-0.1,translate_dangle,translate_dx,translate_dy,
                                               toggle_x,toggle_y,width_t,height_t));
    xAxisArrowheadPolygon[2]=(cal_rotate_point(2.2,0,translate_dangle,translate_dx,translate_dy,
                                               toggle_x,toggle_y,width_t,height_t));

    yAxisArrowheadPolygon[0]=(cal_rotate_point(0.1,2,translate_dangle,translate_dx,translate_dy,
                                               toggle_x,toggle_y,width_t,height_t));
    yAxisArrowheadPolygon[1]=(cal_rotate_point(-0.1,2,translate_dangle,translate_dx,translate_dy,
                                               toggle_x,toggle_y,width_t,height_t));
    yAxisArrowheadPolygon[2]=(cal_rotate_point(0,2.2,translate_dangle,translate_dx,translate_dy,
                                               toggle_x,toggle_y,width_t,height_t));

    QPolygonF xAxisArrowhead=QPolygonF(xAxisArrowheadPolygon);
    QPolygonF yAxisArrowhead=QPolygonF(yAxisArrowheadPolygon);
    trajPlotView->TrajectoryPlotGraphicsScene->addPolygon(xAxisArrowhead,
                                                          QPen(QBrush(Qt::blue), 1),
                                                          QBrush(Qt::blue)
                                                          );
    trajPlotView->TrajectoryPlotGraphicsScene->addPolygon(yAxisArrowhead,
                                                          QPen(QBrush(Qt::blue), 1),
                                                          QBrush(Qt::blue)
                                                          );

    // 绘制坐标轴标签
    QPainterPath xAixs;
    QPainterPath yAixs;
    QFont axisFont;
    axisFont.setPixelSize(16);
    axisFont.setBold(false);
    xAixs.addText(cal_rotate_point(2.5,0,translate_dangle,
                                   translate_dx,translate_dy,
                                   toggle_x,toggle_y,
                                   width_t,height_t),axisFont,"X");
    yAixs.addText(cal_rotate_point(0,2.5,translate_dangle,
                                   translate_dx,translate_dy,
                                   toggle_x,toggle_y,
                                   width_t,height_t),axisFont,"Y");
    trajPlotView->TrajectoryPlotGraphicsScene->addPath(xAixs,
                                                       QPen(QBrush(Qt::blue), 1),
                                                       QBrush(Qt::blue)
                                                       );
    trajPlotView->TrajectoryPlotGraphicsScene->addPath(yAixs,
                                                       QPen(QBrush(Qt::blue), 1),
                                                       QBrush(Qt::blue)
                                                       );

    // 绘制坐标轴
    QPointF originPt = cal_rotate_point(0,0,translate_dangle,
                                        translate_dx,translate_dy,
                                        toggle_x,toggle_y,
                                        width_t,height_t);
    QPointF yaxisPt = cal_rotate_point(0,2,translate_dangle,
                                        translate_dx,translate_dy,
                                        toggle_x,toggle_y,
                                        width_t,height_t);
    QPointF xaxisPt = cal_rotate_point(2,0,translate_dangle,
                                       translate_dx,translate_dy,
                                       toggle_x,toggle_y,
                                       width_t,height_t);
    trajPlotView->TrajectoryPlotGraphicsScene->addLine({originPt,xaxisPt}, QPen(QBrush(Qt::blue), 3));
    trajPlotView->TrajectoryPlotGraphicsScene->addLine({originPt,yaxisPt}, QPen(QBrush(Qt::blue), 3));

    // 绘制点
    int ptCnt=0;
    for(const auto& segment : generated_ptsSegList)
    {
        WayPtGraphicsItem* pointItem;
        for(auto ptIter=segment.begin();ptIter!=segment.end();ptIter++)
        {
            if(ptIter == segment.begin() || ptCnt==generated_ptsNnum)
            {
                pointItem = new WayPtGraphicsItem(WayPtGraphicsItem::KEY_POINT);
                plotKeyPt.push_back(pointItem);
            }
            else
            {
                pointItem= new WayPtGraphicsItem(WayPtGraphicsItem::WAY_POINT);
                plotWayPt.push_back(pointItem);
            }
            pointItem->setPointIndex(ptCnt);
            pointItem->setPointTime(ptIter->time);
            QPointF plotPoint;
            plotPoint = cal_rotate_point(ptIter->pos.x(), ptIter->pos.y(),
                                         translate_dangle,
                                         translate_dx, translate_dy,
                                         toggle_x, toggle_y,
                                         width_t, height_t);
            pointItem->setRect(0,0,4,4);
            pointItem->setPos(plotPoint);
            trajPlotView->TrajectoryPlotGraphicsScene->addItem(pointItem);

            ptCnt++;
        }

//        plotPoint.setY(cal_rotate_point(bezier_path[bezier_cnt].out_points[i].X, bezier_path[bezier_cnt].out_points[i].Y).y());

    }
    trajPlotView->show();
}


/**
 * @brief 点击“确定”按钮，开始规划轨迹
 *
 */
void PagePath::on_Button_create_path_clicked()
{
    buttonLoadPathClickedNum=0;
    // 获取坐标系旋转角度
    translate_dangle = ui->Edit_translate_dangle->text().toDouble();


    // 获取路径点
//    bezier_path[traj_Edit_idx].input_num = 0;
//    bezier_path[traj_Edit_idx].num_btw_two = ui->Edit_num_btw_two->text().toInt();
//    bezier_path[traj_Edit_idx].k_speed = ui->Slider_kspeed->value();
//    bezier_path[traj_Edit_idx].max_speed = ui->Edit_max_speed->text().toInt();
//    bezier_path[traj_Edit_idx].now_angle = ui->Edit_now_angle->text().toFloat();
//    bezier_path[traj_Edit_idx].target_angle = ui->Edit_target_angle->text().toFloat();

    //运动学参数获取
    double max_v,max_acc,max_jerk,target_angle;
    max_v = ui->Edit_max_speed->text().toDouble();
    max_acc = ui->Edit_max_acceleration->text().toDouble();
    max_jerk = ui->Edit_max_jerk->text().toDouble();

    traj_generator->setMaxVel(max_v);
    traj_generator->setMaxAcc(max_acc);
    traj_generator->setMaxDAcc(max_jerk);


    //input_path
    QVector<QPointF> input_pts;
//    int inputPtNum = 0 ;
    x_input_pts.clear();
    y_input_pts.clear();
    for(int i=0;i<point_num;i++)
    {
        QString p_name = "point" + QString::number(i);
        QWidget *p = ui->groupBox_2->findChild<QWidget *>(p_name);
        QList<QLineEdit *> items = p->findChildren<QLineEdit *>();
        if(!items[0]->text().isEmpty() && !items[1]->text().isEmpty())
        {
//            bezier_path[traj_Edit_idx].input_points[i].X =items[0]->text().toFloat();
//            bezier_path[traj_Edit_idx].input_points[i].Y =items[1]->text().toFloat();
//            bezier_path[traj_Edit_idx].input_num++;
//            inputPtNum++;
            x_input_pts.push_back(items[0]->text().toFloat());
            y_input_pts.push_back(items[1]->text().toFloat());
            input_pts.push_back(QPointF(items[0]->text().toFloat(),items[1]->text().toFloat()));
        }

    }

//    if (bezier_path[traj_Edit_idx].input_num == 0)
    if(input_pts.empty())
    {
        QMessageBox::warning(NULL, "过程点数量不能为0", "请输入正确的过程点", QMessageBox::Ok , QMessageBox::Ok);
        return;
    }

    input_ptsList=input_pts;
    Eigen::MatrixXd input_waypoints_mat(input_pts.size(), 3);

    for(int i=0 ;i<input_pts.size();i++)
    {
        QPointF pt = input_pts[i];

        input_waypoints_mat.row(i) <<  pt.x(),pt.y(),0 ;
    }

    traj_generator->trajGeneration(input_waypoints_mat);
    if ( !traj_generator->isHasTraj()){return;}
    // 采样
    int samplePtNum_btw_wayPt;
    samplePtNum_btw_wayPt = ui->Edit_num_btw_two->text().toInt();

    segment_num = traj_generator->getSegmentNum();
    double  traj_time_start = traj_generator->getTrajTimeStart()+0.01,
            traj_time_final = traj_generator->getTrajTimeFinal(),
            traj_time_now;
    traj_time_now = traj_time_start;


    x_inserted_pts.clear();
    y_inserted_pts.clear();
    trajPlotView->scene()->clear();
    plotKeyPt.clear();
    plotWayPt.clear();
    generated_ptsSegList.clear();
    generated_ptsNnum = 0 ;
    for(int i=0;i<segment_num;i++)
    {
        QVector<CtrlCmd_s> segTraj;
        double seg_time = traj_generator->getTrajSegmentTime(i);
        double time_interval = seg_time / (samplePtNum_btw_wayPt);
        double seg_time_start = traj_time_now;
        for(int j=0;j < samplePtNum_btw_wayPt;j++)
        {
            double t = seg_time_start + 1.0 * j * time_interval;
            auto traj_cmd = traj_generator->getCtrlCmd(t);
            Eigen::Vector2d pos_cmd,vel_cmd;
            pos_cmd = (traj_cmd.block(0,0,2,1));
            vel_cmd = (traj_cmd.block(0,1,2,1));
            double vel = vel_cmd.norm();
            double dir = std::acos( vel_cmd.dot(Eigen::Vector2d(1,0)) / ( vel_cmd.norm()*1.0 ) );
//            traj_pos.push_back(QPointF(pos_cmd(0),pos_cmd(1)));
//            traj_speed.push_back(vel);
//            traj_dir.push_back(dir);
//            traj_angle.push_back(0);

            segTraj.push_back(
                    {QPointF(pos_cmd(0),pos_cmd(1)),
                     QPointF(vel_cmd(0),vel_cmd(1)),
                     vel,dir,0.00,t}
                    );
            x_inserted_pts.push_back(pos_cmd(0));
            y_inserted_pts.push_back(pos_cmd(1));
            generated_ptsNnum++;

        }
        generated_ptsSegList.push_back(segTraj);
        traj_time_now +=seg_time;
    }
    //特殊处理最后和第一个点
    generated_ptsSegList[0][0].dir = 0.0000f;
    auto ptsSegListIter = generated_ptsSegList[segment_num-1].end() - 1 ;
    auto inputPtIter = input_ptsList.end() - 1;
    if( (ptsSegListIter->pos - (*inputPtIter) ).manhattanLength() > (1e-5) )
    {
        double t = traj_time_final-0.01;
        auto traj_cmd = traj_generator->getCtrlCmd(t);
        Eigen::Vector2d pos_cmd,vel_cmd;
        pos_cmd = (traj_cmd.block(0,0,2,1));
        vel_cmd = (traj_cmd.block(0,1,2,1));
        double vel = vel_cmd.norm();
        double dir = std::acos( vel_cmd.dot(Eigen::Vector2d(1,0)) / ( vel_cmd.norm()*1.0 ) );
        generated_ptsSegList[segment_num-1].push_back(
                {QPointF(pos_cmd(0),pos_cmd(1)),
                 QPointF(vel_cmd(0),vel_cmd(1)),
                 vel,dir,0.00,t}
        );
        x_inserted_pts.push_back(pos_cmd(0));
        y_inserted_pts.push_back(pos_cmd(1));
    }

    // 路径规划
    //        for(int i=0;i<bezier_path[traj_Edit_idx].input_num;i++)
    //        {
    //            bezier_path[traj_Edit_idx].input_points[i].X=bezier_path[traj_Edit_idx].input_points[i].X+ui->Edit_translate_dy->text().toFloat();
    //            bezier_path[traj_Edit_idx].input_points[i].Y=bezier_path[traj_Edit_idx].input_points[i].Y+ui->Edit_translate_dx->text().toFloat();
    //        }
//    bezier_path[traj_Edit_idx].out_num = (bezier_path[traj_Edit_idx].input_num - 1) * bezier_path[traj_Edit_idx].num_btw_two;
//
//    bezier_path[traj_Edit_idx].ctrlpoints_get();
//
//    bezier_path[traj_Edit_idx].outpoints_get();
//
//    bezier_path[traj_Edit_idx].calculate_length();
//
//    bezier_path[traj_Edit_idx].direct_planning();
//
//    bezier_path[traj_Edit_idx].angle_planning();
//
//    // 速度规划
//    if (bezier_path[traj_Edit_idx].input_num == 2)
//    {
//        bezier_path[traj_Edit_idx].strghtline_speed_plan();
//    }
//    else if (bezier_path[traj_Edit_idx].input_num > 2 && bezier_path[traj_Edit_idx].input_num < 7)
//    {
//        bezier_path[traj_Edit_idx].speed_planning();
//    }
//    else if (bezier_path[traj_Edit_idx].input_num == 7)
//    {
//        bezier_path[traj_Edit_idx].strghtline_speed_plan();
//    }

    /*输入点提醒*/
//    ui->plainTextEdit_input->clear();
//    QString inputPtInfo = "";
//    inputPtInfo=QString::asprintf("第%d条贝塞尔曲线\r\n", traj_Edit_idx);
//    ui->plainTextEdit_input->insertPlainText(inputPtInfo);
//    for (int i = 0; i < input_ptsList[traj_Edit_idx].size(); i++)
//    {
//        inputPtInfo=QString::asprintf(
//                "第%d个点,(%.3f,%.3f)\r\n",
//                i,input_ptsList[traj_Edit_idx][i].x(),
//                input_ptsList[traj_Edit_idx][i].y()
//                );
//        ui->plainTextEdit_input->insertPlainText(inputPtInfo);
//    }
//
//    /*输出点个数*/
//    ui->Edit_point_num->clear();
//    QString outputPtNum = "";
//    outputPtNum=QString::asprintf("%d", generated_ptsSegList[traj_Edit_idx].size());
//    ui->Edit_point_num->setText(outputPtNum);


    /*输出点提醒*/
    init_table_out();
    table_update();

//    x_all_pts.resize(bezier_path[traj_Edit_idx].out_num + 1);
//    y_all_pts.resize(bezier_path[traj_Edit_idx].out_num + 1);
//    x_inserted_pts.resize(bezier_path[traj_Edit_idx].out_num + 1 - bezier_path[traj_Edit_idx].input_num);
//    y_inserted_pts.resize(bezier_path[traj_Edit_idx].out_num + 1 - bezier_path[traj_Edit_idx].input_num);
//    x_input_pts.resize(bezier_path[traj_Edit_idx].input_num);
//    y_input_pts.resize(bezier_path[traj_Edit_idx].input_num);
//    int num = 0;
//    for (int j = 0; j <= bezier_path[traj_Edit_idx].out_num; j++)
//    {
//        if (j % bezier_path[traj_Edit_idx].num_btw_two == 0)
//        {
//            x_input_pts[num] = bezier_path[traj_Edit_idx].out_points[j].X;
//            y_input_pts[num] = bezier_path[traj_Edit_idx].out_points[j].Y;
//            num++;
//        }
//        else
//        {
//            x_inserted_pts[j - num] = bezier_path[traj_Edit_idx].out_points[j].X;
//            y_inserted_pts[j - num] = bezier_path[traj_Edit_idx].out_points[j].Y;
//        }
//        x_all_pts[j]=bezier_path[traj_Edit_idx].out_points[j].X;
//        y_all_pts[j]=bezier_path[traj_Edit_idx].out_points[j].Y;
//    }

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
        code=QString::asprintf("/*No.0 Bezier path has %d points in total.*/\r\n", generated_ptsNnum);
        ba.append(code);
        code.sprintf("const Points points_pos[%d]{\r\n", 0);
        ba.append(code);
        int pointCnt = 0;
        for (const auto& segment : generated_ptsSegList)
        {
            for(const auto& ctrlCmd : segment)
            {
                code.sprintf("{%.5f,\t%.5f,\t%.5f,\t%.5f,\t%.5f},",
                             ctrlCmd.pos.x(),ctrlCmd.pos.y(),
                             ctrlCmd.speed,ctrlCmd.dir,
                             ctrlCmd.angle);

                ba.append(code);
                code.sprintf("      /*point ranks %d*/", pointCnt++);
                code.append("\r\n");
                ba.append(code);
            }
        }
        code.sprintf("};\r\n");
        ba.append(code);

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
//    ui->plainTextEdit_input->clear();
//    ui->Edit_bezier_length->clear();
//    ui->Edit_point_num->clear();
    trajPlotView->scene()->clear();
    input_ptsList.clear();
    generated_ptsSegList.clear();
    plotWayPt.clear();
    plotKeyPt.clear();
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

//    ui->Edit_bezier_cnt->setText("0");

    traj_Edit_idx = 0;
    traj_num = 1;
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

//    trajPlotView->clear();
    map_width=ui->Edit_map_width->text().toFloat();
    map_height=ui->Edit_map_heigh->text().toFloat();
    map_width_pixel=img->width();
    map_height_pixel=img->height();
    res_w=trajPlotView->width();
    res_h=res_w*(map_height_pixel/map_width_pixel);
    trajPlotView->resize(res_w,res_h);
    trajPlotView->setFixedSize(res_w,res_h);
    trajPlotView->setSceneRect(0, 0, res_w, res_h);
    width_t=float(res_w)/map_width;
    height_t=res_h/map_height;
    *newImg=img->scaled(res_w,res_h);
    trajPlotView->setBackgroundBrush(QPixmap::fromImage(*newImg));
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
void PagePath::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    map_width=ui->Edit_map_width->text().toFloat();
    map_height=ui->Edit_map_heigh->text().toFloat();
    map_width_pixel=img->width();
    map_height_pixel=img->height();
    res_w=trajPlotView->width();
    res_h=res_w*(map_height_pixel/map_width_pixel);
    trajPlotView->resize(res_w,res_h);
    trajPlotView->setFixedSize(res_w,res_h);
    trajPlotView->setSceneRect(0, 0, res_w, res_h);
    width_t=float(res_w)/map_width;
    height_t=res_h/map_height;
    *newImg=img->scaled(res_w,res_h);
    trajPlotView->setBackgroundBrush(QPixmap::fromImage(*newImg));
}

