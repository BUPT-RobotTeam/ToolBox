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
#include <qmath.h>

double map_width = 0;
double map_height = 0;
double map_width_pixel = 0;
double map_height_pixel = 0;
double translate_dx = 0;
double translate_dy = 0;
double translate_dangle = 0;
int toggle_x = 1;
int toggle_y = 1;


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
//    get_coordTranslate();




    traj_generator.reset(new TimeOptimizerTraj( ui->Edit_max_speed->text().toDouble(),
                                                ui->Edit_max_acceleration->text().toDouble()));
    outputModel = new QStandardItemModel();
    inputModel = new QStandardItemModel();
    xDelegate = new SpinBoxDelegate(this,- 99 ,99 , 0.01   );
    yDelegate = new SpinBoxDelegate(this,- 99 ,99 , 0.01   );
    genNumDelegate = new SpinBoxDelegate(this,1 ,99 , 1,1,0);

    init_table_out();
    init_table_input();
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
    connect(ui->buttonGroup_outputMode, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),this,&PagePath::on_outputModeSelChanged);

}


PagePath::~PagePath()
{
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
    outputModel->clear();
//    outputModel->setRowCount(1);
    QStringList headerList;
    headerList << "Time"
               << "X"
               << "Y"
               << "Speed"
               << "Direct"
               << "Angle";
    outputModel->setHorizontalHeaderLabels(headerList);
    ui->table_out->setModel(outputModel);
    ui->table_out->setColumnWidth(0, 70); // 设置列的宽度
    ui->table_out->setColumnWidth(1, 70);
    ui->table_out->setColumnWidth(2, 70);
    ui->table_out->setColumnWidth(3, 70);
    ui->table_out->setColumnWidth(4, 70);
    ui->table_out->setColumnWidth(5, 70);

    ui->table_out->setSelectionMode(QTableView::SingleSelection);
    ui->table_out->setSelectionBehavior(QTableView::SelectRows );
    disconnect(outputModel,nullptr,this,nullptr);
    disconnect(ui->table_out,nullptr,this,nullptr);

    delete output_view_Menu;
    output_view_Menu = new QMenu(this);
    output_view_Menu->addAction("删除",this,[=]{
        int wayidx = ui->table_out->currentIndex().row();
        int keyidx = -1;
        auto waypt = plotWayPt[wayidx];
        keyidx = waypt->getKeyIndex();
        removePt(wayidx,keyidx);

    });
    connect(ui->table_out,&QTableView::customContextMenuRequested,this,&PagePath::on_table_output_CustomContextMenuRequested);

}

/**
 * @brief 初始化输入表
 *
 */
void PagePath::init_table_input()
{

    inputModel->clear();
//    outputModel->setRowCount(1);
    disconnect(inputModel,nullptr,this,nullptr);
    disconnect(ui->table_input,nullptr,this,nullptr);

    QStringList headerList;
    headerList << "X"
               << "Y"
//               << "Speed"
//               << "Direct"
//               << "Angle"
               << "生成点数量";
    inputModel->setHorizontalHeaderLabels(headerList);
    ui->table_input->setModel(inputModel);
    ui->table_input->setColumnWidth(0, 80); // 设置列的宽度
    ui->table_input->setColumnWidth(1, 80); // 设置列的宽度
    ui->table_input->setColumnWidth(2, 150); // 设置列的宽度

    ui->table_input->setItemDelegateForColumn(0,xDelegate);
    ui->table_input->setItemDelegateForColumn(1,yDelegate);
    ui->table_input->setItemDelegateForColumn(2,genNumDelegate);

    ui->table_input->setSelectionMode(QTableView::SingleSelection);
    ui->table_input->setSelectionBehavior(QTableView::SelectRows);

    //删除菜单,初始化并连接信号
    delete input_view_Menu;
    input_view_Menu = new QMenu(this);
    input_view_Menu->addAction("删除",this,[=]{
        int keyidx = ui->table_input->currentIndex().row();
        int wayidx = -1;
        if (!plotWayPt.isEmpty())
        {
            auto keypt = plotKeyPt[keyidx];
            wayidx = keypt->getPointIndex();
        }
        removePt(wayidx,keyidx);

    });
    connect(inputModel,&QStandardItemModel::itemChanged,this,&PagePath::inputModelChanged);
    connect(ui->table_input,&QTableView::customContextMenuRequested,this,&PagePath::on_table_input_CustomContextMenuRequested);

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
            aItem->setEditable(false);
            rowList.push_back(aItem);

            QString x = QString::asprintf("%.3f", ctrlCmd.pos.x());
            aItem = new QStandardItem(x);
            aItem->setTextAlignment(Qt::AlignHCenter);
            aItem->setEditable(false);
            rowList.push_back(aItem);

            QString y = QString::asprintf("%.3f", ctrlCmd.pos.y());
            aItem = new QStandardItem(y);
            aItem->setTextAlignment(Qt::AlignHCenter);
            aItem->setEditable(false);
            rowList.push_back(aItem);

            QString speed = QString::asprintf("%.3f", ctrlCmd.speed);
            aItem = new QStandardItem(speed);
            aItem->setTextAlignment(Qt::AlignHCenter);
            aItem->setEditable(false);
            rowList.push_back(aItem);

            QString direct = QString::asprintf("%.3f", ctrlCmd.dir);
            aItem = new QStandardItem(direct);
            aItem->setTextAlignment(Qt::AlignHCenter);
            aItem->setEditable(false);
            rowList.push_back(aItem);

            QString angle = QString::asprintf("%.3f",ctrlCmd.angle);
            aItem = new QStandardItem(angle);
            aItem->setTextAlignment(Qt::AlignHCenter);
            aItem->setEditable(false);
            rowList.push_back(aItem);

            outputModel->appendRow(rowList);
            rowcnt++;
        }

    }

    ui->table_out->setModel(outputModel);
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
 * @brief 旋转坐标系正向换算函数
 * @param x 坐标点
 * @param y 坐标点
 * @param dangle 旋转，正运算设置为translate_dangle
 * @param dx 正运算设置为translate_dx
 * @param dy 正运算设置为translate_dy
 * @param toggle_x toggle_x
 * @param toggle_y toggle_y
 * @param w 正运算设置为width_t
 * @param h 正运算设置为height_t
 * @return 换算后的点
 * @warning 逆运算似乎不同构，还是用 ret_rotate_point 函数吧
 */
