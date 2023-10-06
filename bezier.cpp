/*****************************************************************************
Copyright: 2019/2/18 北京邮电大学机器人队
File name: bezier.cpp
Description: 贝塞尔曲线生成相应函数
Author: ZH
Version: 2.0
Date: 2020/2/18
History: 2019.6.6、2020/2/18
*****************************************************************************/

#include "math.h"
#include "bezier.h"

#define PI 3.14159265

/***************************************************************
  *  @brief     贝塞尔曲线产生辅助点
  *  @param     * points传入路径上控制点数组
  *  @note      理解不了的话参加知乎专栏贝塞尔曲线了解下原理先
  *  @Sample usage
  *  @author    ZH
  *  @edit      2020/2/16
 **************************************************************/
void Bezier::ctrlpoints_get() //传入路径上控制点数组和个数
{
    PointF p1, p2, p3;
    float l1, l2, K;
    for (int i = 0; i < (input_num - 2); i++)
    {
        p1.X = (input_points[i].X + input_points[i + 1].X) / 2;
        p1.Y = (input_points[i].Y + input_points[i + 1].Y) / 2;
        p2.X = (input_points[i + 1].X + input_points[i + 2].X) / 2;
        p2.Y = (input_points[i + 1].Y + input_points[i + 2].Y) / 2; //

        l1 = dis_btw_points(input_points[i], input_points[i + 1]);
        l2 = dis_btw_points(input_points[i + 1], input_points[i + 2]);

        p3.X = (l1 * p2.X + l2 * p1.X) / (l1 + l2);
        p3.Y = (l1 * p2.Y + l2 * p1.Y) / (l1 + l2);

        K = 1; //决定贝塞尔曲线的圆度

        ctrl_points[2 * i].X = (p1.X - p3.X) * K + input_points[i + 1].X;
        ctrl_points[2 * i].Y = (p1.Y - p3.Y) * K + input_points[i + 1].Y;
        ctrl_points[2 * i + 1].X = (p2.X - p3.X) * K + input_points[i + 1].X;
        ctrl_points[2 * i + 1].Y = (p2.Y - p3.Y) * K + input_points[i + 1].Y;
    }
}

/***************************************************************
  *  @brief     贝塞尔曲线产生一个输出点
  *  @param     起点：start_point；终点：end_point；控制点1,2：ctr_point_1,2；t为系数；bezier_rank:贝塞尔阶数
  *  @note      建议先百度贝塞尔曲线了解原理
  *  @Sample usage
  *  @author    ZH
  *  @edit      2020/2/16
 **************************************************************/
PointF Bezier::bezier_point_get(PointF start_point, PointF end_point, PointF ctr_point_1, PointF ctr_point_2, double t, int bezier_rank)
{
    PointF bezier_point;
    switch (bezier_rank)
    {
    case 1:
    {
        bezier_point.X = (1 - t) * start_point.X + t * end_point.X;
        bezier_point.Y = (1 - t) * start_point.Y + t * end_point.Y;
        break;
    }
    case 2:
    {
        bezier_point.X = (1 - t) * (1 - t) * start_point.X + 2 * t * (1 - t) * ctr_point_1.X + t * t * end_point.X;
        bezier_point.Y = (1 - t) * (1 - t) * start_point.Y + 2 * t * (1 - t) * ctr_point_1.Y + t * t * end_point.Y;
        break;
    }
    case 3:
    {
        bezier_point.X = (1 - t) * (1 - t) * (1 - t) * start_point.X + 3 * t * (1 - t) * (1 - t) * ctr_point_1.X + 3 * t * t * (1 - t) * ctr_point_2.X + t * t * t * end_point.X;
        bezier_point.Y = (1 - t) * (1 - t) * (1 - t) * start_point.Y + 3 * t * (1 - t) * (1 - t) * ctr_point_1.Y + 3 * t * t * (1 - t) * ctr_point_2.Y + t * t * t * end_point.Y;
        break;
    }
    default:
        break;
    }
    return bezier_point;
}

/***************************************************************
  *  @brief     获得贝塞尔曲线的输出点
  *  @param     输入的过程点：input_points；输出点：out_points；控制点：ctrl_points；
  *  @param     输入的点数：input_num;两个点之间的点数：num_btw_two
  *  @note      建议先百度贝塞尔曲线了解原理
  *  @Sample usage
  *  @author    ZH
  *  @edit      2020/2/17
 **************************************************************/
