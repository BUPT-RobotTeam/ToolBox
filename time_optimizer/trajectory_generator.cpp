#include <trajectory_generator.h>
#include <QMessageBox>
#include <QString>
#include <QTextStream>
#include <QDebug>

TimeOptimizerTraj::TimeOptimizerTraj(double max_vel,double max_acc,double max_d_acc,double d_s,
                  int dev_order,int min_order,double rho):
        AbstractTrajGenerator(max_vel, max_acc, max_d_acc),
        _rho(rho),_d_s(d_s),_dev_order(dev_order),_min_order(min_order)
{
    _poly_num1D = 2 * _dev_order;
};


/**
 * @brief 轨迹生成函数
 * @param path Eigen::MatrixXd 路径点
 * @param max_vel
 * @param max_acc
 * @param _max_d_acc
 * @param _d_s
 */
void TimeOptimizerTraj::trajGeneration(Eigen::MatrixXd path)
{
    TrajectoryGeneratorWaypoint  trajectoryGeneratorWaypoint;
    MinimumTimeOptimizer time_optimizer;
    
    MatrixXd vel = MatrixXd::Zero(2,3); 
    MatrixXd acc = MatrixXd::Zero(2,3);
//    std::cout<< path <<std::endl;
    // give an arbitraty time allocation, all set all durations as 1 in the commented function.
    _polyTime  = timeAllocation(path); //_polyTime  = timeAllocationNaive(path); 

    // generate a minimum-jerk piecewise monomial polynomial-based trajectory
    // ros::Time time_1 = ros::Time::now();
    _polyCoeff = trajectoryGeneratorWaypoint.PolyQPGeneration(_dev_order, path, vel, acc, _polyTime);   
    // ros::Time time_2 = ros::Time::now();
    _segment_num = _polyCoeff.rows();

    // visualize the spatial fixed trajectory
//    visWayPointPath(path);
//    visWayPointTraj( _polyCoeff, _polyTime);

    // ROS_WARN("[TimeOptimizer DEMO] Spatial trajectory generated");
    // cout<<"[TimeOptimizer DEMO] time cunsume in spatial trajectory is: "<<(time_2 - time_1).toSec()<<endl;
    // use this structure to evaluate this monomial polynomial trajectory in the time optimizer; 
    // or your OWN implementation inheriting the base class for other types of piecewise trajectory (B-spline ...)
    TrajPolyMono polyTraj(_polyCoeff, _polyTime);
    

    // ros::Time time_3 = ros::Time::now();
    // run the time optimizer
    if(time_optimizer.MinimumTimeGeneration( polyTraj, _MAX_Vel, _MAX_Acc, _MAX_d_Acc, _d_s, _rho) )
    {   
        // ros::Time time_4 = ros::Time::now();
        _has_traj = true;    
        // ROS_WARN("[TimeOptimizer DEMO] Temporal trajectory generated");
        // cout<<"[TimeOptimizer DEMO] time cunsume in temporal trajectory is: "<<(time_4 - time_3).toSec()<<endl;
        
        // pull out the results in an allocator data structure
        _time_allocator = time_optimizer.GetTimeAllcoation();

        // _traj_time_final = _traj_time_start = ros::Time::now();
        _traj_time_final = _traj_time_start = 0;

        for(int i = 0; i < _time_allocator->time.rows(); i++)
        {   
            int K = _time_allocator->K(i);
            _traj_time_final += _time_allocator->time(i, K - 1);

        }

        cout<<"[TimeOptimizer DEMO] now start publishing commands"<<endl;
    }
    else
    {
        QString warningText;
        warningText=QString::asprintf(
                u8"[TimeOptimizer DEMO] 可能的原因 :\n"
                u8"1 - 检查你的Mosek license是否安装,\n"
                u8"2 - 求解器的数值问题，调大d_s"
        );
        QMessageBox::warning(nullptr, u8"[TimeOptimizer DEMO] 轨迹生成失败",
                             warningText, QMessageBox::Ok  , QMessageBox::Ok);

//        cout<<"[TimeOptimizer DEMO] temporal optimization fail"<<endl;
//        cout<<"[TimeOptimizer DEMO] possible resons : " << "\n" <<
//        "1 - please check the spatial trajectory,"     <<  "\n" <<
//        "2 - numerical issue of the solver, try setting a larger d_s"<<endl;
    }
}