QPointF cal_rotate_point(double x,double y,double dangle,double dx,double dy,int toggle_x,int toggle_y,double w,double h)
{
    if(std::abs(dangle)<1e-5)
    {
        return {(dx+toggle_x*x)*w,(dy+toggle_y*y)*h};
    }
    else
    {
        double x_val=x*cos(dangle * M_PI / 180.0) - y*sin(dangle * M_PI / 180.0);
        double y_val=y*cos(dangle * M_PI / 180.0) + x*sin(dangle * M_PI / 180.0);
        return  {(dx+toggle_x*x_val)*w, (dy+toggle_y*y_val)*h};
    }
}

/**
 * @brief 旋转坐标系反向换算函数
 * @param x 坐标点
 * @param y 坐标点
 * @param dangle 旋转，设置为translate_dangle
 * @param dx 设置为translate_dx
 * @param dy 设置为translate_dy
 * @param toggle_x toggle_x
 * @param toggle_y toggle_y
 * @param w 设置为width_t
 * @param h 设置为height_t
 * @return 换算后的点
 * @return
 */
QPointF ret_rotate_point(double x,double y,double dangle,double dx,double dy,int toggle_x,int toggle_y,double w,double h)
{
    if(std::abs(dangle)<1e-5)
    {
        return {(x/w-dx)/toggle_x,(y/h-dy)/toggle_y};
    }
//    if(translate_dangle==0)
//    {
//        return QPointF((x/width_t-translate_dy)/toggle_x,(y/height_t-translate_dx)/toggle_y);
//    }

    double x_val=(x/w-dx)/toggle_x;
    double y_val=(y/h-dy)/toggle_y;
    return {x_val*cos(-dangle * M_PI / 180.0) - y_val*sin(-dangle * M_PI / 180.0),
            y_val*cos(-dangle * M_PI / 180.0) + x_val*sin(-dangle * M_PI / 180.0)};

}
/**
 * 清空之前打印的点，但不清空关键点。
 * 获取坐标变换并重新绘制坐标轴\n
 * 之后遍历每段轨迹，更新关键点坐标，绘制路径点
 * （最后一个点是特殊处理的。）\n
 * 同时还会修改plotWayPt,plotKeyPt
 */
