#ifndef _TRAJ_GEN_H_
#define _TRAJ_GEN_H_

#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
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
int _poly_num1D;
class TimeOptimizerTraj
{
    public:

    TimeOptimizerTraj(double max_vel,double max_acc=1.0,double max_d_acc=0.5,double d_s=0.5,
                      int dev_order=4,int min_order=3,double rho=0.000):
        _dev_order(dev_order),_min_order(min_order),_rho(rho),
        _MAX_Vel(max_vel),_MAX_Acc(max_acc),_MAX_d_Acc(max_d_acc),_d_s(d_s)
    {
        _poly_num1D = 2 * _dev_order;
    };


    void trajGeneration(Eigen::MatrixXd path,double max_vel,double max_acc=1.0,double _max_d_acc=0.5,double _d_s=0.5);
    Matrix3d getCtrlVar(double t);

    void visWayPointTraj( MatrixXd polyCoeff, VectorXd time);
    void visWayPointPath(MatrixXd path);
    Vector3d getPosPoly( MatrixXd polyCoeff, int k, double t );
    Vector3d getVelPoly( MatrixXd polyCoeff, int k, double t );
    Vector3d getAccPoly( MatrixXd polyCoeff, int k, double t );
    
    
    private:

    // double _vis_traj_width;

    //planning : motion variable
    double _MAX_Vel=1, _MAX_Acc=1, _MAX_d_Acc=0.5, _d_s=0.5;
    //planning: start point
    double _start_x, _start_y, _start_z;
    //plannging: a hyperparameter that weighting acc regularization (punishing large acc)
    double _rho; 
    //planning: poly order
    int _dev_order, _min_order, _poly_num1D;
    

    // bool _is_dump_data, _is_use_inte;
    // std::string _pkg_path;
    MatrixXd _polyCoeff;
    VectorXd _polyTime;
    int _segment_num;
    // ros::Time _traj_time_start, _traj_time_final;
    double _traj_time_final , _traj_time_start ;
    bool _has_traj = false;
    Allocator * _time_allocator = NULL;

    VectorXd timeAllocationNaive(MatrixXd Path);
    VectorXd timeAllocation( MatrixXd Path);
    // void rcvWaypointsCallback(const nav_msgs::Path & wp);
};




#endif