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

    AbstractTrajGenerator(double maxVel,
                          double maxAcc, double maxDAcc)
                          : _MAX_Vel(maxVel),
                            _MAX_Acc(maxAcc),
                            _MAX_d_Acc(maxDAcc)
    {

    };
    virtual ~AbstractTrajGenerator() {} ;
    virtual void trajGeneration(Eigen::MatrixXd path) = 0;

    virtual Matrix3d getCtrlCmd(double t) = 0;
    virtual Vector3d getPosPoly( MatrixXd polyCoeff, int k, double t ) = 0;
    virtual Vector3d getVelPoly( MatrixXd polyCoeff, int k, double t ) = 0;
    virtual Vector3d getAccPoly( MatrixXd polyCoeff, int k, double t ) = 0;
    virtual double getTrajSegmentTime(int seg_idx) = 0;
    bool isHasTraj() const {
        return _has_traj;
    }
    int getSegmentNum() const {
        return _segment_num;
    }

    void setMaxVel(double maxVel) {
        _MAX_Vel = maxVel;
    }

    void setMaxAcc(double maxAcc) {
        _MAX_Acc = maxAcc;
    }

    void setMaxDAcc(double maxDAcc) {
        _MAX_d_Acc = maxDAcc;
    }

    double getTrajTimeFinal() const {
        return _traj_time_final;
    }

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
class TimeOptimizerTraj :public AbstractTrajGenerator
{
    public:



    TimeOptimizerTraj(double max_vel,double max_acc,double max_d_acc=0.5,double d_s=0.1,
                      int dev_order=4,int min_order=3,double rho=0.000);

    TimeOptimizerTraj(const TimeOptimizerTraj& c):
            AbstractTrajGenerator(c),_rho(c._rho),_d_s(c._d_s),_dev_order(c._dev_order),
        _min_order(c._min_order),_poly_num1D(c._poly_num1D),_polyTime(c._polyTime)
    {

        delete _time_allocator;
        _time_allocator = new Allocator(*(c._time_allocator));

    };


    void trajGeneration(Eigen::MatrixXd path) override;

    void visWayPointTraj( MatrixXd polyCoeff, VectorXd time);
    void visWayPointPath(MatrixXd path);

    Matrix3d getCtrlCmd(double t) override ;
    Vector3d getPosPoly( MatrixXd polyCoeff, int k, double t ) override ;
    Vector3d getVelPoly( MatrixXd polyCoeff, int k, double t ) override ;
    Vector3d getAccPoly( MatrixXd polyCoeff, int k, double t ) override ;
    double getTrajSegmentTime(int seg_idx) override;

    void setRho(double rho) {
        _rho = rho;
    }

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


    Allocator * _time_allocator = nullptr;

    VectorXd timeAllocationNaive(MatrixXd Path);
    VectorXd timeAllocation( MatrixXd Path);
    // void rcvWaypointsCallback(const nav_msgs::Path & wp);
};




#endif //_TRAJ_GEN_H_