void PagePath::plotTrajectory()
{
    if(buttonLoadPathClickedNum!=0)
    {
        buttonLoadPathClickedNum=0;
//        return;
    }
    buttonLoadPathClickedNum++;
//    trajPlotView->scene()->clear();
    clear_axis();
    clearWayPt();
    plotWayPt.clear();
    get_coordTranslate();

    draw_axis();


    // 绘制点
    int ptCnt=0,segCnt=0;
    for(const auto& segment : generated_ptsSegList)
    {
        WayPtGraphicsItem* pointItem;

        pointItem = plotKeyPt[segCnt];
        pointItem->setKeyIndex(segCnt);
        pointItem->setPointIndex(ptCnt);
        auto plotPoint = cal_rotate_point(segment[0].pos.x(), segment[0].pos.y(),
                                     translate_dangle,
                                     translate_dx, translate_dy,
                                     toggle_x, toggle_y,
                                     width_t, height_t);
        pointItem->setPos(plotPoint);
        plotWayPt.push_back(pointItem);

        ptCnt++;

        for(auto ptIter=segment.begin()+1;ptIter!=segment.end();ptIter++)
        {
            if (ptCnt + 1 == generated_ptsNnum)
            {
                break;
            }
            pointItem= new WayPtGraphicsItem(WayPtGraphicsItem::WAY_POINT);

            plotWayPt.push_back(pointItem);
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
            connect(pointItem,&WayPtGraphicsItem::pointSelected,this, &PagePath::scenePointSelected);
            connect(pointItem,&WayPtGraphicsItem::pointPosChanged,this, &PagePath::scenePointPosChanged);
            connect(pointItem,&WayPtGraphicsItem::deletePointItem,this, &PagePath::scenePointDeleted);

            ptCnt++;
        }
        segCnt++;
//        plotPoint.setY(cal_rotate_point(bezier_path[bezier_cnt].out_points[i].X, bezier_path[bezier_cnt].out_points[i].Y).y());

    }

    WayPtGraphicsItem* pointItem;

    pointItem = plotKeyPt[segCnt];
    pointItem->setKeyIndex(segCnt);
    pointItem->setPointIndex(ptCnt);
    auto ptIter = ( (generated_ptsSegList.end()-1)->end() ) - 1;
    auto plotPoint = cal_rotate_point((ptIter)->pos.x(), ptIter->pos.y(),
                                      translate_dangle,
                                      translate_dx, translate_dy,
                                      toggle_x, toggle_y,
                                      width_t, height_t);
    pointItem->setPos(plotPoint);
    plotWayPt.push_back(pointItem);

    trajPlotView->show();


}

void PagePath::get_coordTranslate() const {
    translate_dangle = ui->Edit_translate_dangle->text().toDouble();
    translate_dx= ui->Edit_translate_dx->text().toDouble();
    translate_dy= ui->Edit_translate_dy->text().toDouble();
    toggle_x= ui->Edit_x_toggle->text().toInt();
    toggle_y= ui->Edit_y_toggle->text().toInt();

    map_width= ui->Edit_map_width->text().toFloat();
    map_height= ui->Edit_map_heigh->text().toFloat();

    map_width_pixel=img->width();
    map_height_pixel=img->height();
    res_w=trajPlotView->width();
    res_h=res_w*(map_height_pixel/map_width_pixel);

    width_t=float(res_w)/map_width;
    height_t=res_h/map_height;

}
/**
 *
 */
void PagePath::clear_axis()
{
    trajPlotView->scene()->removeItem(xAxisArrowItem);
    trajPlotView->scene()->removeItem(yAxisArrowItem);

    trajPlotView->scene()->removeItem(xAxisPathItem);
    trajPlotView->scene()->removeItem(yAxisPathItem);

    trajPlotView->scene()->removeItem(xAxisLineItem);
    trajPlotView->scene()->removeItem(yAxisLineItem);

}
/**
 * 注意需要在类中存储相关item的指针以便删除
 */
