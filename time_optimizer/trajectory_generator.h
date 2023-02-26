#ifndef _TRAJ_GEN_H_
#define _TRAJ_GEN_H_

#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <Eigen/Dense>
#include <random>

// Useful customized headers
// #include "backward.hpp"
#include "time_optimizer.h"
#include "trajectory_generator_waypoint.h"
// #include "json.hpp"

// The trajectory class the demo use
#include "traj_poly_mono.h"


using namespace Eigen;
// using json = nlohmann::json;
// namespace backward {
//     backward::SignalHandling sh;
// }
/**
 * @brief 多项式轨迹生成问题抽象描述：
 * 给定轨迹多项式阶数，给定轨迹执行时间。设定轨迹点和起终运动状态作为约束。
 * 需要暴露的接口有：传入path生成轨迹，传入运动参数，获取轨迹段数和时间，获取运动指令
 * 轨迹的多项式只作为求解器的内部参数而不暴露。
 */
class AbstractTrajGenerator
{
public:
    /**
     * 抽象轨迹生成类构造函数，给定运动学约束
     * @param maxVel
     * @param maxAcc
     * @param maxDAcc
     */
    AbstractTrajGenerator(double maxVel,
                          double maxAcc, double maxDAcc)
                          : _MAX_Vel(maxVel),
                            _MAX_Acc(maxAcc),
                            _MAX_d_Acc(maxDAcc)
    {

    };
    /**
     * @brief 虚析构函数，便于子类释放自己的指针
     */
    virtual ~AbstractTrajGenerator() {} ;
    /**
     * 纯虚拟生成轨迹函数
     * @param path 传入path，注意使用eigen矩阵库。
     */
    virtual void trajGeneration(Eigen::MatrixXd path) = 0;
    /**
     * 按照时间获取控制变量，纯虚拟
     * @param t 时间点
     * @return Matrix3d 可以包括位置速度加速度
     */
    virtual Matrix3d getCtrlCmd(double t) = 0;
    /**
     * 根据空间轨迹参数获取点
     * @param polyCoeff 空间轨迹
     * @param k 可以是段号
     * @param t 时间
     * @return 3d位置
     */
    virtual Vector3d getPosPoly( MatrixXd polyCoeff, int k, double t ) = 0;
    /**
     * 根据空间轨迹参数获取速度
     * @param polyCoeff
     * @param k 可以是段号
     * @param t 时间
     * @return 3d速度
     */
    virtual Vector3d getVelPoly( MatrixXd polyCoeff, int k, double t ) = 0;
    /**
     *
     * @param polyCoeff 根据空间轨迹参数获取加速度
     * @param k 可以是段号
     * @param t 时间
     * @return 3d加速度
     */
    virtual Vector3d getAccPoly( MatrixXd polyCoeff, int k, double t ) = 0;
    /**
     * 按段号获取对应段的执行时间
     * @param seg_idx
     * @return 执行时间
     */
    virtual double getTrajSegmentTime(int seg_idx) = 0;
    /**
     *
     * @return 是否生成了轨迹
     */
    bool isHasTraj() const {
        return _has_traj;
    }
    /**
     *
     * @return 生成轨迹的段数，一般是和关键点数量一致。除非是给定起终自动搜索。
     */
    int getSegmentNum() const {
        return _segment_num;
    }
    /**
     * 设定最大速度
     * @param maxVel
     */
    void setMaxVel(double maxVel) {
        _MAX_Vel = maxVel;
    }
    /**
     * 设定最大加速度
     * @param maxAcc
     */
    void setMaxAcc(double maxAcc) {
        _MAX_Acc = maxAcc;
    }
    /**
     * 设定最大加加速度
     * @param maxDAcc
     */
    void setMaxDAcc(double maxDAcc) {
        _MAX_d_Acc = maxDAcc;
    }
    /**
     * 获取轨迹最终时间
     * @return
     */
    double getTrajTimeFinal() const {
        return _traj_time_final;
    }
    /**
     * 获取轨迹初始时间
     * @return
     */
    double getTrajTimeStart() const {
        return _traj_time_start;
    }

protected:
    bool _has_traj = false;
    //planning : motion variable
    double _MAX_Vel=1, _MAX_Acc=1, _MAX_d_Acc=0.5;
    double _traj_time_final = 0 , _traj_time_start = 0 ;
    MatrixXd _polyCoeff;
    int _segment_num = 0 ;

};
/**
 * @brief 时间最优轨迹类，根据 论文 [Optimal Time Allocation for Quadrotor Trajectory Generation](https://ieeexplore.ieee.org/document/8593579)
 * 以及其存储库[HKUST-Aerial-Robotics/TimeOptimizer ](https://github.com/HKUST-Aerial-Robotics/TimeOptimizer)
 * 中的demo.cpp抽象而来
 *
 */
