#ifndef BEZIER_LABEL_H
#define BEZIER_LABEL_H

#include <QLabel>

class Bezier_Label : public QLabel
{
    Q_OBJECT

public:
    Bezier_Label(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // BEZIER_LABEL_H