void PagePath::draw_axis() {// 绘制坐标系


    // 绘制箭头
    QVector<QPointF> xAxisArrowheadPolygon{3}, yAxisArrowheadPolygon{3};

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
    QPolygonF xAxisArrowhead(xAxisArrowheadPolygon),yAxisArrowhead(yAxisArrowheadPolygon);

    xAxisArrowItem = trajPlotView->TrajectoryPlotGraphicsScene->addPolygon(xAxisArrowhead,
                                                          QPen(QBrush(Qt::blue), 1),
                                                          QBrush(Qt::blue)
                                                          );
    yAxisArrowItem = trajPlotView->TrajectoryPlotGraphicsScene->addPolygon(yAxisArrowhead,
                                                          QPen(QBrush(Qt::blue), 1),
                                                          QBrush(Qt::blue)
                                                          );

    // 绘制坐标轴标签

    QPainterPath xAxis,yAxis;
    QFont axisFont;
    axisFont.setPixelSize(16);
    axisFont.setBold(false);
    xAxis.addText(cal_rotate_point(2.5, 0, translate_dangle,
                                   translate_dx, translate_dy,
                                   toggle_x, toggle_y,
                                   width_t, height_t), axisFont, "X");
    yAxis.addText(cal_rotate_point(0, 2.5, translate_dangle,
                                   translate_dx, translate_dy,
                                   toggle_x, toggle_y,
                                   width_t, height_t), axisFont, "Y");
    xAxisPathItem = trajPlotView->TrajectoryPlotGraphicsScene->addPath(xAxis,
                                                       QPen(QBrush(Qt::blue), 1),
                                                       QBrush(Qt::blue)
                                                       );

    yAxisPathItem = trajPlotView->TrajectoryPlotGraphicsScene->addPath(yAxis,
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
    xAxisLineItem = trajPlotView->TrajectoryPlotGraphicsScene->addLine({originPt, xaxisPt}, QPen(QBrush(Qt::blue), 3));
    yAxisLineItem = trajPlotView->TrajectoryPlotGraphicsScene->addLine({originPt, yaxisPt}, QPen(QBrush(Qt::blue), 3));
}


/**
 * @details 首先清零以前的轨迹生成缓存\n
 * 之后从输入框后获取运动学参数，并赋值给轨迹参数器。\n
 * 从表格中获取输入点，注意判断输入框合法性。
 * 少于两个点不能去生成轨迹，轨迹生成器会出现数值错误。
 * 有两个点在同一位置也会导致错误\n
 * 之后用eigen矩阵存储输入点，解出轨迹后采样。
 * 采样按照等时间采样。存储是按照轨迹段分段存储。特殊处理第一个点的dir为0，以及最后一个点也要存储在内（按照等时采样刚好最后一个点不会被采样到）。\n
 * 输出点到表格中，进行一次点可视化。
 * @todo 属于生成器的要求，应该在轨迹生成器里判断而不是在此处判断
 */
void PagePath::on_Button_create_path_clicked()
{
    buttonLoadPathClickedNum=0;//这个变量暂时没有用了
    clear_trajectory();
    // 获取坐标系旋转角度


    //运动学参数获取
    double max_v,max_acc,max_jerk,target_angle;
    max_v = ui->Edit_max_speed->text().toDouble();
    max_acc = ui->Edit_max_acceleration->text().toDouble();
    max_jerk = ui->Edit_max_jerk->text().toDouble();

    traj_generator->setMaxVel(max_v);
    traj_generator->setMaxAcc(max_acc);
    traj_generator->setMaxDAcc(max_jerk);
    dynamic_cast<TimeOptimizerTraj*>(traj_generator.get())->setDS(ui->Sample_interval->text().toDouble());

    //input_path
    QVector<QPointF> input_pts;
//    int inputPtNum = 0 ;

    for(int i=0; i < inputPoint_num; i++)
    {
        auto inputXIdx = inputModel->index(i,0);
        auto inputYIdx = inputModel->index(i,1);

        auto xData=inputModel->data(inputXIdx);
        auto yData=inputModel->data(inputYIdx);
        if(xData.canConvert<double>() && yData.canConvert<double>() )
        {
            input_pts.push_back(QPointF(xData.toDouble(),yData.toDouble()));
        }
        else
        {
            QMessageBox::warning(nullptr, "请输入正确的关键点", "关键点输入非法类型", QMessageBox::Ok , QMessageBox::Ok);
            return;
        }

    }


    if(input_pts.size() < 2)
    {
        QMessageBox::warning(nullptr, "请输入正确的关键点", "关键点数量不能小于2", QMessageBox::Ok , QMessageBox::Ok);
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

//    samplePtNum_btw_wayPt = ui->Edit_num_btw_two->text().toInt();

    segment_num = traj_generator->getSegmentNum();
    double  traj_time_start = traj_generator->getTrajTimeStart()+0.01,
            traj_time_final = traj_generator->getTrajTimeFinal(),
            traj_time_now;
    traj_time_now = traj_time_start;

    switch (sampleMode)
    {
        case POINT_NUM:
        {
            QVector<int> samplePtNum_btw_wayPt;
            for(int i=0;i<segment_num;i++) {
                auto inputNumIdx = inputModel->index(i,2);
                auto numData=inputModel->data(inputNumIdx);
                if ( !(numData.canConvert<int>()) )
                {
                    QMessageBox::warning(nullptr, "ToolBox", "输入的关键点间隔数非法！", QMessageBox::Ok , QMessageBox::Ok);
                    return;
                }
                samplePtNum_btw_wayPt.push_back(numData.toInt());
            }
            sampleTrajByPtNum(traj_time_final, traj_time_now, samplePtNum_btw_wayPt);
            break;
        }
        case TIMEINTERVAL:
        {
            double time_interval = ui->Edit_sampleTime->value();
            if(static_cast<int>((traj_time_final-traj_time_start)/time_interval) < inputPoint_num )
            {
                QMessageBox::warning(nullptr, "ToolBox", "时间间隔过大导致关键点丢失，请设置一个更小的时间间隔", QMessageBox::Ok , QMessageBox::Ok);
                return;
            }

            sampleTrajByTime(traj_time_now, time_interval);
            break;
        }
        default:
            break;
    }


    /*输出点提醒*/
    init_table_out();
    table_update();
    plotTrajectory();

}

void PagePath::sampleTrajByTime(double traj_time_now, double time_interval) {
    for(int i=0; i < segment_num; i++)
    {
        QVector<CtrlCmd_s> segTraj;
        double seg_time = traj_generator->getTrajSegmentTime(i);
        double seg_time_final = traj_time_now + seg_time;
        while(traj_time_now<seg_time_final)
        {
            auto traj_cmd = traj_generator->getCtrlCmd(traj_time_now);
            Vector2d pos_cmd,vel_cmd;
            pos_cmd = (traj_cmd.block(0,0,2,1));
            vel_cmd = (traj_cmd.block(0,1,2,1));
            double vel = vel_cmd.norm();
            double dir = acos(vel_cmd.dot(Vector2d(1, 0)) / (vel_cmd.norm() * 1.0 ) );
//            traj_pos.push_back(QPointF(pos_cmd(0),pos_cmd(1)));
//            traj_speed.push_back(vel);
//            traj_dir.push_back(dir);
//            traj_angle.push_back(0);

            segTraj.push_back(
                    {QPointF(pos_cmd(0),pos_cmd(1)),
                     QPointF(vel_cmd(0),vel_cmd(1)),
                     vel,dir,0.00,traj_time_now}
            );

            generated_ptsNnum++;

            traj_time_now+=time_interval;
        }
        generated_ptsSegList.push_back(segTraj);

    }
}

void PagePath::sampleTrajByPtNum(double traj_time_final, double traj_time_now, const QVector<int> &samplePtNum_btw_wayPt) {
    for(int i=0; i < segment_num; i++)
    {
        QVector<CtrlCmd_s> segTraj;

        int samplePtNum;
        samplePtNum = samplePtNum_btw_wayPt[i];
        double seg_time = traj_generator->getTrajSegmentTime(i);
        double time_interval = seg_time / (samplePtNum);
        double seg_time_start = traj_time_now;
        for(int j=0;j < samplePtNum;j++)
        {
            double t = seg_time_start + 1.0 * j * time_interval;
            auto traj_cmd = traj_generator->getCtrlCmd(t);
            Vector2d pos_cmd,vel_cmd;
            pos_cmd = (traj_cmd.block(0,0,2,1));
            vel_cmd = (traj_cmd.block(0,1,2,1));
            double vel = vel_cmd.norm();
            double dir = acos(vel_cmd.dot(Vector2d(1, 0)) / (vel_cmd.norm() * 1.0 ) );
//            traj_pos.push_back(QPointF(pos_cmd(0),pos_cmd(1)));
//            traj_speed.push_back(vel);
//            traj_dir.push_back(dir);
//            traj_angle.push_back(0);

            segTraj.push_back(
                    {QPointF(pos_cmd(0),pos_cmd(1)),
                     QPointF(vel_cmd(0),vel_cmd(1)),
                     vel,dir,0.00,t}
                    );

            generated_ptsNnum++;

        }
        generated_ptsSegList.push_back(segTraj);
        traj_time_now +=seg_time;
    }
    //特殊处理最后和第一个点
    generated_ptsSegList[0][0].dir = 0.0000f;
    auto ptsSegListIter = generated_ptsSegList[segment_num - 1].end() - 1 ;
    auto inputPtIter = input_ptsList.end() - 1;
    if( (ptsSegListIter->pos - (*inputPtIter) ).manhattanLength() > (1e-5) )
    {
        double t = traj_time_final-0.01;
        auto traj_cmd = traj_generator->getCtrlCmd(t);
        Vector2d pos_cmd,vel_cmd;
        pos_cmd = (traj_cmd.block(0,0,2,1));
        vel_cmd = (traj_cmd.block(0,1,2,1));
        double vel = vel_cmd.norm();
        double dir = acos(vel_cmd.dot(Vector2d(1, 0)) / (vel_cmd.norm() * 1.0 ) );
        generated_ptsSegList[segment_num - 1].push_back(
                {QPointF(pos_cmd(0),pos_cmd(1)),
                 QPointF(vel_cmd(0),vel_cmd(1)),
                 vel,dir,0.00,t}
        );
        generated_ptsNnum++;

    }
}


/**
 * @brief 点击“生成文件”按钮
 * @details 从表格中读取数据，之后写入文件
 */
void PagePath::on_Button_create_file_clicked()
{
    if (ui->Edit_file_location->text().isEmpty())
    {
        QMessageBox::warning(nullptr, "无路径", "请输入生成文件路径", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
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

        for(int i=0;i<generated_ptsNnum;i++)
        {
            auto outputTimeIdx = outputModel->index(i,0);
            auto outputXIdx = outputModel->index(i,1);
            auto outputYIdx = outputModel->index(i,2);
            auto outputSpeedIdx = outputModel->index(i,3);
            auto outputDirIdx = outputModel->index(i,4);
            auto outputAngleIdx = outputModel->index(i,5);

            auto timeData=outputModel->data(outputTimeIdx);
            auto xData=outputModel->data(outputXIdx);
            auto yData=outputModel->data(outputYIdx);
            auto speedData=outputModel->data(outputSpeedIdx);
            auto dirData=outputModel->data(outputDirIdx);
            auto angleData=outputModel->data(outputAngleIdx);
            code.sprintf("{%.5f,\t%.5f,\t%.5f,\t%.5f,\t%.5f},",
                         xData.toDouble(), yData.toDouble(),
                         speedData.toDouble(), dirData.toDouble(),
                         angleData.toDouble());

            ba.append(code);
            code.sprintf("      /*point ranks %d*/", pointCnt++);
            code.append("\r\n");
            ba.append(code);
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
 * @details 清空两个表格。
 * 清空scene和存储点指针数组\n
 * 清空轨迹生成器\n
 * 重新绘制scene的坐标轴。
 * @bug 好像清空表格和坐标系变换一起操作会有问题
 */
void PagePath::on_Button_clear_clicked()
{
    init_table_out();
    init_table_input();
//    ui->plainTextEdit_input->clear();
//    ui->Edit_bezier_length->clear();
//    ui->Edit_point_num->clear();

    trajPlotView->scene()->clear();
    plotWayPt.clear();
    plotKeyPt.clear();
    inputPoint_num =0;

    //清零轨迹生成器时要全部清空
    clear_trajectory();

    get_coordTranslate();
    draw_axis();
    addKeypt();
    addKeypt();
    trajPlotView->show();

//    ui->Edit_bezier_cnt->setText("0");

}
/**
 * @details 清空轨迹点元数据，包括输入点、分段存储的输出点数组。
 */
void PagePath::clear_trajectory() {
    generated_ptsNnum =0;
    segment_num =0;
    generated_ptsSegList.clear();
    input_ptsList.clear();

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
        QMessageBox::information(nullptr, "error", "No Directory",
                                 QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
}


/**
 * @brief 点击“选择图片”图标
 * @details 同时会计算小车坐标和scene坐标的变换关系。
 */
void PagePath::on_Button_load_img_clicked()
{
    QString tempFilename = QFileDialog::getOpenFileName(this,
                                                        "Choose picture", "/",
                                                        "Image Files(*.jpg *.png *.bmp *.jpeg *.gif *.tga)");
    if (tempFilename.isEmpty())
    {
//        ui->Edit_file_location->setText(tempFilename);
        QMessageBox::information(nullptr, "error", "No such file",
                                 QMessageBox::Yes, QMessageBox::Yes);
        return;
    }

    ui->Edit_img_location->setText(tempFilename);
    img->load(tempFilename);

//    trajPlotView->clear();
    get_coordTranslate();
    trajPlotView->resize(res_w,res_h);
    trajPlotView->setFixedSize(res_w,res_h);
    trajPlotView->setSceneRect(0, 0, res_w, res_h);
    *newImg=img->scaled(res_w,res_h);
    trajPlotView->setBackgroundBrush(QPixmap::fromImage(*newImg));
}

/**
 * @brief  添加关键点
 * @details 添加上一行最后一列的单元格。\n
 * 添加一行坐标编辑单元格\n
 * 在场景中添加关键点，初始坐标(1,1)。并将点的WayPtGraphicsItem指针加入plotKeyPt中。\n
 * 连接信号。
 */
void PagePath::addKeypt() {

    //在列表中添加spinbox便于编辑
    if (inputPoint_num > 0) {
        auto lastRowNumItem = new QStandardItem(QString::asprintf("%d", 6));
        lastRowNumItem->setTextAlignment(Qt::AlignHCenter);
//    rowList.push_back(aItem);
        inputModel->setItem(inputPoint_num - 1, 2, lastRowNumItem);
        //特殊处理最后一段的点
    }
    QList<QStandardItem*> rowList;

    auto xItem = new QStandardItem(QString::asprintf("%d", 1));
    xItem->setTextAlignment(Qt::AlignHCenter);
    auto yItem = new QStandardItem(QString::asprintf("%d", 1));
    yItem->setTextAlignment(Qt::AlignHCenter);
    auto rowNumItem = new QStandardItem();
    rowNumItem->setTextAlignment(Qt::AlignHCenter);
    rowNumItem->setEditable(false);
    rowList.push_back(xItem);
    rowList.push_back(yItem);
    rowList.push_back(rowNumItem);


    inputModel->appendRow(rowList);

    //在场景中添加关键点

    auto pointItem =  new WayPtGraphicsItem(WayPtGraphicsItem::KEY_POINT);

    pointItem->setKeyIndex(inputPoint_num);
    auto plotPoint = cal_rotate_point(1, 1,
                                 translate_dangle,
                                 translate_dx, translate_dy,
                                 toggle_x, toggle_y,
                                 width_t, height_t);
    pointItem->setRect(0,0,4,4);
    pointItem->setPos(plotPoint);
    /**
     * 会添加以下信号@code{.cpp}
     * connect(pointItem,&WayPtGraphicsItem::pointSelected,this, &PagePath::scenePointSelected);
     * connect(pointItem,&WayPtGraphicsItem::pointPosChanged,this, &PagePath::scenePointPosChanged);
     * connect(pointItem,&WayPtGraphicsItem::deletePointItem,this, &PagePath::scenePointDeleted);
     * @endcode
     */ ///////
    connect(pointItem,&WayPtGraphicsItem::pointSelected,this, &PagePath::scenePointSelected);
    connect(pointItem,&WayPtGraphicsItem::pointPosChanged,this, &PagePath::scenePointPosChanged);
    connect(pointItem,&WayPtGraphicsItem::deletePointItem,this, &PagePath::scenePointDeleted);

    plotKeyPt.push_back(pointItem);

    trajPlotView->scene()->addItem(pointItem);
    inputPoint_num++;
}
/**
 * @brief 点击“加点”按钮
 * @details 调用  PagePath::addKeypt();
 */
void PagePath::on_Button_add_point_clicked()
{
    addKeypt();
}


/**
 * @brief PagePath::on_Button_delete_point_clicked  点击删点按钮
 * 不允许删除关键点到两个点以下
 */
void PagePath::on_Button_delete_point_clicked()
{
    if (inputPoint_num > 2 )
    {
        removePt(plotKeyPt[inputPoint_num-1]->getPointIndex(),inputPoint_num-1);
    }
}

/**
 *
 * @brief 窗口显示事件
 * @details 为了准确获取trajPlotView的大小，正确resize trajPlotView的大小。
 * 所以需要在此事件中调用 plotScene_init();
 * @param event
 */
void PagePath::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    plotScene_init();
}
/**
 * 获取场景的坐标变换，之后设置背景图
 * @note 如果想使用qt原生的graphicsView坐标变换。需要注意不能使用背景笔刷或者不要，
 * 否则会出现背景图平铺。如果想利用qt原生坐标变换，可能得给scene画上背景比如坐标轴什么的，转scene不转view。
 */
void PagePath::plotScene_init() {//设置图片背景
    get_coordTranslate();
    trajPlotView->resize(res_w, res_h);
    trajPlotView->setFixedSize(res_w, res_h);
    trajPlotView->setSceneRect(0, 0, res_w, res_h);


    *newImg = img->scaled(res_w, res_h);
    trajPlotView->setBackgroundBrush(QPixmap::fromImage(*newImg));

    //绘制坐标轴
    draw_axis();
    addKeypt();
    addKeypt();
    trajPlotView->show();
}

void PagePath::scenePointSelected(int idx,int keyIdx) {


    WayPtGraphicsItem * selPoint = nullptr;
    if(keyIdx>=0)
    {
        selPoint= plotKeyPt[keyIdx];
    }
    else
    {
        selPoint= plotWayPt[idx];
    }

    auto retPt = ret_rotate_point(
            selPoint->scenePos().x(),selPoint->scenePos().y(),
            translate_dangle,
            translate_dx, translate_dy,
            toggle_x, toggle_y,
            width_t, height_t
    );
    auto nowPointValue=QString::asprintf("第%d个点,第%d个关键点\tx: %.3f,y: %.3f",idx,keyIdx,retPt.x(),retPt.y());

    ui->nowPoint->setText(nowPointValue);
    ui->nowPoint->update();
}

void PagePath::scenePointReleased(int idx,int keyIdx) {
}

void PagePath::scenePointDeleted(int idx,int keyIdx) {
    removePt(idx,keyIdx);
}

void PagePath::scenePointPosChanged(int idx, QPointF nowPos, int keyIdx) {
    WayPtGraphicsItem * selPoint = nullptr;
    if(keyIdx>=0)
    {
        selPoint= plotKeyPt[keyIdx];
    }
    else
    {
        selPoint= plotWayPt[idx];
    }

    auto retPt = ret_rotate_point(
            selPoint->scenePos().x(),selPoint->scenePos().y(),
            translate_dangle,
            translate_dx, translate_dy,
            toggle_x, toggle_y,
            width_t, height_t
    );
    auto nowPointValue=QString::asprintf("第%d个点,第%d个关键点\tx: %.3f,y: %.3f",idx,keyIdx,retPt.x(),retPt.y());
    if (keyIdx >= 0)
    {
        auto modelXIdx = inputModel->index(keyIdx,0);
        auto modelYIdx = inputModel->index(keyIdx,1);
        inputModel->setData(modelXIdx,retPt.x());
        inputModel->setData(modelYIdx,retPt.y());
    }
    ui->nowPoint->setText(nowPointValue);
    ui->nowPoint->update();
}
/**
 * 利用对象的WayPtGraphicsItem::getPointType()判断点类型\n
 * 使用QObject::deleteLater()可以让对象完成事件后销毁
 * 注意调用此函数仅限于可视化点时使用，用于清空场景且不让关键点对象被销毁。
 */
void PagePath::clearWayPt() {
    for(auto x :plotWayPt)
    {
        if(x->getPointType() == WayPtGraphicsItem::WAY_POINT)
        {
            trajPlotView->scene()->removeItem(x);
            x->deleteLater();
        }
    }
}

void PagePath::inputModelChanged(QStandardItem *item) {
    int rowNum = item->row();

    auto inputXIdx = inputModel->index(rowNum,0);
    auto inputYIdx = inputModel->index(rowNum,1);
    auto xData=inputModel->data(inputXIdx);
    auto yData=inputModel->data(inputYIdx);

    if(xData.canConvert<double>() && yData.canConvert<double>() )
    {
        auto plotPoint = cal_rotate_point(xData.toDouble(), yData.toDouble(),
                                          translate_dangle,
                                          translate_dx, translate_dy,
                                          toggle_x, toggle_y,
                                          width_t, height_t);
        auto plotPointitem = plotKeyPt[rowNum];
        plotPointitem->setPos(plotPoint);
    }
}
/**
 * @brief 输出表格右键菜单
 * 加5个偏移防止鼠标连击
 * @param pos
 */
void PagePath::on_table_output_CustomContextMenuRequested(QPoint pos)
{
    output_view_Menu->exec(QCursor::pos()+QPoint{5,5});
}
/**
 * @brief 输入表格右键菜单
 * 加5个偏移防止鼠标连击
 * @param pos
 */
void PagePath::on_table_input_CustomContextMenuRequested(QPoint pos)
{
    input_view_Menu->exec(QCursor::pos()+QPoint{5,5});
}
/**
 * 删除点。分别根据wayidx，keyidx是否大于等于0来决定是否删除\n
 * 如果不能将关键点删除到少于两个，函数会直接返回
 * 删除点时同时会删除：场景项目、数组内容、表格内容。\n
 * 并使用QObject::deleteLater()可以让对象完成事件后销毁
 */
void PagePath::removePt(int wayidx, int keyidx) {

    if (keyidx >= 0  )
    {
        if(inputPoint_num <= 2)
        {
            return;//不能删除要直接返回，否则会作为路径点被删除
        }
        auto keypt = plotKeyPt[keyidx];
        trajPlotView->scene()->removeItem(keypt);
        keypt->deleteLater();
        plotKeyPt.removeAt(keyidx);
        inputModel->removeRow(keyidx);
        inputPoint_num--;
    }
    if ( wayidx>= 0 )
    {
        auto waypt = plotWayPt[wayidx];
        if (keyidx < 0  )
        {
            trajPlotView->scene()->removeItem(waypt);
            //避免重复从场景中移除
        }
        plotWayPt.removeAt(wayidx);
        outputModel->removeRow(wayidx);
        waypt->deleteLater();
        generated_ptsNnum--;
    }

    updatePlotIdx();
}
/**
 * 遍历数组更新关键点和路径点下标
 */
void PagePath::updatePlotIdx() {
    int keycnt=0;
    for (auto keyptItem : plotKeyPt){
        keyptItem->setKeyIndex(keycnt);
        keycnt++;
    }
    int waycnt=0;
    for (auto wayptItem : plotWayPt) {
        wayptItem->setPointIndex(waycnt);
        waycnt++;
    }
}

void PagePath::on_outputModeSelChanged(QAbstractButton *button) {
    if (button == ui->radioButton_PointNumMode)
    {
        ui->Edit_sampleTime->setReadOnly(true);
        sampleMode = POINT_NUM;
//            break;
    }
    else if( button == ui->radioButton_TimeIntervalMode )
    {
        ui->Edit_sampleTime->setReadOnly(false);
        sampleMode = TIMEINTERVAL;
    }

}


