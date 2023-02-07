#include "mychart.h"
#include "ui_mychart.h"
#include "pagepath.h"
#include <QChartView>

Mychart::Mychart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mychart)
{
    ui->setupUi(this);
    chart = new QChart;
    axis_x = new QValueAxis;
    axis_y = new QValueAxis;
    axis_x->setRange(-13,13);
    axis_y->setRange(-map_height,map_height);
    axis_x->setTickCount(27);
    axis_y->setTickCount(21);
    axis_x->setLabelFormat("%.2f");
    axis_y->setLabelFormat("%.2f");
    chart->addAxis(axis_y,Qt::AlignLeft);
    chart->addAxis(axis_x,Qt::AlignBottom);

    series_path = new QLineSeries;
    series_path->setPen(QPen(Qt::red,2,Qt::SolidLine));
    series_path->setName("规划曲线");
    for (int i = 0; i < bezier_path[bezier_cnt].out_num; i++)
    {
        series_path->append(bezier_path[bezier_cnt].out_points[i].X,
                           bezier_path[bezier_cnt].out_points[i].Y);
    }
    chart->addSeries(series_path);
    series_path->attachAxis(axis_x);
    series_path->attachAxis(axis_y);


    series_pos = new QLineSeries;
    series_pos->setPen(QPen(Qt::blue,2,Qt::SolidLine));
    series_pos->setName("实际曲线");
    for (int i = 0; i <= carpos_cnt; i++)
    {
        series_pos->append(carpos[i]);
    }
    chart->addSeries(series_pos);
    series_pos->attachAxis(axis_x);
    series_pos->attachAxis(axis_y);


    chart->setTitle("规划曲线-实际曲线比对");  // 设置图表的标题
    ui->graphicsView->setChart(chart);
    //ui->graphicsView->resize(400,300);
}

Mychart::~Mychart()
{
    delete ui;
}