Matrix3d TimeOptimizerTraj::getCtrlCmd(double t)
{
    if( _has_traj == false || t > _traj_time_final )
    {   
        return {};
    }
    // if(_is_dump_data) t_result<<t<<endl;

    MatrixXd time     = _time_allocator->time;
    MatrixXd time_acc = _time_allocator->time_acc;

    int idx;
    for(idx = 0; idx < _segment_num; idx++)
    {   
        int K = _time_allocator->K(idx);
        if( t  > time(idx, K - 1))
            t -= time(idx, K - 1);
        else
            break;
    }
    double t_tmp = t;     

    int grid_num = _time_allocator->K(idx);
    
    // now we need to find which grid the time instance belongs to
    int grid_idx;
    // for(grid_idx = 0; grid_idx < _time_allocator->K(idx); grid_idx++){
    //     if (t > time(idx, grid_idx)) continue;
    //     else{ 
    //         if(grid_idx > 0) t -= time(idx, grid_idx - 1);
    //         else             t -= 0.0;
    //         break;
    //     }
    // }
    for(grid_idx = 0; 
        grid_idx < _time_allocator->K(idx) && t > time(idx, grid_idx);
        grid_idx++);
    if(grid_idx > 0){ t -= time(idx, grid_idx - 1); }

    double delta_t;
    if(grid_idx > 0)
        delta_t = (time(idx, grid_idx) - time(idx, grid_idx - 1));
    else
        delta_t = time(idx, grid_idx) - 0.0;
    
    double delta_s = t * _time_allocator->s_step / delta_t;
    double s = _time_allocator->s(idx, grid_idx) + delta_s;

    // get position data 
    Vector3d position_s = getPosPoly(_polyCoeff, idx, s); 
    Vector3d position   = position_s;

    // get velocity data
    double s_k   = _time_allocator->s(idx, grid_idx);
    double s_k_1 = _time_allocator->s(idx, grid_idx + 1);
    double b_k   = _time_allocator->b(idx, grid_idx);
    double b_k_1 = _time_allocator->b(idx, grid_idx + 1);

    Vector3d velocity_s1 = getVelPoly(_polyCoeff, idx, s_k  ); 
    Vector3d velocity_s2 = getVelPoly(_polyCoeff, idx, s_k_1);

    Vector3d velocity1   = velocity_s1 * sqrt(b_k);
    Vector3d velocity2   = velocity_s2 * sqrt(b_k_1);
    Vector3d velocity   = velocity1 + (velocity2 - velocity1) * t / delta_t;

// ### NOTE: From what above we get the position and velocity easily.
// ###       positions are the same as the trajectory before re-timing; and velocity are obtained by interpolation between each grid.
// ###       In what follows, we will get the accleration. It's more complicated since each acceleration ais evaluated at the middle of a grid        
    // reset grid_idx and t for time acceleration axis
    t = t_tmp;
    for(grid_idx = 0; grid_idx < _time_allocator->K(idx); grid_idx++)
    {
        if (t > time_acc(idx, grid_idx)) continue;
        else{ 
            if(grid_idx > 0) t -= time_acc(idx, grid_idx - 1);
            else             t -= 0.0;
            break;
        }
    }
    
    if(grid_idx == grid_num)
        t -= time_acc(idx, grid_num - 1);

    // prepare to do accleration interpolation
    Vector3d velocity_s, acceleration_s, acceleration1, acceleration2;
    Vector3d acceleration;

    double a_k;
    // # special case 1: the very first grid of all segments of the trajectory, do interpolation in one grid
    if( grid_idx == 0 && idx == 0 ) 
    {   
        s_k   = _time_allocator->s(idx, 0);
        s_k_1 = _time_allocator->s(idx, 0 + 1);
        
        a_k   = _time_allocator->a(idx, 0);
        b_k   = _time_allocator->b(idx, 0);
        b_k_1 = _time_allocator->b(idx, 0 + 1);

        velocity_s     = getVelPoly(_polyCoeff, idx, (s_k + s_k_1 ) / 2.0);
        acceleration_s = getAccPoly(_polyCoeff, idx, (s_k + s_k_1 ) / 2.0);
        acceleration2 = velocity_s * a_k + acceleration_s * (b_k + b_k_1) / 2.0;
        acceleration1 << 0.0, 0.0, 0.0;
        
        acceleration   = acceleration1 + (acceleration2 - acceleration1) * t / time_acc(0, 0); 
    }
    // # special case 2: the very last grid of all segments of the trajectory, do interpolation in one grid
    else if( grid_idx == grid_num && idx == (_segment_num - 1) )
    {   
        s_k   = _time_allocator->s(idx, grid_num - 1);
        s_k_1 = _time_allocator->s(idx, grid_num);
        
        a_k   = _time_allocator->a(idx, grid_num - 1);
        b_k   = _time_allocator->b(idx, grid_num - 1);
        b_k_1 = _time_allocator->b(idx, grid_num    );

        velocity_s     = getVelPoly(_polyCoeff, idx, (s_k + s_k_1 ) / 2.0);
        acceleration_s = getAccPoly(_polyCoeff, idx, (s_k + s_k_1 ) / 2.0);
        acceleration = velocity_s * a_k + acceleration_s * (b_k + b_k_1) / 2.0;
    }
    // # regular case: do interpolation between two grids
    else 
    {   
        // sub-case 1: two grids are in the same segment
        if(grid_idx < grid_num && grid_idx > 0) // take average accleration in a same segment
        {   
            delta_t = (time_acc(idx, grid_idx) - time_acc(idx, grid_idx - 1));
            
            s_k   = _time_allocator->s(idx, grid_idx - 1);
            s_k_1 = _time_allocator->s(idx, grid_idx + 0);
            
            a_k   = _time_allocator->a(idx, grid_idx - 1);
            b_k   = _time_allocator->b(idx, grid_idx - 1);
            b_k_1 = _time_allocator->b(idx, grid_idx + 0);

            velocity_s     = getVelPoly(_polyCoeff, idx, (s_k + s_k_1 ) / 2.0);
            acceleration_s = getAccPoly(_polyCoeff, idx, (s_k + s_k_1 ) / 2.0);
            acceleration1 = velocity_s * a_k + acceleration_s * (b_k + b_k_1) / 2.0;

            s_k   = _time_allocator->s(idx, grid_idx + 0);
            s_k_1 = _time_allocator->s(idx, grid_idx + 1);

            a_k   = _time_allocator->a(idx, grid_idx + 0);
            b_k   = _time_allocator->b(idx, grid_idx + 0);
            b_k_1 = _time_allocator->b(idx, grid_idx + 1);              

            velocity_s     = getVelPoly(_polyCoeff, idx, (s_k + s_k_1 ) / 2.0);
            acceleration_s = getAccPoly(_polyCoeff, idx, (s_k + s_k_1 ) / 2.0);
            acceleration2 = velocity_s * a_k + acceleration_s * (b_k + b_k_1) / 2.0;
            acceleration   = acceleration1 + (acceleration2 - acceleration1) * t / delta_t;   
        }
        // sub-case 2: two grids are in consecutive segment, the current grid is in a segment's tail
        else if(grid_idx == grid_num)// take average accleration between two segments
        {   
            delta_t = (time(idx, grid_num - 1) - time_acc(idx, grid_num - 1) + time_acc(idx + 1, 0) );
            
            s_k   = _time_allocator->s(idx, grid_idx - 1);
            s_k_1 = _time_allocator->s(idx, grid_idx);
            
            a_k   = _time_allocator->a(idx, grid_idx - 1);
            b_k   = _time_allocator->b(idx, grid_idx - 1);
            b_k_1 = _time_allocator->b(idx, grid_idx);

            velocity_s     = getVelPoly(_polyCoeff, idx, (s_k + s_k_1 ) / 2.0);
            acceleration_s = getAccPoly(_polyCoeff, idx, (s_k + s_k_1 ) / 2.0);
            acceleration1 = velocity_s * a_k + acceleration_s * (b_k + b_k_1) / 2.0;
            s_k   = _time_allocator->s(idx + 1, 0);
            s_k_1 = _time_allocator->s(idx + 1, 1);

            a_k   = _time_allocator->a(idx + 1, 0);
            b_k   = _time_allocator->b(idx + 1, 0);
            b_k_1 = _time_allocator->b(idx + 1, 1);              

            velocity_s     = getVelPoly(_polyCoeff, idx + 1, (s_k + s_k_1 ) / 2.0);
            acceleration_s = getAccPoly(_polyCoeff, idx + 1, (s_k + s_k_1 ) / 2.0);
            acceleration2 = velocity_s * a_k + acceleration_s * (b_k + b_k_1) / 2.0;
            acceleration  = acceleration1 + (acceleration2 - acceleration1) * t / delta_t;        
        }
        // sub-case 3: two grids are in consecutive segment, the current grid is in a segment's head
        else if(grid_idx == 0)// take average accleration between two segments
        {   
            int grid_num_k = _time_allocator->K(idx - 1);
            delta_t = (time(idx - 1, grid_num_k - 1) - time_acc(idx - 1, grid_num_k - 1) + time_acc(idx, 0) );
            
            s_k   = _time_allocator->s(idx - 1, grid_num_k - 1);
            s_k_1 = _time_allocator->s(idx - 1, grid_num_k    );
            
            a_k   = _time_allocator->a(idx - 1, grid_num_k - 1);
            b_k   = _time_allocator->b(idx - 1, grid_num_k - 1);
            b_k_1 = _time_allocator->b(idx - 1, grid_num_k    );

            velocity_s     = getVelPoly(_polyCoeff, idx - 1, (s_k + s_k_1 ) / 2.0);
            acceleration_s = getAccPoly(_polyCoeff, idx - 1, (s_k + s_k_1 ) / 2.0);
            acceleration1  = velocity_s * a_k + acceleration_s * (b_k + b_k_1) / 2.0;

            s_k   = _time_allocator->s(idx, 0);
            s_k_1 = _time_allocator->s(idx, 0 + 1);
            
            a_k   = _time_allocator->a(idx, 0);
            b_k   = _time_allocator->b(idx, 0);
            b_k_1 = _time_allocator->b(idx, 0 + 1);

            velocity_s     = getVelPoly(_polyCoeff, idx, (s_k + s_k_1 ) / 2.0);
            acceleration_s = getAccPoly(_polyCoeff, idx, (s_k + s_k_1 ) / 2.0);
            acceleration2  = velocity_s * a_k + acceleration_s * (b_k + b_k_1) / 2.0;
            acceleration   = acceleration1 + (acceleration2 - acceleration1) * (t + time(idx - 1, grid_num_k - 1) - time_acc(idx - 1, grid_num_k - 1)) / delta_t;   
        } 
        else {
            // no else
        }
    }

    // dump data in 3 files
    // if(_is_dump_data)
    // {
        // pos_result << position(0)     <<","<< position(1)     <<","<< position(2)    << endl;
        // vel_result << velocity(0)     <<","<< velocity(1)     <<","<< velocity(2)    << endl;
        // acc_result << acceleration(0) <<","<< acceleration(1) <<","<< acceleration(2)<< endl;
    // }
    Matrix3d ret;
    ret << position , velocity , acceleration;
//    std::cout <<ret;
    return ret;
}

