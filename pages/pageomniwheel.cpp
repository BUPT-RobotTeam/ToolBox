#include "pageomniwheel.h"
#include "ui_pageomniwheel.h"

PageOmniWheel::PageOmniWheel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PageOmniWheel)
{
    ui->setupUi(this);
}

PageOmniWheel::~PageOmniWheel()
{
    delete ui;
}

void PageOmniWheel::on_mainWindowStatusButton_clicked()
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

void PageOmniWheel::on_alwaysOnTopButton_clicked()
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

void PageOmniWheel::on_connectVrepButton_clicked()
{
    int para_status = 1;
    clientID = simxStart("127.0.0.1", 19997, true, true, 5000, 5);
    if(clientID!=-1){
        if (simxGetObjectHandle(clientID, "Wheel1", &jointWheel1, simx_opmode_blocking) != simx_return_ok)
           para_status = 0;
        if (simxGetObjectHandle(clientID, "Wheel2", &jointWheel2, simx_opmode_blocking) != simx_return_ok)
           para_status = 0;
        if (simxGetObjectHandle(clientID, "Wheel3", &jointWheel3, simx_opmode_blocking) != simx_return_ok)
           para_status = 0;
        if(para_status)
            ui->vrepStatusLabel->setText("Connected");
        else ui->vrepStatusLabel->setText("Connected,but not joints");
        ui->connectVrepButton->setEnabled(false);

    }else{
        ui->vrepStatusLabel->setText("Disconnected");
    }
}
void PageOmniWheel::sendVelsToVrep(float v1,float v2,float v3){
    simxFloat tarVel1 = v1;
    simxFloat tarVel2 = v2;
    simxFloat tarVel3 = v3;
    simxSetJointTargetVelocity(clientID, jointWheel1, tarVel1, simx_opmode_blocking);
    simxSetJointTargetVelocity(clientID, jointWheel2, tarVel2, simx_opmode_blocking);
    simxSetJointTargetVelocity(clientID, jointWheel3, tarVel3, simx_opmode_blocking);
//  应该校验是否发送成功的，暂时没有加
//if (simxSetJointTargetVelocity(clientID, Revolute_joint, tar_velo, simx_opmode_blocking) == simx_return_ok)//设置关节目标转速
}

void PageOmniWheel::on_generalSendVelButton_clicked()
{
    float v1 = ui->vel1SpinBox->value();
    float v2 = ui->vel2SpinBox->value();
    float v3 = ui->vel3SpinBox->value();
    sendVelsToVrep(v1,v2,v3);
}
