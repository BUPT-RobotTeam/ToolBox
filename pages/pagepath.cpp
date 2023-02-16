#include "pagepath.h"
#include "ui_pagepath.h"
#include "ui_txtdialog.h"
#include <QString>
#include <QImage>
#include <QBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QChart>
#include <QVector>
#include <QMenu>
#include <QTransform>
#include <time_optimizer/trajectory_generator.h>

float map_width = 0;
float map_height = 0;
QPointF *carpos = new QPointF[1000];
int carpos_cnt = 0;
int m_point=-1;
int n_point=-1;
int x0_num=-1;
int point_num;
int x_toggle=1;
int y_toggle=1;
int x2_toggle=1;
int y2_toggle=1;
int curve=-1;
float res_w,res_h;

//TODO:: use abstract trajectory generator class;
Bezier *bezier_path = new Bezier[10];



int traj_num = 1;
int traj_Edit_idx = 0;

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
    //调整plot尺寸
    res_w=float(ui->customPlot->width());
    res_h=float(ui->customPlot->width())/float(img->size().width())*float(img->size().height());
    ui->customPlot->resize(int(res_w),int(res_h));
    qDebug()<<"init"<<ui->customPlot->width()<<ui->customPlot->height()<<img->size().height();

    newImg = new QImage;
    *newImg = img->scaled(int(res_w),int(res_h));
    point_num=0;

    ui->Edit_translate_dx->text().toDouble();
    ui->Edit_translate_dy->text().toDouble();
    ui->Edit_translate_dangle->text().toDouble() - 90;

//    connect(ui->customPlot,SIGNAL(mousePress(QMouseEvent*)),this,SLOT(myMousePressEvent(QMouseEvent*)));
//    connect(ui->customPlot,SIGNAL(mouseRelease(QMouseEvent*)),this,SLOT(myMouseReleaseEvent(QMouseEvent*)));
//    connect(ui->customPlot,SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(myMouseMoveEvent(QMouseEvent*)));

    QSharedPointer<AbstractTrajGenerator> traj_gen(new TimeOptimizerTraj(1,1));
    traj_generators.push_back(traj_gen);

    ui->scrollArea->setWidget(ui->widget);
    ui->widget->setMinimumSize(500,1000);

    init_table_out();
    table_update();

    actionScreen = new QAction();
    connect(ui->spinBox_kspeed, SIGNAL(valueChanged(int)), ui->Slider_kspeed, SLOT(setValue(int)));
    connect(ui->Slider_kspeed, SIGNAL(valueChanged(int)), ui->spinBox_kspeed, SLOT(setValue(int)));
    connect(actionScreen,SIGNAL(triggered()),this,SLOT(on_actionScreen_triggered()));

    ui->customPlot->xAxis->setBasePen(QPen(Qt::blue,3));
    ui->customPlot->yAxis->setBasePen(QPen(Qt::blue,3));
    ui->customPlot->xAxis2->setBasePen(QPen(Qt::blue,3));
    ui->customPlot->yAxis2->setBasePen(QPen(Qt::blue,3));

    ui->customPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->customPlot->xAxis2->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->customPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->customPlot->yAxis2->setUpperEnding(QCPLineEnding::esSpikeArrow);

    ui->customPlot->xAxis->setLabel("X");
    ui->customPlot->xAxis2->setLabel("X");
    ui->customPlot->yAxis->setLabel("Y");
    ui->customPlot->yAxis2->setLabel("Y");

    ui->customPlot->xAxis->setTickPen(QPen(Qt::black,2));
    ui->customPlot->xAxis->setTickLength(7);
    ui->customPlot->xAxis->setSubTickPen(QPen(Qt::black,1.3));
    ui->customPlot->xAxis->setSubTickLength(4);
    ui->customPlot->xAxis->setNumberFormat("g");

    ui->customPlot->xAxis2->setTickPen(QPen(Qt::black,2));
    ui->customPlot->xAxis2->setTickLength(7);
    ui->customPlot->xAxis2->setSubTickPen(QPen(Qt::black,1.3));
    ui->customPlot->xAxis2->setSubTickLength(4);
    ui->customPlot->xAxis2->setNumberFormat("g");

    ui->customPlot->yAxis->setTickPen(QPen(Qt::black,2));
    ui->customPlot->yAxis->setTickLength(7);
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::black,1.3));
    ui->customPlot->yAxis->setSubTickLength(4);
    ui->customPlot->yAxis->setNumberFormat("g");

    ui->customPlot->yAxis2->setTickPen(QPen(Qt::black,2));
    ui->customPlot->yAxis2->setTickLength(7);
    ui->customPlot->yAxis2->setSubTickPen(QPen(Qt::black,1.3));
    ui->customPlot->yAxis2->setSubTickLength(4);
    ui->customPlot->yAxis2->setNumberFormat("g");

    ui->customPlot->addGraph();
    ui->customPlot->addGraph();


