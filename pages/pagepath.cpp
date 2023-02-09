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

Bezier *bezier_path = new Bezier[10];
int bezier_num = 1;
int bezier_cnt = 0;

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

    res_w=float(ui->customPlot->width());
    res_h=float(ui->customPlot->width())/float(img->size().width())*float(img->size().height());
    ui->customPlot->resize(int(res_w),int(res_h));
    qDebug()<<"init"<<ui->customPlot->width()<<ui->customPlot->height()<<img->size().height();

    newImg = new QImage;
    *newImg = img->scaled(int(res_w),int(res_h));
    point_num=0;

    translate_dx = ui->Edit_translate_dx->text().toDouble();
    translate_dy = ui->Edit_translate_dy->text().toDouble();
    translate_dangle = ui->Edit_translate_dangle->text().toDouble() - 90;

    connect(ui->customPlot,SIGNAL(mousePress(QMouseEvent*)),this,SLOT(myMousePressEvent(QMouseEvent*)));
    connect(ui->customPlot,SIGNAL(mouseRelease(QMouseEvent*)),this,SLOT(myMouseReleaseEvent(QMouseEvent*)));
    connect(ui->customPlot,SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(myMouseMoveEvent(QMouseEvent*)));

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

        //        QString x = QString::asprintf("%.3f", bezier_path->out_points[i].X-ui->Edit_translate_dy->text().toDouble());
        QString x = QString::asprintf("%.3f", bezier_path[bezier_cnt].out_points[i].X);
        aItem = new QStandardItem(x);
        aItem->setTextAlignment(Qt::AlignHCenter);
        model->setItem(i, 1, aItem);
        //qDebug()<<"table"<<x<<y;
        //        QString y = QString::asprintf("%.3f", bezier_path->out_points[i].Y-ui->Edit_translate_dx->text().toDouble());
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


/**
 * @brief 点击加载曲线按钮
 *
 */