class TimeOptimizerTraj :public AbstractTrajGenerator
{
    public:


    /**
     * TimeOptimizerTraj 轨迹生成器构造函数。
     * @param max_vel 最大速度
     * @param max_acc 最大加速度
     * @param max_d_acc 最大加加速度
     * @param d_s 划分时间轨迹的单位长度
     * @param dev_order 阶数
     * @param min_order
     * @param rho 对于加加速度惩罚项系数
     * @see 最后四个参数可以参考论文 https://ieeexplore.ieee.org/document/8593579
     */
    TimeOptimizerTraj(double max_vel,double max_acc,double max_d_acc=0.5,double d_s=0.1,
                      int dev_order=4,int min_order=3,double rho=0.000);

    TimeOptimizerTraj(const TimeOptimizerTraj& c):
            AbstractTrajGenerator(c),_rho(c._rho),_d_s(c._d_s),_dev_order(c._dev_order),
        _min_order(c._min_order),_poly_num1D(c._poly_num1D),_polyTime(c._polyTime)
    {

        delete _time_allocator;
        _time_allocator = new Allocator(*(c._time_allocator));

    };

    /**
     * 轨迹生成函数
     * @param path 关键点
     */
    void trajGeneration(Eigen::MatrixXd path) override;
    /**
     * 暂时不需要
     * @param polyCoeff
     * @param time
     */
    void visWayPointTraj( MatrixXd polyCoeff, VectorXd time);
    /**
     * 暂时不需要
     * @param path
     */
    void visWayPointPath(MatrixXd path);
    /**
     * 按照时间获取控制变量，纯虚拟
     * @param t 时间点
     * @return Matrix3d 可以包括位置速度加速度
     */
    Matrix3d getCtrlCmd(double t) override ;
    /**
     * 根据空间轨迹参数获取点
     * @param polyCoeff 空间轨迹
     * @param k 可以是段号
     * @param t 时间
     * @return 3d位置
     */
    Vector3d getPosPoly( MatrixXd polyCoeff, int k, double t ) override ;
    /**
     * 根据空间轨迹参数获取速度
     * @param polyCoeff
     * @param k 可以是段号
     * @param t 时间
     * @return 3d速度
     */
    Vector3d getVelPoly( MatrixXd polyCoeff, int k, double t ) override ;
    /**
     *
     * @param polyCoeff 根据空间轨迹参数获取加速度
     * @param k 可以是段号
     * @param t 时间
     * @return 3d加速度
     */
    Vector3d getAccPoly( MatrixXd polyCoeff, int k, double t ) override ;
    /**
     * 按段号获取对应段的执行时间
     * @param seg_idx
     * @return 执行时间
     */
    double getTrajSegmentTime(int seg_idx) override;
    /**
     * 设置加加速度惩罚项
     * @param rho
     */
    void setRho(double rho) {
        _rho = rho;
    }
    /**
     * 设置ds
     * @param dS
     */
    void setDS(double dS) {
        _d_s = dS;
    }

    ~TimeOptimizerTraj() override;


private:

    // double _vis_traj_width;

    //planning: start point
//    double _start_x, _start_y, _start_z;
    //plannging: a hyperparameter that weighting acc regularization (punishing large acc)
    double _rho=0.0000, _d_s=0.05;
    //planning: poly order
    int _dev_order=3, _min_order=4, _poly_num1D;
    

    // bool _is_dump_data, _is_use_inte;
    // std::string _pkg_path;

    VectorXd _polyTime;

    // ros::Time _traj_time_start, _traj_time_final;


    Allocator * _time_allocator = nullptr;///< 时间分配器，速度优化从这里获取

    VectorXd timeAllocationNaive(MatrixXd Path);
    VectorXd timeAllocation( MatrixXd Path);
    // void rcvWaypointsCallback(const nav_msgs::Path & wp);
};




#endif //_TRAJ_GEN_H_