//        QGraphicsScene* pScene = new QGraphicsScene(this);
//        pScene->addWidget (ui->button);
//        QGraphicsView* pView = new QGraphicsView(ui->groupBox_2);
//        pView->setScene(pScene);
//        pView->setFixedSize (ui->button->width(),ui->button->height());
////        pView->setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
//        pView->rotate(90);

}


PagePath::~PagePath()
{
    delete ui;
    delete txtdialog;
    delete mVesc;
    delete model;
    delete aItem;
    delete img;
    delete newImg;
    delete point;
    delete xy;
    delete point_line;
    delete actionScreen;
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
//    if( !traj_Edit_idx ) {return;}
    if(!traj_generators[traj_Edit_idx]->isHasTraj()){return;}
    for (int i = 0; i < generated_ptsList[traj_Edit_idx].size(); i++)
    {
        QString num = QString::asprintf("%d", i);
        aItem = new QStandardItem(num);            // 创建item对象
        aItem->setTextAlignment(Qt::AlignHCenter); // 设置item值，居中对齐
        model->setItem(i, 0, aItem);               // 将item写入model指定位置

        //        QString x = QString::asprintf("%.3f", bezier_path->out_points[i].X-ui->Edit_translate_dy->text().toDouble());
        QString x = QString::asprintf("%.3f",generated_ptsList[traj_Edit_idx][i].x());
        aItem = new QStandardItem(x);
        aItem->setTextAlignment(Qt::AlignHCenter);
        model->setItem(i, 1, aItem);
        //qDebug()<<"table"<<x<<y;
        //        QString y = QString::asprintf("%.3f", bezier_path->out_points[i].Y-ui->Edit_translate_dx->text().toDouble());
        QString y = QString::asprintf("%.3f", generated_ptsList[traj_Edit_idx][i].y());
        aItem = new QStandardItem(y);
        aItem->setTextAlignment(Qt::AlignHCenter);
        model->setItem(i, 2, aItem);

        QString speed = QString::asprintf("%.3f", generated_speedList[traj_Edit_idx][i]);
        aItem = new QStandardItem(speed);
        aItem->setTextAlignment(Qt::AlignHCenter);
        model->setItem(i, 3, aItem);

        QString direct = QString::asprintf("%.3f", generated_dirList[traj_Edit_idx][i]);
        aItem = new QStandardItem(direct);
        aItem->setTextAlignment(Qt::AlignHCenter);
        model->setItem(i, 4, aItem);

        QString angle = QString::asprintf("%.3f", generated_angleList[traj_Edit_idx][i]);
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
        connect(mVesc->commands(), SIGNAL(drawCarPos(float, float)),
                this, SLOT(drawCarPos(float, float)));
    }
}


/**
 * @brief 打印小车轨迹点
 *
 * @param x
 * @param y
 */
void PagePath::drawCarPos(float x, float y)
{
    carpos[carpos_cnt++].setX(x);
    carpos[carpos_cnt++].setY(y);
    QString pos_ = "";
    pos_=QString::asprintf("%.3f", x);
    ui->Edit_posx->setText(pos_);
    pos_=QString::asprintf("%.3f", y);
    ui->Edit_posy->setText(pos_);
}


/**
 * @brief 点击输入曲线数量按钮
 *
 */
