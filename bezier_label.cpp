/*****************************************************************************
Copyright: 2019/2/18 北京邮电大学机器人队
File name: bezier_label.cpp
Description: 贝塞尔曲线生成相应函数
Author: ZH
Version: 2.0
Date: 2020/2/18
History: 2020/2/18
*****************************************************************************/

#include "bezier_label.h"
#include <QPainter>
#include "pages/pagepath.h"

Bezier_Label::Bezier_Label(QWidget *parent) : QLabel(parent)
{
}

void Bezier_Label::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    QPainter bezier_painter;
    bezier_painter.begin(this);

    QFont font("宋体", 15, QFont::Bold, true);
    bezier_painter.setFont(font);
    bezier_painter.setPen(QPen(Qt::blue, 6, Qt::SolidLine, Qt::SquareCap));

    float width_t = map_width_pixel / map_width;
    float height_t = map_height_pixel / map_height;

    /*平移、旋转坐标系*/
    bezier_painter.translate(translate_dx * width_t, translate_dy * height_t);
    bezier_painter.rotate(translate_dangle);

    /*画坐标系*/
    bezier_painter.drawLine(0, 3 * toggle_y, -map_width_pixel / 4 * toggle_x, 3 * toggle_y);
    bezier_painter.drawLine(-3 * toggle_x, 0, -3 * toggle_x, map_height_pixel / 4 * toggle_y);

    /*画箭头*/
    bezier_painter.setPen(QPen(Qt::blue, 2, Qt::SolidLine, Qt::SquareCap));
    QPointF polygon_y[3] = {QPointF(2 * toggle_x, map_height_pixel / 4 * toggle_y),
                            QPointF(-8 * toggle_x, map_height_pixel / 4 * toggle_y),
                            QPointF(-3 * toggle_x, (map_height_pixel / 4 + 5) * toggle_y)};
    bezier_painter.drawPolygon(polygon_y, 3);
    bezier_painter.drawText(-30 * toggle_x, map_height_pixel / 4 * toggle_y, "y");
    QPointF polygon_x[3] = {QPointF(-map_width_pixel / 4 * toggle_x, 8 * toggle_y),
                            QPointF(-map_width_pixel / 4 * toggle_x, -2 * toggle_y),
                            QPointF((-map_width_pixel / 4 - 5) * toggle_x, 3 * toggle_y)};
    bezier_painter.drawPolygon(polygon_x, 3);
    bezier_painter.drawText(-map_width_pixel / 4 * toggle_x, 25 * toggle_y, "x");

    bezier_painter.setPen(QPen(Qt::red, 4, Qt::SolidLine, Qt::RoundCap));
    /*画过程点*/
    for (int i = 0; i <= bezier_cnt; i++)
    {
        for (int j = 0; j <= bezier_path[bezier_cnt].out_num; j++)
        {
            bezier_painter.drawPoint(QPointF(-bezier_path[bezier_cnt].out_points[j].X * width_t * toggle_x,
                                             bezier_path[bezier_cnt].out_points[j].Y * height_t * toggle_y));
        }
    }

    /*画小车的实际坐标点*/
    bezier_painter.setPen(QPen(Qt::blue, 4, Qt::SolidLine, Qt::SquareCap));
    for (int i = 0; i <= carpos_cnt; i++)
    {
        bezier_painter.drawPoint(carpos[i]);
    }
    bezier_painter.end();
}
