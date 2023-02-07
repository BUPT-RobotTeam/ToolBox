#include "pagevreprudderbase.h"
#include "ui_pagevreprudderbase.h"


PageVrepRudderBase::PageVrepRudderBase(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PageVrepRudderBase)
{
    ui->setupUi(this);

    timer_5ms = new QTimer(this);
}

void PageVrepRudderBase::timer5ms(){
    timeMsCount+=50;
    if(timeMsCount%1000==0){
       timeSCount +=1;
       ui->vrepStatusLabel->setText(QString("Connected: %1:%2").arg(timeSCount/60).arg(timeSCount%60));
       timeMsCount = 0;
    }
    if(simxGetObjectPosition(clientID,objectCar,1,carPosition, simx_opmode_blocking) != simx_return_ok);
        ui->lineEdit_4->setText(QString("%1").arg(carPosition[0]));
}

PageVrepRudderBase::~PageVrepRudderBase()
{
    delete ui;
}

void PageVrepRudderBase::on_actionalwaysOnTop_triggered()
{
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
    this->show();
}


void PageVrepRudderBase::on_mainWindowStatusButton_clicked()
{
    if(mainWindowStatus){
        emit hideMainWindow();
        mainWindowStatus = false;
        ui->mainWindowStatusButton->setText("显示主窗口");
    }else{
        emit showMainWindow();
        mainWindowStatus = true;
        ui->mainWindowStatusButton->setText("隐藏主窗口");
    }
}

void PageVrepRudderBase::on_alwaysOnTopButton_clicked()
{
    if(!alwaysTopFlag){
        this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
        alwaysTopFlag = true;
        ui->alwaysOnTopButton->setText("取消总在最前");
        this->show();
    }else{
        this->setWindowFlags(this->windowFlags() &~ Qt::WindowStaysOnTopHint);
        alwaysTopFlag = false;
        ui->alwaysOnTopButton->setText("总在最前");
        this->show();
    }
}

void PageVrepRudderBase::on_connectVrepButton_clicked()
{
    int para_status = 1;
    clientID = simxStart("127.0.0.1", 19997, true, true, 5000, 5);
    if(clientID!=-1){
        if (simxGetObjectHandle(clientID, "Dir1", &jointDir1, simx_opmode_blocking) != simx_return_ok)
           para_status = 0;
        if (simxGetObjectHandle(clientID, "Dir2", &jointDir2, simx_opmode_blocking) != simx_return_ok)
           para_status = 0;
        if (simxGetObjectHandle(clientID, "Dir3", &jointDir3, simx_opmode_blocking) != simx_return_ok)
           para_status = 0;
        if (simxGetObjectHandle(clientID, "Dir4", &jointDir4, simx_opmode_blocking) != simx_return_ok)
           para_status = 0;
        if (simxGetObjectHandle(clientID, "Vel1", &jointVel1, simx_opmode_blocking) != simx_return_ok)
           para_status = 0;
        if (simxGetObjectHandle(clientID, "Vel2", &jointVel2, simx_opmode_blocking) != simx_return_ok)
           para_status = 0;
        if (simxGetObjectHandle(clientID, "Vel3", &jointVel3, simx_opmode_blocking) != simx_return_ok)
           para_status = 0;
        if (simxGetObjectHandle(clientID, "Vel4", &jointVel4, simx_opmode_blocking) != simx_return_ok)
           para_status = 0;
        if (simxGetObjectHandle(clientID, "Car", &objectCar, simx_opmode_blocking) != simx_return_ok)
           para_status = 0;
        if(para_status){
            ui->vrepStatusLabel->setText("Connected");
            timer_5ms->start(50);
            connect(timer_5ms, SIGNAL(timeout()),this, SLOT(timer5ms()));
            ui->startSimulationButton->setEnabled(true);
            ui->endSimulationButton->setEnabled(true);
        }
        else ui->vrepStatusLabel->setText("Connected,but not joints");
        ui->connectVrepButton->setEnabled(false);

    }else{
        ui->vrepStatusLabel->setText("Disconnected");
    }
}

void PageVrepRudderBase::sendDirsToVrep(float d1,float d2,float d3,float d4){
    simxFloat tarDir1 = d1;
    simxFloat tarDir2 = d2;
    simxFloat tarDir3 = d3;
    simxFloat tarDir4 = d4;
    simxSetJointTargetPosition(clientID, jointDir1, tarDir1, simx_opmode_blocking);
    simxSetJointTargetPosition(clientID, jointDir2, tarDir2, simx_opmode_blocking);
    simxSetJointTargetPosition(clientID, jointDir3, tarDir3, simx_opmode_blocking);
    simxSetJointTargetPosition(clientID, jointDir4, tarDir4, simx_opmode_blocking);
}

void PageVrepRudderBase::sendVelsToVrep(float v1,float v2,float v3,float v4){
    simxFloat tarVel1 = v1;
    simxFloat tarVel2 = v2;
    simxFloat tarVel3 = v3;
    simxFloat tarVel4 = v4;
    simxSetJointTargetVelocity(clientID, jointVel1, tarVel1, simx_opmode_blocking);
    simxSetJointTargetVelocity(clientID, jointVel2, tarVel2, simx_opmode_blocking);
    simxSetJointTargetVelocity(clientID, jointVel3, tarVel3, simx_opmode_blocking);
    simxSetJointTargetVelocity(clientID, jointVel4, tarVel4, simx_opmode_blocking);
//  应该校验是否发送成功的，暂时没有加
//if (simxSetJointTargetVelocity(clientID, Revolute_joint, tar_velo, simx_opmode_blocking) == simx_return_ok)//设置关节目标转速
}

void PageVrepRudderBase::on_generalSendDirButton_clicked()
{
    float d1 = ui->dir1SpinBox->value();
    float d2 = ui->dir2SpinBox->value();
    float d3 = ui->dir3SpinBox->value();
    float d4 = ui->dir4SpinBox->value();
    sendDirsToVrep(d1,d2,d3,d4);
}

void PageVrepRudderBase::on_generalSendVelButton_clicked()
{
    float v1 = ui->vel1SpinBox->value();
    float v2 = ui->vel2SpinBox->value();
    float v3 = ui->vel3SpinBox->value();
    float v4 = ui->vel4SpinBox->value();
    sendVelsToVrep(v1,v2,v3,v4);
}

void PageVrepRudderBase::on_startSimulationButton_clicked()
{
    simxStartSimulation(clientID,simx_opmode_blocking);
}

void PageVrepRudderBase::on_endSimulationButton_clicked()
{
    simxStopSimulation(clientID,simx_opmode_blocking);
}

void PageVrepRudderBase::on_pauseSimulationButton_clicked()
{
    simxPauseSimulation(clientID,simx_opmode_blocking);
}