void PagePath::on_Button_bezier_num_clicked()
{
    //TODO:: 应该使用edit的事件来触发判断和数量更新
    if (ui->Edit_bezier_num->text().isEmpty())
    {
        QMessageBox::warning(NULL, "贝塞尔曲线数量不能为0", "请输入正确的数目", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    traj_num = ui->Edit_bezier_num->text().toInt();
    input_ptsList.resize(traj_num);
    generated_ptsList.resize(traj_num);
    generated_angleList.resize(traj_num);
    generated_speedList.resize(traj_num);
    generated_dirList.resize(traj_num);
    traj_generators.resize(traj_num);
}


/**
 * @brief 点击加载曲线按钮
 *
 */
void PagePath::on_Button_load_path_clicked()
{
    ui->Edit_translate_dangle->text().toDouble() - 90;
    if (ui->Edit_x_toggle->text().toInt())
    {
        ui->Edit_x_toggle->text().toInt();
    }
    if (ui->Edit_x_toggle->text().toInt())
    {
        ui->Edit_x_toggle->text().toInt();
    }

    map_width = ui->Edit_map_width->text().toFloat();
    map_height = ui->Edit_map_heigh->text().toFloat();

    res_w=float(ui->customPlot->width());
    res_h=float(ui->customPlot->width())/float(img->size().width())*float(img->size().height());
    ui->customPlot->resize(int(res_w),int(res_h));
    *newImg = img->scaled(int(res_w),int(res_h));
    QLinearGradient plotGradient;
    plotGradient.setColorAt(0, QColor(255, 255, 255, 0));
    ui->customPlot->axisRect()->setBackground(plotGradient);
    ui->customPlot->axisRect()->setBackground(QPixmap::fromImage(*newImg));
    ui->customPlot->axisRect()->setBackgroundScaledMode(Qt::AspectRatioMode::IgnoreAspectRatio);

    ui->customPlot->axisRect()->setMinimumMargins(QMargins(20, 0, 20, 0));
    if(ui->Edit_x_toggle->text().toInt()==1 && ui->Edit_y_toggle->text().toInt()==1)
    {
        ui->customPlot->xAxis->setRange(-ui->Edit_translate_dy->text().toFloat(), map_width-ui->Edit_translate_dy->text().toFloat());
        ui->customPlot->yAxis->setRange(-ui->Edit_translate_dx->text().toFloat(), map_height-ui->Edit_translate_dx->text().toFloat());
        ui->customPlot->xAxis->setVisible(true);
        ui->customPlot->xAxis2->setVisible(false);
        ui->customPlot->yAxis->setVisible(true);
        ui->customPlot->yAxis2->setVisible(false);
        if(x_toggle==-1)
        {
            ui->customPlot->xAxis->setRangeReversed(false);
        }
        if(y_toggle==-1)
        {
            ui->customPlot->yAxis->setRangeReversed(false);
        }
        x_toggle=1;
        y_toggle=1;
        ui->customPlot->graph(0)->setKeyAxis(ui->customPlot->xAxis);
        ui->customPlot->graph(0)->setValueAxis(ui->customPlot->yAxis);
        ui->customPlot->graph(1)->setKeyAxis(ui->customPlot->xAxis);
        ui->customPlot->graph(1)->setValueAxis(ui->customPlot->yAxis);
        ui->customPlot->xAxis->setOffset(-int(ui->Edit_translate_dx->text().toDouble()/ui->Edit_map_heigh->text().toDouble()*(ui->customPlot->height()-32)));
        ui->customPlot->yAxis->setOffset(-int(ui->Edit_translate_dy->text().toDouble()/ui->Edit_map_width->text().toDouble()*(ui->customPlot->width()-27.5)));
    }
    else if(ui->Edit_x_toggle->text().toInt()==1 && ui->Edit_y_toggle->text().toInt()==-1)
    {
        ui->customPlot->xAxis2->setRange(-ui->Edit_translate_dy->text().toFloat(), map_width-ui->Edit_translate_dy->text().toFloat());
        ui->customPlot->yAxis->setRange(-ui->Edit_translate_dx->text().toFloat(), map_height-ui->Edit_translate_dx->text().toFloat());
        ui->customPlot->xAxis2->setVisible(true);
        ui->customPlot->xAxis->setVisible(false);
        ui->customPlot->yAxis->setVisible(true);
        ui->customPlot->yAxis2->setVisible(false);
        if(x2_toggle==-1)
        {
            ui->customPlot->xAxis2->setRangeReversed(false);
        }
        if(y_toggle==1)
        {
            ui->customPlot->yAxis->setRangeReversed(true);
        }
        x2_toggle=1;
        y_toggle=-1;
        ui->customPlot->graph(0)->setKeyAxis(ui->customPlot->xAxis2);
        ui->customPlot->graph(0)->setValueAxis(ui->customPlot->yAxis);
        ui->customPlot->graph(1)->setKeyAxis(ui->customPlot->xAxis2);
        ui->customPlot->graph(1)->setValueAxis(ui->customPlot->yAxis);
        ui->customPlot->xAxis2->setOffset(-int(ui->Edit_translate_dx->text().toDouble()/ui->Edit_map_heigh->text().toDouble()*(ui->customPlot->height()-32)));
        ui->customPlot->yAxis->setOffset(-int(ui->Edit_translate_dy->text().toDouble()/ui->Edit_map_width->text().toDouble()*(ui->customPlot->width()-27.5)));
    }
    else if(ui->Edit_x_toggle->text().toInt()==-1 && ui->Edit_y_toggle->text().toInt()==1)
    {
        ui->customPlot->xAxis->setRange(-ui->Edit_translate_dy->text().toFloat(), map_width-ui->Edit_translate_dy->text().toFloat());
        ui->customPlot->yAxis2->setRange(-ui->Edit_translate_dx->text().toFloat(), map_height-ui->Edit_translate_dx->text().toFloat());
        ui->customPlot->yAxis2->setVisible(true);
        ui->customPlot->yAxis->setVisible(false);
        ui->customPlot->xAxis->setVisible(true);
        ui->customPlot->xAxis2->setVisible(false);
        if(x_toggle==1)
        {
            ui->customPlot->xAxis->setRangeReversed(true);
        }
        if(y2_toggle==-1)
        {
            ui->customPlot->yAxis2->setRangeReversed(false);
        }
        x_toggle=-1;
        y2_toggle=1;
        ui->customPlot->graph(0)->setKeyAxis(ui->customPlot->xAxis);
        ui->customPlot->graph(0)->setValueAxis(ui->customPlot->yAxis2);
        ui->customPlot->graph(1)->setKeyAxis(ui->customPlot->xAxis);
        ui->customPlot->graph(1)->setValueAxis(ui->customPlot->yAxis2);
        ui->customPlot->xAxis->setOffset(-int(ui->Edit_translate_dx->text().toDouble()/ui->Edit_map_heigh->text().toDouble()*(ui->customPlot->height()-32)));
        ui->customPlot->yAxis2->setOffset(-int(ui->Edit_translate_dy->text().toDouble()/ui->Edit_map_width->text().toDouble()*(ui->customPlot->width()-27.5)));
    }
    else if(ui->Edit_x_toggle->text().toInt()==-1 && ui->Edit_y_toggle->text().toInt()==-1)
    {
        ui->customPlot->xAxis2->setRange(-ui->Edit_translate_dy->text().toFloat(), map_width-ui->Edit_translate_dy->text().toFloat());
        ui->customPlot->yAxis2->setRange(-ui->Edit_translate_dx->text().toFloat(), map_height-ui->Edit_translate_dx->text().toFloat());
        ui->customPlot->yAxis2->setVisible(true);
        ui->customPlot->yAxis->setVisible(false);
        ui->customPlot->xAxis2->setVisible(true);
        ui->customPlot->xAxis->setVisible(false);
        if(x2_toggle==1)
        {
            ui->customPlot->xAxis2->setRangeReversed(true);
        }
        if(y2_toggle==1)
        {
            ui->customPlot->yAxis2->setRangeReversed(true);
        }
        x2_toggle=-1;
        y2_toggle=-1;
        ui->customPlot->graph(0)->setKeyAxis(ui->customPlot->xAxis2);
        ui->customPlot->graph(0)->setValueAxis(ui->customPlot->yAxis2);
        ui->customPlot->graph(1)->setKeyAxis(ui->customPlot->xAxis2);
        ui->customPlot->graph(1)->setValueAxis(ui->customPlot->yAxis2);
        ui->customPlot->xAxis2->setOffset(-int(ui->Edit_translate_dx->text().toDouble()/ui->Edit_map_heigh->text().toDouble()*(ui->customPlot->height()-32)));
        ui->customPlot->yAxis2->setOffset(-int(ui->Edit_translate_dy->text().toDouble()/ui->Edit_map_width->text().toDouble()*(ui->customPlot->width()-27.5)));
    }

    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, Qt::green, 8));
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(0)->setData(x_inserted_pts, y_inserted_pts);

    ui->customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::red, 2), QBrush(Qt::white), 8));
    ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(1)->setData(x_input_pts, y_input_pts);

    ui->customPlot->replot();

    //    QCPPainter *painter=new QCPPainter(ui->customPlot);
    //    ui->customPlot->toPainter(painter);
    //    painter->rotate(45.0);

    //    qDebug()<<"---plot loading"<<ui->customPlot->width()<<ui->customPlot->height();
}


