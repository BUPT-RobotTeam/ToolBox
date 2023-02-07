#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QProcess>
#include <QSettings>
#include "vescinterface.h"
#include "widgets/pagelistitem.h"
#include "pages/pagewelcome.h"
#include "pages/pageconnection.h"
#include "pages/pagedataanalysis.h"
//#include "pages/pagefirmware.h"
#include "pages/pagedebugprint.h"
#include "pages/pagesettings.h"
#include "pages/pageimu.h"
#include "pages/pageloganalysis.h"
#include "pages/pageserialanalysis.h"
#include "pages/pagenone.h"
#include "pages/pagepath.h"
//#include "pages/pagevreprudderbase.h"
//#include "pages/pageomniwheel.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool eventFilter(QObject *object, QEvent *e);

private slots:
    //    void reshow();
    void timerSlot();
    void showStatusInfo(QString info, bool isGood);
    void showMessageDialog(const QString &title, const QString &msg, bool isGood, bool richText);
    void serialPortNotWritable(const QString &port);

    void on_actionReconnect_triggered();
    void on_actionDisconnect_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_pageList_currentRowChanged(int currentRow);
    void on_actionVESCToolChangelog_triggered();

    void on_cmdSendButton_1_clicked();

    void on_cmdSendButton_2_clicked();

    void on_cmdSendButton_3_clicked();

    void on_cmdSendButton_4_clicked();

    void on_cmdSendButton_5_clicked();

    void on_cmdSendButton_6_clicked();

    void on_cmdSendButton_7_clicked();

    void on_cmdSendButton_8_clicked();

    void on_cmdSendButton_9_clicked();

    void on_cmdSendButton_0_clicked();

    void on_cmdSendButton_11_clicked();

    void on_cmdSendButton_12_clicked();

    void on_cmdSendEdit_1_returnPressed();

    void on_cmdSendEdit_2_returnPressed();

    void on_cmdSendEdit_3_returnPressed();

    void on_cmdSendEdit_4_returnPressed();

    void on_cmdSendEdit_5_returnPressed();

    void on_cmdSendEdit_6_returnPressed();

    void on_cmdSendEdit_7_returnPressed();

    void on_cmdSendEdit_8_returnPressed();

    void on_cmdSendEdit_9_returnPressed();

    void on_cmdSendEdit_0_returnPressed();

    void on_cmdSendEdit_11_returnPressed();

    void on_cmdSendEdit_12_returnPressed();

    //    void on_actionRudderBase_triggered();

    //    void on_actionOmni_Wheel_triggered();

    void on_actionTxPControl_triggered(bool checked);

    void on_actionRxPControl_triggered(bool checked);

private:
    Ui::MainWindow *ui;

    QSettings mSettings;
    QString mVersion;
    VescInterface *mVesc;
    QTimer *mTimer;
    QLabel *mStatusLabel;
    int mStatusInfoTime;
    bool mKeyLeft;
    bool mKeyRight;

    PageWelcome *mPageWelcome;
    PageConnection *mPageConnection;
    PageDataAnalysis *mPageDataAnalysis;
    PageImu *mPageImu;
    //    PageFirmware *mPageFirmware;
    PageDebugPrint *mPageDebugPrint;
    PageSettings *mPageSettings;
    PageSerialAnalysis *mPageSerialAnalysis;
    PageNone *mPageNone;
    PagePath *mPagePath;

    void addPageItem(QString name,
                     QString icon = "",
                     QString groupIcon = "",
                     bool bold = false,
                     bool indented = false);
    void showPage(const QString &name);
    void reloadPages();
    void checkUdev();
    bool waitProcess(QProcess &process, bool block = true, int timeoutMs = 300000);
    QString runCmd(QString cmd, QStringList args);
};

#endif // MAINWINDOW_H