Vector3d TimeOptimizerTraj::getAccPoly(MatrixXd polyCoeff, int k, double t)
{
    Vector3d ret;

    for ( int dim = 0; dim < 3; dim++ )
    {
        VectorXd coeff = (polyCoeff.row(k)).segment( dim * _poly_num1D, _poly_num1D );
        VectorXd time  = VectorXd::Zero( _poly_num1D );

        for(int j = 0; j < _poly_num1D; j ++)
            if( j==0 || j==1 )
                time(j) = 0.0;
            else
                time(j) = j * (j - 1) * pow(t, j-2);

        ret(dim) = coeff.dot(time);
    }

    return ret;
}

Vector3d TimeOptimizerTraj::getVelPoly(MatrixXd polyCoeff, int k, double t)
{
    Vector3d ret;

    for ( int dim = 0; dim < 3; dim++ )
    {
        VectorXd coeff = (polyCoeff.row(k)).segment( dim * _poly_num1D, _poly_num1D );
        VectorXd time  = VectorXd::Zero( _poly_num1D );
        
        for(int j = 0; j < _poly_num1D; j ++)
            if(j==0)
                time(j) = 0.0;
            else
                time(j) = j * pow(t, j-1);

        ret(dim) = coeff.dot(time);
    }

    return ret;
}

