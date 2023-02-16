#ifndef MYGRAPHICS_H
#define MYGRAPHICS_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QLabel>

class MyGraphicsItem : public QGraphicsEllipseItem
{
private:
    QColor m_color;
public:
    MyGraphicsItem(QColor color,QGraphicsItem *parent = 0);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    int type() const;
};

// 自定义 Scene
class MyGraphicsScene : public QGraphicsScene
{
public:
    explicit MyGraphicsScene(QObject *parent);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

QPointF ret_rotate_point(float x,float y);
#endif // MYGRAPHICS_H
