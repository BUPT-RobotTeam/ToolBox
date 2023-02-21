#ifndef PAGEPATH_H
#define PAGEPATH_H

#include <QWidget>
#include "vescinterface.h"
#include "bezier.h"
#include <QStandardItemModel>
#include "txtdialog.h"
#include "trajectory_generator.h"
#include "spinboxDelegate.h"
#include <QLineEdit>
#include <mygraphics.h>
#include <QLabel>

namespace Ui {
class PagePath;
}



////extern float map_width;
////extern float map_height;
//extern Bezier *bezier_path ;
//extern int toggle_x;
//extern int toggle_y;
//extern double translate_dx;
//extern double translate_dy;
//extern double translate_dangle;
//extern double width_t;
//extern double height_t;
//extern int bezier_cnt;
////extern int traj_num;
////extern int traj_Edit_idx;
////extern QPointF *carpos;
////extern int carpos_cnt;

struct CtrlCmd_s{
    CtrlCmd_s(const QPointF &pos,
              const QPointF &vel,
              double speed,
              double dir,
              double angle,
              double time)
              : pos(pos),
             vel(vel),
             speed(speed),
             dir(dir),
             angle(angle),
             time(time) {};

    QPointF pos{},vel{};
    double speed{},dir{},angle{};
    double time{};
};

class PagePath : public QWidget
{
    Q_OBJECT

public:
    explicit PagePath(QWidget *parent = 0);
    ~PagePath();

    VescInterface *vesc() const;
    void setVesc(VescInterface *vesc);
    void init_table_out();
    void init_table_input();
    void table_update();
    void point_rotate(QVector<double> *x,QVector<double> *y, double angle);



private slots:

//    void on_Button_bezier_num_clicked();
    void scenePointSelected(int idx);

    void scenePointReleased(int idx);

    void scenePointDeleted(int idx);

    void scenePointPosChanged(int idx,QPointF nowPos,int type);




    void on_Button_load_path_clicked();

//    void on_Button_add_bezier_clicked();

    void on_Button_create_path_clicked();

    void on_Button_create_file_clicked();

    void on_Button_clear_clicked();

    void on_Button_open_folder_clicked();

    void on_Button_load_img_clicked();

    void drawCarPos(float x, float y);

    //    void on_Button_cmp_clicked();

    void on_Button_add_point_clicked();

    void on_Button_delete_point_clicked();

    void on_Sampple_time_clicked(bool checked);

    void on_Sample_distance_clicked(bool checked);

    void on_Button_update_point_clicked();

private:

    Ui::PagePath *ui;
    int buttonLoadPathClickedNum;
    QVector<QPointF> input_ptsList;
    // 按段存储
    QVector< QVector<CtrlCmd_s> >generated_ptsSegList{1};
    int segment_num{0},generated_ptsNnum{0};
    int inputPoint_num {0};
    int selKeyPtIdx{-1};
    QVector< WayPtGraphicsItem* > plotWayPt;
    QVector<double> x_all_pts{5},y_all_pts{5};
    txtDialog *txtdialog;
    VescInterface *mVesc;
    QStandardItemModel *outputModel , *inputModel;
    QStandardItem *aItem;
    QImage *img;
    QImage *newImg;
    QLineEdit *point;
    QLabel *xy;
    QLayout *point_line;
    QSharedPointer<AbstractTrajGenerator>  traj_generator;
    TrajectoryPlotGraphicsView *trajPlotView;
    SpinBoxDelegate * xDelegate,*yDelegate,*genNumDelegate;
    void showEvent(QShowEvent *event) override;
    void addKeypt();



};
QPointF cal_rotate_point(double x, double y, double dangle, double dx, double dy, int toggle_x, int toggle_y, double w,
                         double h);
#endif // PAGEPATH_H