void Bezier::outpoints_get()
{
    double t = 0;
    double step = 1.0 / num_btw_two;
    int bezier_rank = 0;
    if (input_num == 2) //直线的情况
    {
        bezier_rank = 1;
        for (int j = 0; j < num_btw_two; j++)
        {
            t = step * j;
            out_points[j] = bezier_point_get(input_points[0], input_points[1], ctrl_points[0], ctrl_points[1], t, bezier_rank);
        }
    }
    else
    {
        for (int i = 0; i < input_num - 1; i++)
        {

            if (i == 0)
            {
                for (int j = 0; j < num_btw_two; j++) //前三个点用二阶
                {
                    t = step * j;
                    out_points[i * num_btw_two + j] = bezier_point_get(input_points[0], input_points[1], ctrl_points[0], ctrl_points[1], t, 2);
                }
            }
            else if (i == input_num - 2) //最后三个点用二阶
            {
                for (int j = 0; j < num_btw_two; j++)
                {
                    t = step * j;
                    out_points[i * num_btw_two + j] = bezier_point_get(input_points[i], input_points[i + 1], ctrl_points[2 * i - 1], ctrl_points[2 * i], t, 2);
                }
            }
            else
            {
                for (int j = 0; j < num_btw_two; j++) //中间点用三阶
                {
                    t = step * j;
                    out_points[i * num_btw_two + j] = bezier_point_get(input_points[i], input_points[i + 1], ctrl_points[2 * i - 1], ctrl_points[2 * i], t, 3);
                }
            }
        }
    }
    out_points[(input_num - 1) * num_btw_two] = input_points[input_num - 1];
}

/***************************************************************
  *  @brief     得出贝塞尔曲线的总长，即路程，相当于用微分法，有点误差
  *  @param     输出点：out_points； 输出点的个数：out_num；
  *  @note      建议先百度贝塞尔曲线了解原理
  *  @Sample usage
  *  @author    ZH
  *  @edit      2020/2/17
 **************************************************************/
void Bezier::calculate_length()
{
    length = 0;
    for (int i = 0; i <= out_num - 1; i++)
    {
        length += dis_btw_points(out_points[i], out_points[i + 1]);
    }
}

/***************************************************************
  *  @brief     贝塞尔曲线的速度方向规划
  *  @param     输出点：out_points；输出的贝塞尔曲线速度方向数组：bezier_direct; 输出点的个数：out_num；
  *  @note      建议先百度贝塞尔曲线了解原理
  *  @Sample usage
  *  @author    ZH
  *  @edit      2020/2/17
 **************************************************************/
void Bezier::direct_planning()
{
    for (int i = 0; i <= out_num - 1; i++)
    {
        direct[i] = atan2((out_points[i + 1].Y - out_points[i].Y), (out_points[i + 1].X - out_points[i].X));
    }
    direct[out_num] = direct[out_num - 1];
}

/***************************************************************
  *  @brief     小车姿态的角度规划
  *  @param     小车姿态的角度数组：bezier_angle；小车的最终姿态角：target_angle 输出点的个数：out_num；
  *  @note      建议先百度贝塞尔曲线了解原理
  *  @Sample usage
  *  @author    ZH
  *  @edit      2020/2/17
 *********************************************：*****************/
void Bezier::angle_planning()
{
    float angle_erorr = target_angle - now_angle;
    for (int i = 0; i < out_num / 2; i++)
    {
        angle[i] = now_angle / 180 * PI;
    }
    for (int i = out_num / 2; i <= out_num; i++)
    {
        angle[i] = now_angle / 180 * PI + angle_erorr / 180 * PI * (i - out_num / 2) / (out_num - out_num / 2);
    }
    for (int i = out_num + 1; i < out_num + 3; i++)
    {
        angle[i] = now_angle / 180 * PI + angle_erorr / 180 * PI;
    }
}

/***************************************************************
  *  @brief     根据曲率计算小车的速度
  *  @param
  *  @note      先生成点集，之后调用此函数
  *  @Sample usage     生成的速度规划在speed_each_point数组中，每个速度代表对应点的速度
  *  @author    ZH
  *  @edit      2019/9/26
  *  @upadate   2020/2/21
 **************************************************************/