/**
* @brief PagePath::myMousePressEvent 配合移动或删除轨迹点
* @param event
*/
/*
void PagePath::myMousePressEvent(QMouseEvent *event)
{
    qDebug()<<"mousePressEvent"<<bezier_path[traj_Edit_idx].out_num;
    int x_pos = event->pos().x();
    int y_pos = event->pos().y();
    float x_val,y_val;

    if(ui->Edit_x_toggle->text().toInt()==1 && ui->Edit_y_toggle->text().toInt()==1)
    {
        x_val = ui->customPlot->xAxis->pixelToCoord(x_pos);
        y_val = ui->customPlot->yAxis->pixelToCoord(y_pos);
    }
    else if(ui->Edit_x_toggle->text().toInt()==1 && ui->Edit_y_toggle->text().toInt()==-1)
    {
        x_val = ui->customPlot->xAxis2->pixelToCoord(x_pos);
        y_val = ui->customPlot->yAxis->pixelToCoord(y_pos);
    }
    else if(ui->Edit_x_toggle->text().toInt()==-1 && ui->Edit_y_toggle->text().toInt()==1)
    {
        x_val = ui->customPlot->xAxis->pixelToCoord(x_pos);
        y_val = ui->customPlot->yAxis2->pixelToCoord(y_pos);
    }
    else
    {
        x_val = ui->customPlot->xAxis2->pixelToCoord(x_pos);
        y_val = ui->customPlot->yAxis2->pixelToCoord(y_pos);
    }

    if(event->button()==Qt::LeftButton)
    {
        for(int i=0;i<=bezier_path[traj_Edit_idx].out_num;i++){
            if(fabs(x_val - x_all_pts[i]) < 0.2 && fabs(y_val - y_all_pts[i]) < 0.2){
                x0_num=i;
                break;
            }
        }
        for(int i=0; i < x_inserted_pts.size(); i++){
            if(fabs(x_val - x_inserted_pts[i]) < 0.2 && fabs(y_val - y_inserted_pts[i]) < 0.2){
                m_point=i;
                curve=0;
                //                qDebug()<<"left now is"<<i;
                break;
            }
        }
        if(m_point==-1)
        {
            for(int i=0; i < x_input_pts.size(); i++){
                if(fabs(x_val - x_input_pts[i]) < 0.2 && fabs(y_val - y_input_pts[i]) < 0.2){
                    m_point=i;
                    curve=1;
                    //                    qDebug()<<"left now is"<<i;
                    break;
                }
            }
        }
    }
    else if (event->button()==Qt::RightButton)
    {
        for(int i=0;i<=bezier_path[traj_Edit_idx].out_num;i++){
            if(fabs(x_val - x_all_pts[i]) < 0.2 && fabs(y_val - y_all_pts[i]) < 0.2){
                x0_num=i;
                break;
            }
        }
        for(int i=0; i < x_inserted_pts.size(); i++){
            if(fabs(x_val - x_inserted_pts[i]) < 0.2 && fabs(y_val - y_inserted_pts[i]) < 0.2){
                //                qDebug()<<"right now is"<<i;
                n_point=i;
                curve=0;
                break;
            }
        }
        for(int i=0; i < x_input_pts.size(); i++){
            if(fabs(x_val - x_input_pts[i]) < 0.2 && fabs(y_val - y_input_pts[i]) < 0.2){
                n_point=i;
                curve=1;
                //                qDebug()<<"right now is"<<i;
                break;
            }
        }
        if(n_point!=-1)
        {
            QMenuBar *menubar=new QMenuBar(ui->customPlot);
            QMenu *menu = new QMenu(menubar);
            actionScreen->setText(tr("刪除"));
            menu->addAction(actionScreen);
            QPoint *p=new QPoint(cursor().pos());
            p->setX(p->x()+5);
            p->setY(p->y()+5);
            menu->exec(*p);
            n_point=-1;
            x0_num=-1;
            curve=-1;
        }
    }
    qDebug()<<"-----pressed"<<"x0_num"<<x0_num;
}

*/
/**
 * @brief PagePath::myMouseReleaseEvent 配合移动或删除轨迹点
 * @param event
 */
 /*
void PagePath::myMouseReleaseEvent(QMouseEvent *event)
{
    m_point=-1;
}
*/

