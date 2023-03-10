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
#include <QAbstractButton>

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
/**
 * @brief 控制变量结构体，包括二维角度、速度、朝向、角度、时间
 * @todo 应该用eigen存储pos和vel的。
 */
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

/**
 * @brief 路径规划页面实现
 */

class PagePath : public QWidget
{
    Q_OBJECT

public:
    /**
     *
     * @param parent
     */
    explicit PagePath(QWidget *parent = 0);
    /**
     *
     */
    ~PagePath();
    /**
     * @brief 获取vesc接口，但是暂时无用
     * @return VescInterface
     */
    VescInterface *vesc() const;
    /**
     * @brief 设置vesc接口，暂时无用
     * @param vesc
     */
    void setVesc(VescInterface *vesc);
    /**
     * @brief 初始化输出表
     * 清空表格、输出表头、设置列宽等表格显示初始化\n
     * 设置单行，单元素选择\n
     * 断开信号，删除菜单。并重新连接右键菜单信号，设置删除键信号\n
     * 删除键槽函数用lambda匿名函数编写，获取下标，并调用remove函数
     */
    void init_table_out();
    /**
     * @brief 初始化输入表
     * 清空表格、输出表头、设置列宽等表格显示初始化\n
     * 设置单行，单元素选择\n
     * 断开信号，删除菜单。并重新连接右键菜单信号，设置删除键、数值改变信号\n
     * 删除键槽函数用lambda匿名函数编写，获取下标，并调用remove函数
     */
    void init_table_input();
    /**
     * @brief 将item写入model指定位置。未生成的时候不会有任何行为。
     */
    void table_update();
    /**
     *  @brief 未启用
     * @param x
     * @param y
     * @param angle
     */
    void point_rotate(QVector<double> *x,QVector<double> *y, double angle);



private slots:

//    void on_Button_bezier_num_clicked();
    /**
     * @brief 场景点被选中信号接受槽函数
     * 根据下标设定选择点，反向解出小车坐标系坐标后在nowPoint的label上显示信息。\n
     * 目前连接到WayPtGraphicsItem的信号中
     * @param idx waypt里面的下标
     * @param keyIdx keypt的下标
     * @see plotWayPt
     * @see plotKeyPt
     */
    void scenePointSelected(int idx,int keyIdx);
    /**
     * @brief 场景点被鼠标释放信号接受槽函数（暂时不启用）
     * @param idx waypt里面的下标
     * @param keyIdx keypt的下标
     */
    void scenePointReleased(int idx,int keyIdx);
    /**
     * @brief 场景点被删除信号接受槽函数
     * 目前只会调用removePt函数，和自定义WayPtGraphicsItem的删除按键信号连接。
     * @param idx waypt里面的下标
     * @param keyIdx keypt的下标
     */
    void scenePointDeleted(int idx,int keyIdx);
    /**
     * @brief 场景点被移动信号接受槽函数
     * 根据下标设定选择点，反向解出小车坐标系坐标后在nowPoint的label上显示信息。
     * 同时更新输入表\n
     * 目前连接到WayPtGraphicsItem的信号中
     * @param idx
     * @param nowPos 暂时没用
     * @param keyIdx
     */
    void scenePointPosChanged(int idx,QPointF nowPos,int keyIdx);
    /**
     * @brief 输入表单元格被修改槽函数
     * 根据表格所在行更新对应关键点的位置
     * 注意，data是QVariant，要判断是否可以转换成double
     * @param item
     */
    void inputModelChanged(QStandardItem * item);


//    void on_Button_add_bezier_clicked();
    /**
     * @brief 点击“确定”按钮，开始规划轨迹
     *
     */
    void on_Button_create_path_clicked();
    /**
     * @brief 点击“生成文件”按钮
     *
     */
    void on_Button_create_file_clicked();
    /**
     * @brief 点击“清空”按钮
     *
     */
    void on_Button_clear_clicked();
    /**
     * @brief 点击“选择文件保存路径”图标
     *
     */
    void on_Button_open_folder_clicked();
    /**
     * @brief 点击“选择图片”图标
     *
     */
    void on_Button_load_img_clicked();

