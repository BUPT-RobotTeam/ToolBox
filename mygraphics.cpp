#include "mygraphics.h"
#include <cmath>
#include <pages/pagepath.h>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

int deletePoint=-1;
int selPoint=-1;


WayPtGraphicsItem::WayPtGraphicsItem(int type, QGraphicsItem *parent)
    : QObject(nullptr),QGraphicsEllipseItem(parent),pointType(type)
{

    editMenu = new QMenu(nullptr);
    switch (type) {
        case KEY_POINT:
            m_color = QColor("#F2A766");
            setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
            break;
        case WAY_POINT:
            m_color = QColor("#D9D9D9");
            transferAction = editMenu->addAction(tr("转为关键点"));

            break;
        default:
            break;
    }
    QPen p = pen();
    p.setWidth(6);
    p.setColor(m_color);
    setPen(p);
    setBrush(m_color);

    deleteAction = editMenu->addAction(tr("删除点"),[=](){remove();});
}

/**
 * @brief WayPtGraphicsItem::mousePressEvent 左键移动点
 * @param event
 */
void WayPtGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    if (event->button() == Qt::LeftButton)
    {
        setSelected(true);
        emit pointSelected(this->point_index);
//        if(selPoint==-1)
//        {
//            QPointF LeftButtonClickedPoint(ret_rotate_point(scenePos().x(),scenePos().y()));
//            for (int i=0;i<=bezier_path[bezier_cnt].out_num;i++)
//            {
//                if(fabs(bezier_path[bezier_cnt].out_points[i].X-LeftButtonClickedPoint.x())<0.01 && fabs(bezier_path[bezier_cnt].out_points[i].Y-LeftButtonClickedPoint.y())<0.01)
//                {
//                    selPoint=i;
//                    DO SOMETHING
//                    break;
//                }
//            }
//        }
    }
    else if (event->button() == Qt::RightButton)
    {
        editMenu->exec(QCursor::pos());
    }
}

void WayPtGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->pointType == KEY_POINT)
    {
        emit pointPosChanged(this->point_index,event->pos(),this->pointType);
    }
    QGraphicsItem::mouseMoveEvent(event);
}

/**
 * @brief WayPtGraphicsItem::mouseReleaseEvent 更新坐标点
 * @param event
 */
void WayPtGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    QString nowPointValue="";
//    nowPointValue=QString("第%1个点    x: %2,y: %3").arg(QString::asprintf("%d",selPoint))
//            .arg(QString::asprintf("%.3f", ret_rotate_point(scenePos().x(),scenePos().y()).x()))
//            .arg(QString::asprintf("%.3f", ret_rotate_point(scenePos().x(),scenePos().y()).y()));
//    nowPointValueLabel->setText(nowPointValue);
//    nowPointValueLabel->update();
    setSelected(false);
//    bezier_path[bezier_cnt].out_points[selPoint].X=ret_rotate_point(scenePos().x(),scenePos().y()).x();
//    bezier_path[bezier_cnt].out_points[selPoint].Y=ret_rotate_point(scenePos().x(),scenePos().y()).y();
    selPoint=-1;
    emit pointReleased(this->point_index);
    QGraphicsItem::mouseReleaseEvent(event);
}


int WayPtGraphicsItem::type() const
{
    return UserType + 1;
}

void WayPtGraphicsItem::setPointIndex(int pointIndex) {
    point_index = pointIndex;
}

void WayPtGraphicsItem::setPointTime(double pointTime) {
    point_time = pointTime;
}

void WayPtGraphicsItem::remove() {
    scene()->removeItem(this);
    emit deletePointItem(point_index,KEY_POINT);
    this->deleteLater();
}

// 自定义graphicView
TrajectoryPlotGraphicsView::TrajectoryPlotGraphicsView(QWidget *parent)
    : QGraphicsView(parent) {
    TrajectoryPlotGraphicsScene =  new QGraphicsScene(parent);
    this->setScene(TrajectoryPlotGraphicsScene);
}

/**
 * @brief TrajectoryPlotGraphicsView::mousePressEvent 右键删除点
 * @param event
 */
void TrajectoryPlotGraphicsView::mousePressEvent(QMouseEvent *event)
{

    QGraphicsView::mousePressEvent(event);
//    if (event->button() == Qt::RightButton) {
//        QGraphicsItem *itemToRemove = NULL;
//        foreach (QGraphicsItem *item, items(event->scenePos())) {
//            if (item->type() == QGraphicsItem::UserType+1) {
//                itemToRemove = item;
//                QPointF rightButtonClickedPoint(ret_rotate_point(itemToRemove->scenePos().x(),itemToRemove->scenePos().y()));
//                for (int i=0;i<=bezier_path[bezier_cnt].out_num;i++)
//                {
//                    if(fabs(bezier_path[bezier_cnt].out_points[i].X-rightButtonClickedPoint.x())<0.01 && fabs(bezier_path[bezier_cnt].out_points[i].Y-rightButtonClickedPoint.y())<0.01)
//                    {
//                        deletePoint=i;
//                        break;
//                    }
//                }
//            }
//        }
//        if (itemToRemove != NULL && deletePoint!=-1)
//        {
//            for(int i=deletePoint;i<bezier_path[bezier_cnt].out_num;i++)
//            {
//                bezier_path[bezier_cnt].out_points[i]=bezier_path[bezier_cnt].out_points[i+1];
//            }
//            bezier_path[bezier_cnt].out_num--;
//            removeItem(itemToRemove);
//            deletePoint=-1;
//        }
//    }
}

void TrajectoryPlotGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
};

/**
 * @brief ret_rotate_point 旋转坐标系换算函数
 * @param x
 * @param y
 * @return
 */
QPointF ret_rotate_point(float x,float y)
{
//    if(translate_dangle==0)
//    {
//        return QPointF((x/width_t-translate_dy)/toggle_x,(y/height_t-translate_dx)/toggle_y);
//    }
//    else
//    {
//        float x_val=(x/width_t-translate_dy)/toggle_x;
//        float y_val=(y/height_t-translate_dx)/toggle_y;
//        return  QPointF(x_val*cos(-translate_dangle * M_PI / 180.0) - y_val*sin(-translate_dangle * M_PI / 180.0),
//                        y_val*cos(-translate_dangle * M_PI / 180.0) + x_val*sin(-translate_dangle * M_PI / 180.0));
//    }
}