void PagePath::on_Button_load_path_clicked()
{
    translate_dangle = ui->Edit_translate_dangle->text().toDouble() - 90;
    if (ui->Edit_x_toggle->text().toInt())
    {
        toggle_x = ui->Edit_x_toggle->text().toInt();
    }
    if (ui->Edit_x_toggle->text().toInt())
    {
        toggle_y = ui->Edit_x_toggle->text().toInt();
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
    ui->customPlot->graph(0)->setData(x, y);

    ui->customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::red, 2), QBrush(Qt::white), 8));
    ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(1)->setData(x1, y1);

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
void PagePath::myMousePressEvent(QMouseEvent *event)
{
    qDebug()<<"mousePressEvent"<<bezier_path[bezier_cnt].out_num;
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
        for(int i=0;i<=bezier_path[bezier_cnt].out_num;i++){
            if(fabs(x_val-x0[i])<0.2&&fabs(y_val-y0[i])<0.2){
                x0_num=i;
                break;
            }
        }
        for(int i=0;i<x.size();i++){
            if(fabs(x_val-x[i])<0.2&&fabs(y_val-y[i])<0.2){
                m_point=i;
                curve=0;
                //                qDebug()<<"left now is"<<i;
                break;
            }
        }
        if(m_point==-1)
        {
            for(int i=0;i<x1.size();i++){
                if(fabs(x_val-x1[i])<0.2&&fabs(y_val-y1[i])<0.2){
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
        for(int i=0;i<=bezier_path[bezier_cnt].out_num;i++){
            if(fabs(x_val-x0[i])<0.2&&fabs(y_val-y0[i])<0.2){
                x0_num=i;
                break;
            }
        }
        for(int i=0;i<x.size();i++){
            if(fabs(x_val-x[i])<0.2&&fabs(y_val-y[i])<0.2){
                //                qDebug()<<"right now is"<<i;
                n_point=i;
                curve=0;
                break;
            }
        }
        for(int i=0;i<x1.size();i++){
            if(fabs(x_val-x1[i])<0.2&&fabs(y_val-y1[i])<0.2){
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


/**
 * @brief PagePath::myMouseReleaseEvent 配合移动或删除轨迹点
 * @param event
 */
void PagePath::myMouseReleaseEvent(QMouseEvent *event)
{
    m_point=-1;
}


/**
 * @brief PagePath::myMouseMoveEvent 配合移动或删除轨迹点
 * @param event
 */
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

    for(int i=0;i<=bezier_path[bezier_cnt].out_num;i++){
        if(fabs(x_val-x0[i])<0.2&&fabs(y_val-y0[i])<0.2 && !(event->button()&Qt::LeftButton)){
            QString str;
            str = QString("第%1个点\nx: %2\ny: %3").arg(QString::asprintf("%d",i+1)).arg(QString::asprintf("%.3f", x0[i]))
                    .arg(QString::asprintf("%.3f",y0[i]));
            qDebug()<<"i"<<i<<"x"<<x0[i]<<"y"<<y0[i];
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

    x0[x0_num]=x_val;
    y0[x0_num]=y_val;

    if(curve==1)
    {
        x1[m_point]=x_val;
        y1[m_point]=y_val;
    }
    else if(curve==0)
    {
        x[m_point]=x_val;
        y[m_point]=y_val;
    }

    bezier_path[bezier_cnt].out_points[x0_num].X=x_val;
    bezier_path[bezier_cnt].out_points[x0_num].Y=y_val;

    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, Qt::green, 8));
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(0)->setData(x, y);

    ui->customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::red, 2), QBrush(Qt::white), 8));
    ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(1)->setData(x1, y1);

    ui->customPlot->replot();

}


/**
 * @brief PagePath::on_actionScreen_triggered 删除点槽函数
 */
void PagePath::on_actionScreen_triggered()
{
    x0.remove(x0_num);
    y0.remove(x0_num);

    if(curve==0)
    {
        x.remove(n_point);
        y.remove(n_point);
    }
    else if(curve==1)
    {
        x1.remove(n_point);
        y1.remove(n_point);
    }

    for (int i=x0_num;i<bezier_path[bezier_cnt].out_num;i++)
    {
        bezier_path[bezier_cnt].out_points[i].X=bezier_path[bezier_cnt].out_points[i+1].X;
        bezier_path[bezier_cnt].out_points[i].Y=bezier_path[bezier_cnt].out_points[i+1].Y;
    }
    bezier_path[bezier_cnt].out_num-=1;

    ui->customPlot->graph(0)->setData(x, y);
    ui->customPlot->graph(1)->setData(x1, y1);
    ui->customPlot->replot();

    qDebug()<<"n_point"<<n_point<<"out_num"<<bezier_path[bezier_cnt].out_num;
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
    //    if (ui->Edit_x0->text().isEmpty())
    //    {
    //        QMessageBox::warning(NULL, "过程点数量不能为0", "请输入正确的过程点", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    //        return;
    //    }

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
    //        for(int i=0;i<bezier_path[bezier_cnt].input_num;i++)
    //        {
    //            bezier_path[bezier_cnt].input_points[i].X=bezier_path[bezier_cnt].input_points[i].X+ui->Edit_translate_dy->text().toFloat();
    //            bezier_path[bezier_cnt].input_points[i].Y=bezier_path[bezier_cnt].input_points[i].Y+ui->Edit_translate_dx->text().toFloat();
    //        }
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

    x0.resize(bezier_path[bezier_cnt].out_num+1);
    y0.resize(bezier_path[bezier_cnt].out_num+1);
    x.resize(bezier_path[bezier_cnt].out_num+1 - bezier_path[bezier_cnt].input_num);
    y.resize(bezier_path[bezier_cnt].out_num+1 - bezier_path[bezier_cnt].input_num);
    x1.resize(bezier_path[bezier_cnt].input_num);
    y1.resize(bezier_path[bezier_cnt].input_num);
    int num = 0;
    for (int j = 0; j <= bezier_path[bezier_cnt].out_num; j++)
    {
        if (j % bezier_path[bezier_cnt].num_btw_two == 0)
        {
            x1[num] = bezier_path[bezier_cnt].out_points[j].X;
            y1[num] = bezier_path[bezier_cnt].out_points[j].Y;
            num++;
        }
        else
        {
            x[j - num] = bezier_path[bezier_cnt].out_points[j].X;
            y[j - num] = bezier_path[bezier_cnt].out_points[j].Y;
        }
        x0[j]=bezier_path[bezier_cnt].out_points[j].X;
        y0[j]=bezier_path[bezier_cnt].out_points[j].Y;
    }
    qDebug()<<"input_num"<<bezier_path[bezier_cnt].input_num<<"out_num"<<bezier_path[bezier_cnt].out_num;

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


/**
 * @brief 点击“曲线对比”按钮
 *
 */
void PagePath::on_Button_cmp_clicked()
{
    mychart = new Mychart;
    mychart->show();
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