/**
 * @brief PagePath::myMouseMoveEvent 配合移动或删除轨迹点
 * @param event
 */
 /*
void PagePath::myMouseMoveEvent(QMouseEvent *event)
{
    int x_pos = event->pos().x();
    int y_pos = event->pos().y();
    float x_val,y_val;

    if(ui->Edit_x_toggle->text().toInt()==1 && ui->Edit_y_toggle->text().toInt()==1)
    {
        x_val = ui->customPlot->xAxis->pixelToCoord(x_pos);
        y_val = ui->customPlot->yAxis->pixelToCoord(y_pos);
    }
    else if(ui->Edit_x_toggle->text().toInt()==1 && ui->Edit_y_toggle->text().toInt()==-1)
    {
        x_val = ui->customPlot->xAxis2->pixelToCoord(x_pos);
        y_val = ui->customPlot->yAxis->pixelToCoord(y_pos);
    }
    else if(ui->Edit_x_toggle->text().toInt()==-1 && ui->Edit_y_toggle->text().toInt()==1)
    {
        x_val = ui->customPlot->xAxis->pixelToCoord(x_pos);
        y_val = ui->customPlot->yAxis2->pixelToCoord(y_pos);
    }
    else
    {
        x_val = ui->customPlot->xAxis2->pixelToCoord(x_pos);
        y_val = ui->customPlot->yAxis2->pixelToCoord(y_pos);
    }

    for(int i=0;i<=bezier_path[traj_Edit_idx].out_num;i++){
        if(fabs(x_val - x_all_pts[i]) < 0.2 && fabs(y_val - y_all_pts[i]) < 0.2 && !(event->button() & Qt::LeftButton)){
            QString str;
            str = QString("第%1个点\nx: %2\ny: %3").arg(QString::asprintf("%d",i+1)).arg(QString::asprintf("%.3f", x_all_pts[i]))
                    .arg(QString::asprintf("%.3f", y_all_pts[i]));
            qDebug() << "i" << i << "x" << x_all_pts[i] << "y" << y_all_pts[i];
            QToolTip::showText(cursor().pos(), str, this);
            break;
        }
    }
    if(m_point==-1)
        return;

    QString str;
    str = QString("第%1个点\nx: %2\ny: %3").arg(QString::asprintf("%d",x0_num+1)).arg(QString::asprintf("%.3f", x_val))
            .arg(QString::asprintf("%.3f",y_val));
    qDebug()<<"x0_num"<<x0_num
           <<"point:"<<x_val<<y_val<<str;
    QToolTip::showText(cursor().pos(), str, this);

    x_all_pts[x0_num]=x_val;
    y_all_pts[x0_num]=y_val;

    if(curve==1)
    {
        x_input_pts[m_point]=x_val;
        y_input_pts[m_point]=y_val;
    }
    else if(curve==0)
    {
        x_inserted_pts[m_point]=x_val;
        y_inserted_pts[m_point]=y_val;
    }

    bezier_path[traj_Edit_idx].out_points[x0_num].X=x_val;
    bezier_path[traj_Edit_idx].out_points[x0_num].Y=y_val;

    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, Qt::green, 8));
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(0)->setData(x_inserted_pts, y_inserted_pts);

    ui->customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::red, 2), QBrush(Qt::white), 8));
    ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(1)->setData(x_input_pts, y_input_pts);

    ui->customPlot->replot();

}
*/