Vector3d TimeOptimizerTraj::getPosPoly(MatrixXd polyCoeff, int k, double t)
{
    Vector3d ret;

    for ( int dim = 0; dim < 3; dim++ )
    {
        VectorXd coeff = (polyCoeff.row(k)).segment( dim * _poly_num1D, _poly_num1D );
        VectorXd time  = VectorXd::Zero( _poly_num1D );
        
        for(int j = 0; j < _poly_num1D; j ++)
          if(j==0)
              time(j) = 1.0;
          else
              time(j) = pow(t, j);

        ret(dim) = coeff.dot(time);
    }

    return ret;
}

void TimeOptimizerTraj::visWayPointPath(MatrixXd path)
{

    for(int i = 0; i < path.rows(); i++){
    //   geometry_msgs::Point p;
//      p.x = path(i, 0);
//      p.y = path(i, 1);
//      p.z = path(i, 2);

//      points.points.push_back(p);

      if( i < (path.rows() - 1) )
      {
        //   geometry_msgs::Point p_line;
        //   p_line = p;
        //   line_list.points.push_back(p_line);
//          p_line.x = path(i+1, 0);
//          p_line.y = path(i+1, 1);
//          p_line.z = path(i+1, 2);
//          line_list.points.push_back(p_line);
      }
    }

    // _wp_path_vis_pub.publish(points);
    // _wp_path_vis_pub.publish(line_list);
}

