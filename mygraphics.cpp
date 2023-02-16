#include "mygraphics.h"
#include <cmath>
#include <pages/pagepath.h>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

int deletePoint=-1;
int selPoint=-1;
QString nowPointValue="";

MyGraphicsItem::MyGraphicsItem(QColor color,QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent),m_color(color)
{
    QPen p = pen();
    p.setWidth(6);
    p.setColor(m_color);
    setPen(p);
    setBrush(m_color);
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}

/**
 * @brief MyGraphicsItem::mousePressEvent 左键移动点
 * @param event
 */
void MyGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    if (event->button() == Qt::LeftButton)
    {
        setSelected(true);
        if(selPoint==-1)
        {
            QPointF LeftButtonClickedPoint(ret_rotate_point(scenePos().x(),scenePos().y()));
            for (int i=0;i<=bezier_path[bezier_cnt].out_num;i++)
            {
                if(fabs(bezier_path[bezier_cnt].out_points[i].X-LeftButtonClickedPoint.x())<0.01 && fabs(bezier_path[bezier_cnt].out_points[i].Y-LeftButtonClickedPoint.y())<0.01)
                {
                    selPoint=i;
                    nowPointValue=QString("第%1个点    x: %2,y: %3").arg(QString::asprintf("%d",selPoint))
                            .arg(QString::asprintf("%.3f", bezier_path[bezier_cnt].out_points[selPoint].X))
                            .arg(QString::asprintf("%.3f", bezier_path[bezier_cnt].out_points[selPoint].Y));
                    nowPointValueLabel->setText(nowPointValue);
                    nowPointValueLabel->update();
                    break;
                }
            }
        }
    }
}

void MyGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
}

/**
 * @brief MyGraphicsItem::mouseReleaseEvent 更新坐标点
 * @param event
 */
void MyGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    nowPointValue=QString("第%1个点    x: %2,y: %3").arg(QString::asprintf("%d",selPoint))
            .arg(QString::asprintf("%.3f", ret_rotate_point(scenePos().x(),scenePos().y()).x()))
            .arg(QString::asprintf("%.3f", ret_rotate_point(scenePos().x(),scenePos().y()).y()));
    nowPointValueLabel->setText(nowPointValue);
    nowPointValueLabel->update();
    setSelected(false);
    bezier_path[bezier_cnt].out_points[selPoint].X=ret_rotate_point(scenePos().x(),scenePos().y()).x();
    bezier_path[bezier_cnt].out_points[selPoint].Y=ret_rotate_point(scenePos().x(),scenePos().y()).y();
    selPoint=-1;
    QGraphicsItem::mouseReleaseEvent(event);
}


int MyGraphicsItem::type() const
{
    return UserType + 1;
}

// 自定义scene
MyGraphicsScene::MyGraphicsScene(QObject *parent)
    : QGraphicsScene(parent) {
}

/**
 * @brief MyGraphicsScene::mousePressEvent 右键删除点
 * @param event
 */
void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<width()<<height();
    QGraphicsScene::mousePressEvent(event);
    if (event->button() == Qt::RightButton) {
        QGraphicsItem *itemToRemove = NULL;
        foreach (QGraphicsItem *item, items(event->scenePos())) {
            if (item->type() == QGraphicsItem::UserType+1) {
                itemToRemove = item;
                QPointF rightButtonClickedPoint(ret_rotate_point(itemToRemove->scenePos().x(),itemToRemove->scenePos().y()));
                for (int i=0;i<=bezier_path[bezier_cnt].out_num;i++)
                {
                    if(fabs(bezier_path[bezier_cnt].out_points[i].X-rightButtonClickedPoint.x())<0.01 && fabs(bezier_path[bezier_cnt].out_points[i].Y-rightButtonClickedPoint.y())<0.01)
                    {
                        deletePoint=i;
                        break;
                    }
                }
            }
        }
        if (itemToRemove != NULL && deletePoint!=-1)
        {
            for(int i=deletePoint;i<bezier_path[bezier_cnt].out_num;i++)
            {
                bezier_path[bezier_cnt].out_points[i]=bezier_path[bezier_cnt].out_points[i+1];
            }
            bezier_path[bezier_cnt].out_num--;
            removeItem(itemToRemove);
            deletePoint=-1;
        }
    }
}

void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
};

/**
 * @brief ret_rotate_point 旋转坐标系换算函数
 * @param x
 * @param y
 * @return
 */
QPointF ret_rotate_point(float x,float y)
{
    if(translate_dangle==0)
    {
        return QPointF((x/width_t-translate_dy)/toggle_x,(y/height_t-translate_dx)/toggle_y);
    }
    else
    {
        float x_val=(x/width_t-translate_dy)/toggle_x;
        float y_val=(y/height_t-translate_dx)/toggle_y;
        return  QPointF(x_val*cos(-translate_dangle * M_PI / 180.0) - y_val*sin(-translate_dangle * M_PI / 180.0),
                        y_val*cos(-translate_dangle * M_PI / 180.0) + x_val*sin(-translate_dangle * M_PI / 180.0));
    }
}


