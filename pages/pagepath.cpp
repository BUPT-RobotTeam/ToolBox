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
    map_width=ui->Edit_map_width->text().toFloat();
    map_height=ui->Edit_map_heigh->text().toFloat();



    traj_generator.reset(new TimeOptimizerTraj( ui->Edit_max_speed->text().toDouble(),
                                                ui->Edit_max_acceleration->text().toDouble()));
    outputModel = new QStandardItemModel();
    inputModel = new QStandardItemModel();
    xDelegate = new SpinBoxDelegate(this,- map_width ,map_width , 0.01   );
    yDelegate = new SpinBoxDelegate(this,- map_height ,map_height , 0.01   );
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

    //删除菜单初始化并连接信号
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
    translate_dx=ui->Edit_translate_dx->text().toDouble();
    translate_dy=ui->Edit_translate_dy->text().toDouble();
    toggle_x=ui->Edit_x_toggle->text().toInt();
    toggle_y=ui->Edit_y_toggle->text().toInt();

    map_width=ui->Edit_map_width->text().toFloat();
    map_height=ui->Edit_map_heigh->text().toFloat();
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
void PagePath::clear_axis()
{
    trajPlotView->scene()->removeItem(xAxisArrowItem);
    trajPlotView->scene()->removeItem(yAxisArrowItem);

    trajPlotView->scene()->removeItem(xAxisPathItem);
    trajPlotView->scene()->removeItem(yAxisPathItem);

    trajPlotView->scene()->removeItem(xAxisLineItem);
    trajPlotView->scene()->removeItem(yAxisLineItem);

}
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
 * @brief 点击“确定”按钮，开始规划轨迹
 *
 */
void PagePath::on_Button_create_path_clicked()
{
    buttonLoadPathClickedNum=0;
    // 获取坐标系旋转角度
    translate_dangle = ui->Edit_translate_dangle->text().toDouble();

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

    for(int i=0; i < inputPoint_num; i++)
    {
        auto inputXIdx = inputModel->index(i,0);
        auto inputYIdx = inputModel->index(i,1);
        auto inputNumIdx = inputModel->index(i,2);

        auto xData=inputModel->data(inputXIdx);
        auto yData=inputModel->data(inputYIdx);
        auto numData=inputModel->data(inputNumIdx);
        if(xData.canConvert<double>() && yData.canConvert<double>() && (i==inputPoint_num-1 ||numData.canConvert<int>()))
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
    int samplePtNum_btw_wayPt;
    samplePtNum_btw_wayPt = ui->Edit_num_btw_two->text().toInt();

    segment_num = traj_generator->getSegmentNum();
    double  traj_time_start = traj_generator->getTrajTimeStart()+0.01,
            traj_time_final = traj_generator->getTrajTimeFinal(),
            traj_time_now;
    traj_time_now = traj_time_start;


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
        generated_ptsNnum++;

    }

    /*输出点提醒*/
    init_table_out();
    table_update();
    plotTrajectory();

}


/**
 * @brief 点击“生成文件”按钮
 * @todo 使用tabletView的数据
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
 *
 */
void PagePath::on_Button_clear_clicked()
{
    init_table_out();
    init_table_input();
//    ui->plainTextEdit_input->clear();
//    ui->Edit_bezier_length->clear();
//    ui->Edit_point_num->clear();
    inputPoint_num=0;
    generated_ptsNnum=0;
    segment_num=0;
    trajPlotView->scene()->clear();
    input_ptsList.clear();
    draw_axis();
    addKeypt();
    addKeypt();
    trajPlotView->show();
    //清零轨迹生成器时要全部清空
    generated_ptsSegList.clear();
    plotWayPt.clear();
    plotKeyPt.clear();

//    ui->Edit_bezier_cnt->setText("0");

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
        QMessageBox::information(nullptr, "error", "No such file",
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
 * @brief PagePath::addKeypt() 添加关键点
 */
void PagePath::addKeypt() {

    //在列表中添加spinbox便于编辑
    if (inputPoint_num > 0) {
        auto lastRowNumItem = new QStandardItem(QString::asprintf("%d", 1));
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
    connect(pointItem,&WayPtGraphicsItem::pointSelected,this, &PagePath::scenePointSelected);
    connect(pointItem,&WayPtGraphicsItem::pointPosChanged,this, &PagePath::scenePointPosChanged);
    connect(pointItem,&WayPtGraphicsItem::deletePointItem,this, &PagePath::scenePointDeleted);

    plotKeyPt.push_back(pointItem);

    trajPlotView->scene()->addItem(pointItem);
    inputPoint_num++;
}
/**
 * @brief PagePath::on_Button_add_point_clicked 点击“加点”按钮
 */
void PagePath::on_Button_add_point_clicked()
{
    addKeypt();
}


/**
 * @brief PagePath::on_Button_delete_point_clicked  点击删点按钮
 */
void PagePath::on_Button_delete_point_clicked()
{
    if (inputPoint_num > 2 )
    {
        removePt(plotKeyPt[inputPoint_num-1]->getPointIndex(),inputPoint_num-1);
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


void PagePath::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    //设置图片背景
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

    auto retPt = cal_rotate_point(
            selPoint->scenePos().x(),selPoint->scenePos().y(),
            -translate_dangle,
            -translate_dx, -translate_dy,
            toggle_x, toggle_y,
            1/width_t, 1/height_t
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

    auto retPt = cal_rotate_point(
            selPoint->scenePos().x(),selPoint->scenePos().y(),
            -translate_dangle,
            -translate_dx, -translate_dy,
            toggle_x, toggle_y,
            1/width_t, 1/height_t
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

void PagePath::on_table_output_CustomContextMenuRequested(QPoint pos)
{
    output_view_Menu->exec(QCursor::pos());
}

void PagePath::on_table_input_CustomContextMenuRequested(QPoint pos)
{

    input_view_Menu->exec(QCursor::pos());
}

void PagePath::removePt(int wayidx, int keyidx) {

    if (keyidx >= 0 && inputPoint_num > 2 )
    {
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
        trajPlotView->scene()->removeItem(waypt);
        plotWayPt.removeAt(wayidx);
        outputModel->removeRow(wayidx);
        waypt->deleteLater();
        generated_ptsNnum--;
    }

    updatePlotIdx();
}

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