/**
 * @brief PagePath::on_actionScreen_triggered 删除点槽函数
 */
void PagePath::on_actionScreen_triggered()
{
    x_all_pts.remove(x0_num);
    y_all_pts.remove(x0_num);

    if(curve==0)
    {
        x_inserted_pts.remove(n_point);
        y_inserted_pts.remove(n_point);
    }
    else if(curve==1)
    {
        x_input_pts.remove(n_point);
        y_input_pts.remove(n_point);
    }

    for (int i=x0_num;i<bezier_path[traj_Edit_idx].out_num; i++)
    {
        bezier_path[traj_Edit_idx].out_points[i].X=bezier_path[traj_Edit_idx].out_points[i + 1].X;
        bezier_path[traj_Edit_idx].out_points[i].Y=bezier_path[traj_Edit_idx].out_points[i + 1].Y;
    }
    bezier_path[traj_Edit_idx].out_num-=1;

    ui->customPlot->graph(0)->setData(x_inserted_pts, y_inserted_pts);
    ui->customPlot->graph(1)->setData(x_input_pts, y_input_pts);
    ui->customPlot->replot();

    qDebug()<<"n_point"<<n_point<<"out_num"<<bezier_path[traj_Edit_idx].out_num;
}


/**
 * @brief 点击“输入下一条”按钮
 *
 *
 */
