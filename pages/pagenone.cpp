#include "pagenone.h"
#include "ui_pagenone.h"
extern "C"{
//#include "extApi.h"
//#include "extApiPlatform.h"
//#include "v_repLib.h"
}

PageNone::PageNone(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageNone)
{
    ui->setupUi(this);
    mVesc = 0;
}

VescInterface *PageNone::vesc() const
{
    return mVesc;
}

void PageNone::setVesc(VescInterface *vesc)
{
    mVesc = vesc;

    if (mVesc) {

    }
}

PageNone::~PageNone()
{
    delete ui;
}

void PageNone::on_pushButton_clicked()
{
//    clientID = simxStart("127.0.0.1", 19997, true, true, 5000, 5);
//    if(clientID!=-1){
//        ui->label_2->setText("Sucess");
//    }else{
//        ui->label_2->setText("Error");
//    }
}

void PageNone::on_pushButton_2_clicked()
{
//    simxInt Revolute_joint;
//    if (simxGetObjectHandle(clientID, "Revolute_joint", &Revolute_joint, simx_opmode_blocking) == simx_return_ok)//获得关节句柄，若成功
//            {
//                // here we have the joint handle in variable jointHandle!
//                ui->label_3->setText("Successfully");

//                simxFloat tar_velo = ui->doubleSpinBox->value();//设置一个变量存储关节目标转速
//                if (simxSetJointTargetVelocity(clientID, Revolute_joint, tar_velo, simx_opmode_blocking) == simx_return_ok)//设置关节目标转速
//                    ui->label_3->setText("target velocity");
//                else ui->label_3->setText("angle set failed.");
//            }
//            else  ui->label_3->setText("Wrong");

}
