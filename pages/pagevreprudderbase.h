#ifndef PAGEVREPRUDDERBASE_H
#define PAGEVREPRUDDERBASE_H

#include <QMainWindow>
#include <QTimer>
extern "C"{
//#include "extApi.h"
//#include "extApiPlatform.h"
//#include "v_repLib.h"
}

namespace Ui {
class PageVrepRudderBase;
}

class PageVrepRudderBase : public QMainWindow
{
    Q_OBJECT

public:
    explicit PageVrepRudderBase(QWidget *parent = 0);
    ~PageVrepRudderBase();

private slots:
    void timer5ms();

    void on_actionalwaysOnTop_triggered();

    void on_mainWindowStatusButton_clicked();

    void on_alwaysOnTopButton_clicked();

    void on_connectVrepButton_clicked();

    void sendDirsToVrep(float d1,float d2,float d3,float d4);
    void sendVelsToVrep(float v1,float v2,float v3,float v4);

    void on_generalSendDirButton_clicked();

    void on_generalSendVelButton_clicked();

    void on_startSimulationButton_clicked();

    void on_endSimulationButton_clicked();

    void on_pauseSimulationButton_clicked();

signals:
    void showMainWindow();
    void hideMainWindow();

private:
    Ui::PageVrepRudderBase *ui;
    QTimer *timer_5ms;
    unsigned int timeMsCount = 0;
    unsigned int timeSCount = 0;
    bool mainWindowStatus = true;
    bool alwaysTopFlag = false;

    int clientID;
    simxInt jointDir1;
    simxInt jointDir2;
    simxInt jointDir3;
    simxInt jointDir4;
    simxInt jointVel1;
    simxInt jointVel2;
    simxInt jointVel3;
    simxInt jointVel4;
    simxInt objectCar;

    simxFloat carPosition[6];
};

#endif // PAGEVREPRUDDERBASE_H