    //    void on_Button_cmp_clicked();
    /**
     * @brief PagePath::on_Button_add_point_clicked 点击“加点”按钮
     */
    void on_Button_add_point_clicked();
    /**
    * @brief   点击删点按钮
    */
    void on_Button_delete_point_clicked();

    void on_table_output_CustomContextMenuRequested(QPoint pos);

    void on_table_input_CustomContextMenuRequested(QPoint pos);
     /**
      * outputMode按钮变化槽函数
      * @param button
      */
    void on_outputModeSelChanged(QAbstractButton *button);

private://变量
    enum outputMode_enum{POINT_NUM,TIMEINTERVAL};
    outputMode_enum sampleMode=POINT_NUM ;
    Ui::PagePath *ui;
    int buttonLoadPathClickedNum; ///<判断是否已经打印了轨迹
    QVector<QPointF> input_ptsList; ///<存储输入点
    // 按段存储
    QVector< QVector<CtrlCmd_s> >generated_ptsSegList{1}; ///<存储生成的点
    int segment_num{0}, ///<段数量
        generated_ptsNnum{0}; ///<生成点数量
    int inputPoint_num {0}; ///<输入点数量
    QVector< WayPtGraphicsItem* > plotWayPt/**存储点item指针*/,plotKeyPt; ///<存储点item指针
    txtDialog *txtdialog;///<
    VescInterface *mVesc;///<

    QStandardItemModel *outputModel , *inputModel;
    QStandardItem *aItem;///<
    QImage *img;
    QImage *newImg;
    QLineEdit *point;
    QSharedPointer<AbstractTrajGenerator>  traj_generator;///< 轨迹生成类，智能指针会自动析构
    TrajectoryPlotGraphicsView *trajPlotView;///< 点打印的视图
    SpinBoxDelegate * xDelegate,///< 输入表格代理,
                    *yDelegate, ///< 输入表格代理
                    *genNumDelegate; ///< 输入表格代理
    QGraphicsItem   *xAxisArrowItem/**x轴箭头item指针*/, *yAxisArrowItem,///< y轴箭头item指针
                    *xAxisPathItem/**x轴字符item指针*/,*yAxisPathItem,///< y轴字符item指针
                    *xAxisLineItem/**x轴item指针*/,*yAxisLineItem;///< y轴item指针

    QMenu *input_view_Menu{nullptr} ,///<input_view右键菜单，设为空指针可以进行delete而不报错。
        *output_view_Menu{nullptr};///<output_view右键菜单，设为空指针可以进行delete而不报错。
private: //function
    /**
     * @brief 窗口显示事件
     * @param event
     */
    void showEvent(QShowEvent *event) override;
    /**
     * @brief 添加关键点
     */
    void addKeypt();
    /**
     * @brief 删除场景里的非关键点
     */
    void clearWayPt();
    /**
     * @brief 绘制axis对象；
     */
    void draw_axis();
    /**
     * @brief 删除axis对象
     */
    void clear_axis();
    /**
     * @brief 删除点函数
     * @param wayidx 路径点下标，还未生成是-1
     * @param keyidx 关键点下标，不是关键点是-1
     */
    void removePt(int wayidx, int keyidx);
    /**
     * @brief 遍历数组更新关键点和路径点下标
     */
    void updatePlotIdx();
    /**
     * @brief 打印曲线点，只会被确定键按下时事件调用。在轨迹生成后用来打印点。
     *
     */
    void plotTrajectory();
    /**
     * @brief 场景初始化
     */
    void plotScene_init();
    /**
     * @brief 清空轨迹点元数据。
     */
    void clear_trajectory();
    /**
     * @brief 获取坐标换算
     */
    void get_coordTranslate() const;

    void sampleTrajByPtNum(double traj_time_final, double traj_time_now, const QVector<int> &samplePtNum_btw_wayPt);

    void sampleTrajByTime(double traj_time_now, double time_interval);
};
QPointF cal_rotate_point(double x, double y, double dangle, double dx, double dy, int toggle_x, int toggle_y, double w,
                         double h);
QPointF ret_rotate_point(double x,double y,double dangle,double dx,double dy,
                         int toggle_x,int toggle_y,double w,double h);
#endif // PAGEPATH_H

