#ifndef BEZIER_H
#define BEZIER_H

typedef struct
{
    float X;
    float Y;
} PointF;

class Bezier
{
public:
    int input_num;
    int num_btw_two;
    int out_num=0;
    int max_speed;
    int k_speed;
    float now_angle;
    float target_angle;
    PointF input_points[10];
    PointF out_points[500];
    PointF ctrl_points[500];
    int speed[500];
    float direct[500];
    float angle[500];
    float length;

    /*贝塞尔曲线的主要函数*/

    /*第一步根据输入的过程点生成控制点*/
    void ctrlpoints_get();

    /*第二步就可以根据输入的过程点和控制点生成贝塞尔曲线，获得输出点*/
    void outpoints_get();

    /*曲线速度规划函数*/
    void speed_planning();

    /*直线速度规划函数*/
    void strghtline_speed_plan();

    /*计算曲线的长度*/
    void calculate_length();

    /*速度方向规划函数*/
    void direct_planning();

    /*机器人姿态角规划函数*/
    void angle_planning();

    /*辅助函数*/

    /*获得贝塞尔曲线中的一个输出点，t（0~1）为系数*/
    PointF bezier_point_get(PointF start_point, PointF end_point, PointF ctr_point_1, PointF ctr_point_2, double t, int bezier_rank);

    /*计算两点间距*/
    float dis_btw_points(PointF P1, PointF P2);

    /*计算曲率*/
    float calculate_curvity(PointF P1, PointF P2, PointF P3);
};

/*float dis_btw_points(PointF P1,PointF P2);//计算两点间距
PointF *outpoints_get(PointF input_points[],PointF ctrl_points[],PointF out_points[],int input_num,int num_btw_two);
PointF bezier_points_get(PointF *start_point,PointF *end_point,PointF *ctr_point_1,PointF *ctr_point_2,double t,int bezier_rank);
PointF *ctrlpoints_get(PointF* points,int point_number);//传入路径上控制点数组和个数
float calculate_curvity(PointF P1 , PointF P2 , PointF P3);
void speed_planning(PointF *out_points, int point_number, int max_speed, int *out_speed, int k_speed);
void strghtline_speed_plan(PointF *out_points, int point_number, int max_speed, int *out_speed, int k_speed);
float calculate_length(PointF *out_points, int out_num);
float *direct_planning(PointF *out_points, float *bezier_direct, int out_num);
void angle_planning(float *bezier_angle, float now_angle, float target_angle, int out_num);*/

#endif // BEZIER_H
