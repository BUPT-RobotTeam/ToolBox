#ifndef MYGRAPHICS_H
#define MYGRAPHICS_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QVector>
#include <QVector3D>
#include <QSharedPointer>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
class WayPtGraphicsItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    WayPtGraphicsItem(int type, QGraphicsItem *parent = 0);
    WayPtGraphicsItem(QColor color, QGraphicsItem *parent = 0);
    void setPointIndex(int pointIndex);
    void setKeyIndex(int keyIndex);
    void setPointTime(double pointTime);
    void remove();
    int getPointType() const;
    enum {KEY_POINT,WAY_POINT};

signals:
    void deletePointItem(int idx,int keyIdx);
    void pointPosChanged(int idx,QPointF nowPos,int keyIdx);
    void pointSelected(int idx,int keyIdx);
    void pointReleased(int idx,int keyIdx);

public slots:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    int type() const override;

private:
    QColor m_color;
    //全局列表索引
    int global_index{-1};
    //点类型
    int pointType{};
    //关键点列表索引
    int key_index{-1};
    double point_time{};
    QAction *deleteAction,*transferAction ;
    QMenu *editMenu ;


//    NewAction = fileMenu->addAction("增加IP地址");
//    InsertAction = fileMenu->addAction("插入IP地址");
//    DeleteAction = fileMenu->addAction("删除IP地址");
};

// 自定义 Scene
class TrajectoryPlotGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TrajectoryPlotGraphicsView(QWidget *parent);
//    QVector<WayPtGraphicsItem *> plotPoint(QVector<QPointF> plotKeyPt,QVector<QPointF> plotWayPt);
//    WayPtGraphicsItem * plotPoint(QPointF polopt);
    QGraphicsScene* TrajectoryPlotGraphicsScene;


//    void removept(WayPtGraphicsItem*);
signals:
    void addedPt(WayPtGraphicsItem *);

protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;


};

QPointF ret_rotate_point(float x,float y);
#endif // MYGRAPHICS_H
