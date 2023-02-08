#ifndef PAGEPATH_H
#define PAGEPATH_H

#include <QWidget>
#include "vescinterface.h"
#include "bezier.h"
#include <QStandardItemModel>
#include "txtdialog.h"
#include "bezier_label.h"
#include "mychart.h"
#include <QLineEdit>

namespace Ui {
class PagePath;
}

extern float map_width;
extern float map_height;
extern float map_width_pixel;
extern float map_height_pixel;
extern double translate_dx;
extern double translate_dy;
extern double translate_dangle;
extern Bezier *bezier_path;
extern int bezier_num;
extern int bezier_cnt;
extern int toggle_x;
extern int toggle_y;
extern QPointF *carpos;
extern int carpos_cnt;
extern float width_t;
extern float height_t;

class PagePath : public QWidget
{
    Q_OBJECT

public:
    explicit PagePath(QWidget *parent = 0);
    ~PagePath();

    VescInterface *vesc() const;
    void setVesc(VescInterface *vesc);
    void init_table_out();
    void table_update();


public slots:
    void myMousePressEvent(QMouseEvent *event);
    void myMouseReleaseEvent(QMouseEvent *event);
    void myMouseMoveEvent(QMouseEvent *event);

private slots:

    void on_Button_bezier_num_clicked();

    void on_Button_load_path_clicked();

    void on_Button_add_bezier_clicked();

    void on_Button_create_path_clicked();

    void on_Button_create_file_clicked();

    void on_Button_clear_clicked();

    void on_Button_open_folder_clicked();

    void on_Button_load_img_clicked();

    void drawpos(float x, float y);

    void on_Button_cmp_clicked();

    void on_Button_add_point_clicked();

    void on_Button_delete_point_clicked();

    void on_actionScreen_triggered();

    void on_Sampple_time_clicked(bool checked);

    void on_Sample_distance_clicked(bool checked);

    void on_Button_update_point_clicked();

private:
    Ui::PagePath *ui;
    QVector<double> x0,y0;
    QVector<double> x, y;
    QVector<double> x1, y1;
    txtDialog *txtdialog;
    VescInterface *mVesc;
    QStandardItemModel *model;
    QStandardItem *aItem;
    Bezier_Label *bezier_label;
    QImage *img;
    QImage *newImg;
    Mychart *mychart;
    QLineEdit *point;
    QLabel *xy;
    QLayout *point_line;
    QAction *actionScreen;
};

#endif // PAGEPATH_H