void TimeOptimizerTraj::visWayPointTraj(MatrixXd polyCoeff, VectorXd time)
{
    double traj_len = 0.0;
    int count = 0;
    Vector3d cur, pre;
    cur.setZero();
    pre.setZero();

    Vector3d pos;
    // geometry_msgs::Point pt;

    for(int i = 0; i < time.size(); i++ )
    {   
        for (double t = 0.0; t < time(i); t += 0.01, count += 1)
        {
          pos = getPosPoly(polyCoeff, i, t);
        //   cur(0) = pt.x = pos(0);
        //   cur(1) = pt.y = pos(1);
        //   cur(2) = pt.z = pos(2);
        //   _traj_vis.points.push_back(pt);

          if (count) traj_len += (pre - cur).norm();
          pre = cur;
        }
    }

    // _wp_traj_vis_pub.publish(_traj_vis);

}


VectorXd TimeOptimizerTraj::timeAllocation( MatrixXd Path)
{ 
    VectorXd time(Path.rows() - 1);

    for (int k = 0; k < (Path.rows() - 1); k++)
    {
        double dtxyz;

        Vector3d p0   = Path.row(k);        
        Vector3d p1   = Path.row(k + 1);    
        double D    = (p1 - p0).norm();             

        double acct = (_MAX_Vel) / _MAX_Acc;
        double accd = (_MAX_Acc * acct * acct / 2);
        double dcct = _MAX_Vel / _MAX_Acc;                                  
        double dccd = _MAX_Acc * dcct * dcct / 2;                           

        if (D < accd + dccd)
        {   
            double t1 = sqrt( _MAX_Acc * D ) / _MAX_Acc;
            double t2 = (_MAX_Acc * t1) / _MAX_Acc;
            dtxyz     = t1 + t2;    
        }
        else
        {                                        
            double t1 = acct;                              
            double t2 = (D - accd - dccd) / _MAX_Vel;
            double t3 = dcct;
            dtxyz     = t1 + t2 + t3;                                                                  
        }

        dtxyz = ceil(dtxyz / _d_s) * _d_s;
        time(k) = dtxyz;
        // Rounding the time allocation; to avoid dis-continuous of published commands
    }

    return time;
}

[[maybe_unused]] VectorXd TimeOptimizerTraj::timeAllocationNaive(MatrixXd Path)
{   
    VectorXd time(Path.rows() - 1);

    for(int i = 0; i < (Path.rows() - 1); i++)
        time(i) = 1.0;

    return time;
}
/**
 * @brief 求某段轨迹的实际时间
 * @param seg_idx 下标从0开始
 * @return double 某段轨迹的实际时间，如果负数说明超过越界了
 */
double TimeOptimizerTraj::getTrajSegmentTime(int seg_idx) {
    if(seg_idx>=_segment_num)
    {return -1;}

//    double ret;

    int seg_k;
    seg_k = (int)_time_allocator->K(seg_idx );
    return _time_allocator->time(seg_idx ,seg_k-1);
}

TimeOptimizerTraj::~TimeOptimizerTraj() {
    delete _time_allocator;
}