void PagePath::on_Button_add_bezier_clicked()
{
    traj_Edit_idx = (traj_Edit_idx + 1) % traj_num;
//    ui->Edit_bezier_cnt->clear();
    QString cnt = "";
    cnt = QString::asprintf("%d", traj_Edit_idx);
    ui->Edit_bezier_cnt->setText(cnt);

    QMessageBox::information(NULL, "提示", "请输入过程点",
                             QMessageBox::Yes, QMessageBox::Yes);
    if(traj_generators[ traj_Edit_idx ].isNull())
    {
        traj_generators[ traj_Edit_idx ].reset(new TimeOptimizerTraj(1,1));
    }
}


/**
 * @brief 点击“确定”按钮，开始规划轨迹
 *
 */
void PagePath::on_Button_create_path_clicked()
{
    //    if (ui->Edit_x0->text().isEmpty())
    //    {
    //        QMessageBox::warning(NULL, "过程点数量不能为0", "请输入正确的过程点", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    //        return;
    //    }

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

    traj_generators[traj_Edit_idx]->setMaxVel(max_v);
    traj_generators[traj_Edit_idx]->setMaxAcc(max_acc);
    traj_generators[traj_Edit_idx]->setMaxDAcc(max_jerk);


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
    input_ptsList.resize(traj_num);
    input_ptsList[traj_Edit_idx]=input_pts;
    Eigen::MatrixXd input_waypoints_mat(input_pts.size(), 3);
//    Eigen::Vector3d input_waypoint_vec;
    for(int i=0 ;i<input_pts.size();i++)
    {
        QPointF pt = input_pts[i];
//        input_waypoint_vec(0)=pt.x();
//        input_waypoint_vec(1)=pt.y();
//        input_waypoint_vec(2)=0;
        input_waypoints_mat.row(i) <<  pt.x(),pt.y(),0 ;
    }

    traj_generators[traj_Edit_idx]->trajGeneration(input_waypoints_mat);
    if ( !traj_generators[traj_Edit_idx]->isHasTraj()){return;}
    // 采样
    int samplePtNum_btw_wayPt;
    samplePtNum_btw_wayPt = ui->Edit_num_btw_two->text().toInt();

    int segment_num = traj_generators[traj_Edit_idx]->getSegmentNum();
    double  traj_time_start = traj_generators[traj_Edit_idx]->getTrajTimeStart(),
            traj_time_final = traj_generators[traj_Edit_idx]->getTrajTimeFinal(),
            traj_time_now;
    traj_time_now = traj_time_start;
    QVector<double> traj_speed,traj_dir,traj_angle;
    QVector<QPointF> traj_pos;
    x_inserted_pts.clear();
    y_inserted_pts.clear();
    for(int i=0;i<segment_num;i++)
    {
        double seg_time = traj_generators[traj_Edit_idx]->getTrajSegmentTime(i);
        double time_interval=seg_time / samplePtNum_btw_wayPt;
        double seg_time_start = traj_time_now;
        for(int j=0;j < samplePtNum_btw_wayPt;j++)
        {
            double t = seg_time_start + 1.0 * j * time_interval;
            auto traj_cmd = traj_generators[traj_Edit_idx]->getCtrlCmd(t);
            Eigen::Vector2d pos_cmd,vel_cmd;
            pos_cmd = (traj_cmd.block(0,0,2,1));
            vel_cmd = (traj_cmd.block(0,1,2,1));
            double vel = vel_cmd.norm();
            double dir = std::acos( vel_cmd.dot(Eigen::Vector2d(1,0)) / ( vel_cmd.norm()*1.0 ) );
            traj_pos.push_back(QPointF(pos_cmd(0),pos_cmd(1)));
            traj_speed.push_back(vel);
            traj_dir.push_back(dir);
            traj_angle.push_back(0);

            x_inserted_pts.push_back(pos_cmd(0));
            y_inserted_pts.push_back(pos_cmd(1));

        }
        traj_time_now +=seg_time;
    }
    generated_ptsList[traj_Edit_idx]=traj_pos;
    generated_angleList[traj_Edit_idx]=traj_angle;
    generated_dirList[traj_Edit_idx]=traj_dir;
    generated_speedList[traj_Edit_idx]=traj_speed;
    

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
    ui->plainTextEdit_input->clear();
    QString inputPtInfo = "";
    inputPtInfo=QString::asprintf("第%d条贝塞尔曲线\r\n", traj_Edit_idx);
    ui->plainTextEdit_input->insertPlainText(inputPtInfo);
    for (int i = 0; i < input_ptsList[traj_Edit_idx].size(); i++)
    {
        inputPtInfo=QString::asprintf(
                "第%d个点,(%.3f,%.3f)\r\n",
                i,input_ptsList[traj_Edit_idx][i].x(),
                input_ptsList[traj_Edit_idx][i].y()
                );
        ui->plainTextEdit_input->insertPlainText(inputPtInfo);
    }

    /*输出点个数*/
    ui->Edit_point_num->clear();
    QString outputPtNum = "";
    outputPtNum=QString::asprintf("%d", generated_ptsList[traj_Edit_idx].size());
    ui->Edit_point_num->setText(outputPtNum);

    /*路径长度*/
//    ui->Edit_bezier_length->clear();
//    QString bezier_length = "";
//    bezier_length.sprintf("%.3f", bezier_path[traj_Edit_idx].length);
//    ui->Edit_bezier_length->setText(bezier_length);

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
    qDebug() << "input_num" << input_ptsList[traj_Edit_idx].size() << "out_num" <<  generated_ptsList[traj_Edit_idx].size();

    //    qDebug()<<"-----sure---"<<ui->customPlot->width()<<ui->customPlot->height();
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

        for (int i = 0; i < traj_num; i++)
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
        //        qDebug() << items;
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
    res_w=float(ui->customPlot->width());
    res_h=float(ui->customPlot->width())/float(img->size().width())*float(img->size().height());
    ui->customPlot->resize(int(res_w),int(res_h));
    *newImg = img->scaled(int(res_w),int(res_h));
    QLinearGradient plotGradient;
    plotGradient.setColorAt(0, QColor(255, 255, 255, 0));
    ui->customPlot->axisRect()->setBackground(plotGradient);
    ui->customPlot->axisRect()->setBackground(QPixmap::fromImage(*newImg));
    ui->customPlot->axisRect()->setBackgroundScaledMode(Qt::AspectRatioMode::IgnoreAspectRatio);
    ui->customPlot->replot();
}


///**
// * @brief 点击“曲线对比”按钮
// *
// */
//void PagePath::on_Button_cmp_clicked()
//{
//    mychart = new Mychart;
//    mychart->show();
//}


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
    //    qDebug() << point_line->parent()->parent();
    //    qDebug() << point_line->parent()->parent()->parent();
    //    qDebug() << ui->point_area_3->children();
    //    qDebug() << point_line->parent()->parent()->children();
    //    qDebug("input point=============================:%d", point_num);
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
