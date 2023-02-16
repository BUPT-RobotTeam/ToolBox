#ifndef PAGEPATH_H
#define PAGEPATH_H

#include <QWidget>
#include "vescinterface.h"
#include "bezier.h"
#include <QStandardItemModel>
#include "txtdialog.h"
#include "trajectory_generator.h"
#include <QLineEdit>
#include <QLabel>

namespace Ui {
class PagePath;
}



//extern float map_width;
//extern float map_height;
//extern Bezier *bezier_path ;
//extern int traj_num;
//extern int traj_Edit_idx;
//extern QPointF *carpos;
//extern int carpos_cnt;
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


//public slots:
//    void myMousePressEvent(QMouseEvent *event);
//    void myMouseReleaseEvent(QMouseEvent *event);
//    void myMouseMoveEvent(QMouseEvent *event);

private slots:

    void on_Button_bezier_num_clicked();

    void on_Button_load_path_clicked();

    void on_Button_add_bezier_clicked();

    void on_Button_create_path_clicked();

    void on_Button_create_file_clicked();

    void on_Button_clear_clicked();

    void on_Button_open_folder_clicked();

    void on_Button_load_img_clicked();

    void drawCarPos(float x, float y);

//    void on_Button_cmp_clicked();

    void on_Button_add_point_clicked();

    void on_Button_delete_point_clicked();

    void on_actionScreen_triggered();

    void on_Sampple_time_clicked(bool checked);

    void on_Sample_distance_clicked(bool checked);

    void on_Button_update_point_clicked();

private:
    Ui::PagePath *ui;
    QVector< QVector<QPointF> > input_ptsList{1},generated_ptsList{1};
    QVector< QVector<double> > generated_angleList{1},generated_speedList{1},generated_dirList{1};
    QVector<double> x_all_pts{5},y_all_pts{5};
    QVector<double> x_inserted_pts, y_inserted_pts;
    QVector<double> x_input_pts, y_input_pts;
    txtDialog *txtdialog;
    VescInterface *mVesc;
    QStandardItemModel *model;
    QStandardItem *aItem;
    QImage *img;
    QImage *newImg;
    QLineEdit *point;
    QLabel *xy;
    QLayout *point_line;
    QAction *actionScreen;
    QVector<QSharedPointer<AbstractTrajGenerator> > traj_generators;
//    QPushButton *pushButton;
};

#endif // PAGEPATH_H