void Bezier::speed_planning()
{
    speed[0] = 50; //起始速度
    float mid;
    for (int i = 2; i < out_num; i++)
    {
        /*将三个点乘以一个系数来计算曲率是毫无道理的，但是用来规划速度却还可以...
         * 希望能有更合理的速度规划方法2020.2.21*/
        PointF p1, p2, p3;
        p1.X = out_points[i - 2].X * 52;
        p1.Y = out_points[i - 2].Y * 52;
        p2.X = out_points[i - 1].X * 52;
        p2.Y = out_points[i - 1].Y * 52;
        p3.X = out_points[i].X * 52;
        p3.Y = out_points[i].Y * 52;

        float curvity = calculate_curvity(p1, p2, p3);

        if (curvity >= 1e4 || curvity <= 1e-6)
        {
            speed[i - 1] = speed[i - 2];
            continue;
        }

        mid = sqrtf(k_speed * 20 * curvity);
        if (mid > max_speed)
        {
            mid = max_speed;
        }
        speed[i - 1] = (int)mid;
        if (speed[i - 1] == -2147483648) //无穷大的情景,即三点接近共线，曲率无穷大
        {
            speed[i - 1] = speed[i - 2];
        }
        if (speed[i - 1] <= 30)
        {
            speed[i - 1] = 30;
        }
    }
    speed[out_num - 1] = 30;
    speed[out_num] = 30;

    /*起始的几个点和最后的几个点的速度减小，防止加速度过大，希望有更合理的速度规划方法2020.2.21*/
    float t = 0.2;
    for (int i = 1; i <= 8; i++)
    {
        speed[i] = speed[i] * t;
        t += 0.1;
    }
    t = 0.1;
    for (int i = out_num - 2; i >= out_num - 10; i--)
    {
        speed[i] *= t;
        t += 0.1;
    }
}

/***************************************************************
  *  @brief     由于之前的贝塞尔曲线不支持规划直线路径的速度规划，所以增加了直线路径的速度规划
  *  @param
  *  @note
  *  @Sample usage     用于直线路径的规划
  *  @author    ZH
  *  @edit      2019/12/10
 **************************************************************/
void Bezier::strghtline_speed_plan()
{
    double dis_in_total = dis_btw_points(out_points[0], out_points[out_num]);
    /*生成每个点的速度大小*/
    for (int i = 0; i <= out_num / 2; i++)
    {
        double dis_to_bgn = dis_btw_points(out_points[0], out_points[i]);
        speed[i] = 50 + k_speed * dis_to_bgn / dis_in_total;
        if (speed[i] > max_speed)
        {
            speed[i] = max_speed;
        }
    }

    int j = 0;
    for (int i = out_num; i > out_num / 2; i--, j++)
    {
        speed[i] = speed[j] - 50;
        if (speed[i] > max_speed)
        {
            speed[i] = max_speed;
        }
    }
}

/***************************************************************
  *  @brief     计算两点间距离
  *  @param     P1:点1
  *  @param     P2:点2
  *  @note      无
  *  @Sample usage     无
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
float Bezier::dis_btw_points(PointF P1, PointF P2)
{
    return sqrt((P1.X - P2.X) * (P1.X - P2.X) + (P1.Y - P2.Y) * (P1.Y - P2.Y));
}

/***************************************************************
  *  @brief     曲率计算方法
  *  @param     PointF P1,P2,P3 分别为前进路上的第一个点，第二个点，和第三个点
  *  @note      此函数配合bezier_speed_planning使用，用来进行速度规划
  *  @Sample usage     此函数配合speed_optimize_curvature使用
  *  @author    ZH
  *  @edit      2019/9/26
 **************************************************************/
float Bezier::calculate_curvity(PointF P1, PointF P2, PointF P3)
{
    float m1, n1;
    float m2, n2;
    float a1, b1;
    float a2, b2;
    float x0, y0;
    float curvity;
    /*if( atan2f( P2.X - P1.X , P2.Y - P1.Y ) - atan2f( P3.X - P2.X , P3.Y - P2.Y ) <= 1e-3 )//三点共线，直接标记曲率为0
    {
        curvity = 0;
        return curvity;
    }*/
    m1 = (P1.X + P3.X) / 2;
    n1 = (P1.Y + P3.Y) / 2;
    m2 = (P2.X + P3.X) / 2;
    n2 = (P2.Y + P3.Y) / 2;
    a1 = (P3.Y - P1.Y) / (P3.X - P1.X);
    b1 = n1 - a1 * m1;
    a2 = (P3.Y - P2.Y) / (P3.X - P2.X);
    b2 = n2 - a2 * m2;
    x0 = (b2 - b1) / (a1 - a2);
    y0 = a1 * x0 + b1;
    curvity = sqrt((P1.X - x0) * (P1.X - x0) + (P1.Y - y0) * (P1.Y - y0));
    return curvity;
}
