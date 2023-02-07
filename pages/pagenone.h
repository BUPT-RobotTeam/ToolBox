#ifndef PAGENONE_H
#define PAGENONE_H

#include <QWidget>
#include "vescinterface.h"

namespace Ui {
class PageNone;
}

class PageNone : public QWidget
{
    Q_OBJECT

public:
    explicit PageNone(QWidget *parent = 0);
    ~PageNone();

    VescInterface *vesc() const;
    void setVesc(VescInterface *vesc);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::PageNone *ui;
    VescInterface *mVesc;
    int clientID;
};

#endif // PAGENONE_H
