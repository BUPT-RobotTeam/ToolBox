#ifndef PAGEOMNIWHEEL_H
#define PAGEOMNIWHEEL_H

#include <QMainWindow>
extern "C"{
//#include "extApi.h"
//#include "extApiPlatform.h"
//#include "v_repLib.h"
}

namespace Ui {
class PageOmniWheel;
}

class PageOmniWheel : public QMainWindow
{
    Q_OBJECT

public:
    explicit PageOmniWheel(QWidget *parent = 0);
    ~PageOmniWheel();
signals:
    void showMainWindow();
    void hideMainWindow();

private slots:
    void on_mainWindowStatusButton_clicked();

    void on_alwaysOnTopButton_clicked();

    void on_connectVrepButton_clicked();

    void on_generalSendVelButton_clicked();
    void sendVelsToVrep(float v1,float v2,float v3);

private:
    Ui::PageOmniWheel *ui;

    bool mainWindowStatus = true;
    bool alwaysTopFlag = false;
    int clientID;
    simxInt jointWheel1;
    simxInt jointWheel2;
    simxInt jointWheel3;
};

#endif // PAGEOMNIWHEEL_H
