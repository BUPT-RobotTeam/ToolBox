/**
 * @authors liny2 Cameliass
 * @brief 自定义图像场景和图形对象，用于显示、拖动关键点和路径点。
 */
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
/**
 * @brief 自定义图形对象，用于显示关键点
 *
 */
class WayPtGraphicsItem : public QObject, public QGraphicsEllipseItem
{

    Q_OBJECT
public:
    /**
     * @brief 构造函数，指定点类型。
     * @param type 关键点或路径点 \n
     * @refitem WayPtGraphicsItem::KEY_POINT 关键点 \n
     * @refitem WayPtGraphicsItem::WAY_POINT 路径点
     * @param parent 父亲图形对象，实际使用传个nullptr就行
     *
     */
    WayPtGraphicsItem(int type, QGraphicsItem *parent = 0);
    /**
     * 已经弃用
     * @param color
     * @param parent
     * @see WayPtGraphicsItem(int type, QGraphicsItem *parent = 0);
     */
    WayPtGraphicsItem(QColor color, QGraphicsItem *parent = 0);
    /**
     * @brief 用于指定点在waypoint列表的idx，未生成轨迹为-1
     * @param pointIndex 下标
     * @refitem PagePath::plotWayPt
     * @refitem PagePath::plotKeyPt;
     */
    void setPointIndex(int pointIndex);
    /**
     * @brief 用于指定点在keypoint列表的idx，不是keypoint为-1
     * @param keyIndex
     * @see PagePath::plotWayPt
     * @see PagePath::plotKeyPt;
     */
    void setKeyIndex(int keyIndex);
    /**
     * 暂时不使用
     * @param pointTime
     */
    void setPointTime(double pointTime);
    /**
     * @brief 用于在删除点之前进行一些操作
     * @details 目前只会发送信号 deletePointItem(int idx,int keyIdx);\n
     * @see deletePointItem(int idx,int keyIdx);
     */
    void remove();
    /**
     * @brief 获取点的类型
     * @return int 点类型
     * @refitem WayPtGraphicsItem::KEY_POINT 关键点 \n
     * @refitem WayPtGraphicsItem::WAY_POINT 路径点
     */
    int getPointType() const;
    /**
     * @brief 获取路径点下标，未生成点为-1
     * @return int，下标
     */
    int getPointIndex() const;
    /**
     * @brief 获取关键点下标，不是关键点为-1
     * @return int，下标
     */
    int getKeyIndex() const;

    enum {KEY_POINT,WAY_POINT};

signals:
    void deletePointItem(int idx,int keyIdx);
    void pointPosChanged(int idx,QPointF nowPos,int keyIdx);
    void pointSelected(int idx,int keyIdx);
    void pointReleased(int idx,int keyIdx);

public slots:

protected:
    /**
    * @brief WayPtGraphicsItem::mousePressEvent 点击选中点，重载父类QGraphicsEllipseItem的函数\n
    * 右键会弹出删除点菜单
    * @details 为了防止点击后快速再次点击造成的点漂移，判断鼠标位置是否在item中，否则 setSelected(false)
    * @param event
    */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    /**
     * @brief WayPtGraphicsItem::mouseMoveEvent 左键移动点，重载父类QGraphicsEllipseItem的函数
     * @param event
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    /**
     * @brief WayPtGraphicsItem::mouseMoveEvent 松开点，重载父类QGraphicsEllipseItem的函数
     * @param event
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    int type() const override;

private:
    QColor m_color;///< 点颜色
    int global_index{-1};///<全局列表索引
    int pointType{};///<点类型
    int key_index{-1};///<关键点列表索引
    double point_time{};///<点在轨迹上对应的时刻
    QAction *deleteAction,///<菜单项，删除
    *transferAction;///<菜单项，转为关键点，暂时没用;
    QMenu *editMenu ;///<右键菜单;



};

/**
 * 自定义 GraphicsView用于显示点
 */
class TrajectoryPlotGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    /**
     * 构造函数，会将 TrajectoryPlotGraphicsScene 置入view
     * @param parent 页面
     */
    explicit TrajectoryPlotGraphicsView(QWidget *parent);
//    QVector<WayPtGraphicsItem *> plotPoint(QVector<QPointF> plotKeyPt,QVector<QPointF> plotWayPt);
//    WayPtGraphicsItem * plotPoint(QPointF polopt);
    QGraphicsScene* TrajectoryPlotGraphicsScene;///<默认场景


//    void removept(WayPtGraphicsItem*);
signals:
    /**
     * 暂时无用
     */
    void addedPt(WayPtGraphicsItem *);

protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    /**
     * 暂时未真正重载
     * @param event
     */
    void mousePressEvent(QMouseEvent *event) override;
    /**
     * 暂时未真正重载
     * @param event
     */
    void mouseMoveEvent(QMouseEvent *event) override;


};

#endif // MYGRAPHICS_H
