#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QListWidgetItem>
#include <cmath>
#include <QEventLoop>
#include <QDesktopServices>
#include "widgets/helpdialog.h"
#include "utility.h"

namespace
{

    void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
    {
        QByteArray localMsg = msg.toLocal8Bit();
        QString str;
        QString typeStr;
        bool isBad = false;

        switch (type)
        {
        case QtDebugMsg:
            typeStr = "DEBUG";
            break;
            //    case QtInfoMsg: typeStr = "INFO"; break;
        case QtWarningMsg:
            typeStr = "WARNING";
            isBad = true;
            break;
        case QtCriticalMsg:
            typeStr = "CRITICAL";
            isBad = true;
            break;
        case QtFatalMsg:
            typeStr = "FATAL";
            isBad = true;
            break;

        default:
            break;
        }

        str.sprintf("%s (%s:%u %s): %s", typeStr.toLocal8Bit().data(),
                    context.file, context.line, context.function, localMsg.constData());

        if (PageDebugPrint::currentMsgHandler)
        {
            QString strTmp;
            if (isBad)
            {
                strTmp = "<font color=\"red\">" + str + "</font><br>";
            }
            else
            {
                strTmp = str + "<br>";
            }

            QMetaObject::invokeMethod(PageDebugPrint::currentMsgHandler, "printConsole",
                                      Qt::QueuedConnection, Q_ARG(QString, strTmp));
        }

        printf("%s\n", str.toLocal8Bit().data());
        fflush(stdout);
    }
} // namespace

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mVersion = QString::number(VT_VERSION, 'f', 2);
    mVesc = new VescInterface(this);
    mStatusInfoTime = 0;
    mStatusLabel = new QLabel(this);
    ui->statusBar->addPermanentWidget(mStatusLabel);
    mTimer = new QTimer(this);

    connect(mTimer, SIGNAL(timeout()),
            this, SLOT(timerSlot()));
    connect(mVesc, SIGNAL(statusMessage(QString, bool)),
            this, SLOT(showStatusInfo(QString, bool)));
    connect(mVesc, SIGNAL(messageDialog(QString, QString, bool, bool)),
            this, SLOT(showMessageDialog(QString, QString, bool, bool)));
    connect(mVesc, SIGNAL(serialPortNotWritable(QString)),
            this, SLOT(serialPortNotWritable(QString)));
    connect(mVesc->commands(), SIGNAL(mcConfigCheckResult(QStringList)),
            this, SLOT(mcConfigCheckResult(QStringList)));
    connect(ui->actionAboutQt, SIGNAL(triggered(bool)),
            qApp, SLOT(aboutQt()));

    // Remove the menu with the option to hide the toolbar
    ui->mainToolBar->setContextMenuPolicy(Qt::PreventContextMenu);

    reloadPages();

    qApp->installEventFilter(this);
    qInstallMessageHandler(myMessageOutput);

    mTimer->start(20);

    // Restore size and position
    if (mSettings.contains("mainwindow/size"))
    {
        resize(mSettings.value("mainwindow/size").toSize());
    }

    if (mSettings.contains("mainwindow/position"))
    {
        move(mSettings.value("mainwindow/position").toPoint());
    }

    if (mSettings.contains("mainwindow/maximized"))
    {
        bool maximized = mSettings.value("mainwindow/maximized").toBool();
        if (maximized)
        {
            showMaximized();
        }
    }

    if (mSettings.contains("cmdText_1"))
    {
        ui->cmdSendEdit_1->setText(mSettings.value("cmdText_1").toString());
    }
    if (mSettings.contains("cmdText_2"))
    {
        ui->cmdSendEdit_2->setText(mSettings.value("cmdText_2").toString());
    }
    if (mSettings.contains("cmdText_3"))
    {
        ui->cmdSendEdit_3->setText(mSettings.value("cmdText_3").toString());
    }
    if (mSettings.contains("cmdText_4"))
    {
        ui->cmdSendEdit_4->setText(mSettings.value("cmdText_4").toString());
    }
    if (mSettings.contains("cmdText_5"))
    {
        ui->cmdSendEdit_5->setText(mSettings.value("cmdText_5").toString());
    }
    if (mSettings.contains("cmdText_6"))
    {
        ui->cmdSendEdit_6->setText(mSettings.value("cmdText_6").toString());
    }
    if (mSettings.contains("cmdText_7"))
    {
        ui->cmdSendEdit_7->setText(mSettings.value("cmdText_7").toString());
    }
    if (mSettings.contains("cmdText_8"))
    {
        ui->cmdSendEdit_8->setText(mSettings.value("cmdText_8").toString());
    }
    if (mSettings.contains("cmdText_9"))
    {
        ui->cmdSendEdit_9->setText(mSettings.value("cmdText_9").toString());
    }
    if (mSettings.contains("cmdText_0"))
    {
        ui->cmdSendEdit_0->setText(mSettings.value("cmdText_0").toString());
    }
    if (mSettings.contains("cmdText_11"))
    {
        ui->cmdSendEdit_11->setText(mSettings.value("cmdText_11").toString());
    }
    if (mSettings.contains("cmdText_12"))
    {
        ui->cmdSendEdit_12->setText(mSettings.value("cmdText_12").toString());
    }
    mPageDebugPrint->printConsole("Tool Box " + mVersion + " started<br>");
}

MainWindow::~MainWindow()
{
    // Save settings
    mSettings.setValue("version", mVersion);
    mSettings.setValue("introVersion", VT_INTRO_VERSION);
    mSettings.setValue("mainwindow/position", pos());
    mSettings.setValue("mainwindow/maximized", isMaximized());

    mSettings.setValue("cmdText_1", ui->cmdSendEdit_1->text());
    mSettings.setValue("cmdText_2", ui->cmdSendEdit_2->text());
    mSettings.setValue("cmdText_3", ui->cmdSendEdit_3->text());
    mSettings.setValue("cmdText_4", ui->cmdSendEdit_4->text());
    mSettings.setValue("cmdText_5", ui->cmdSendEdit_5->text());
    mSettings.setValue("cmdText_6", ui->cmdSendEdit_6->text());
    mSettings.setValue("cmdText_7", ui->cmdSendEdit_7->text());
    mSettings.setValue("cmdText_8", ui->cmdSendEdit_8->text());
    mSettings.setValue("cmdText_9", ui->cmdSendEdit_9->text());
    mSettings.setValue("cmdText_0", ui->cmdSendEdit_0->text());
    mSettings.setValue("cmdText_11", ui->cmdSendEdit_11->text());
    mSettings.setValue("cmdText_12", ui->cmdSendEdit_12->text());

    if (!isMaximized())
    {
        mSettings.setValue("mainwindow/size", size());
    }

    delete ui;
}

bool MainWindow::eventFilter(QObject *object, QEvent *e)
{
    Q_UNUSED(object);

    if (!mVesc->isPortConnected() || !ui->actionKeyboardControl->isChecked())
    {
        return false;
    }

    if (e->type() == QEvent::KeyPress || e->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        bool isPress = e->type() == QEvent::KeyPress;

        switch (keyEvent->key())
        {
        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_Left:
        case Qt::Key_Right:
        case Qt::Key_PageDown:
        case Qt::Key_0:
        case Qt::Key_1:
        case Qt::Key_2:
        case Qt::Key_3:
        case Qt::Key_4:
        case Qt::Key_5:
        case Qt::Key_6:
        case Qt::Key_7:
        case Qt::Key_8:
        case Qt::Key_9:
            break;
        default:
            return false;
        }

        if (keyEvent->isAutoRepeat())
        {
            return true;
        }

        switch (keyEvent->key())
        {
        case Qt::Key_Up:
            if (isPress)
            {
            }
            else
            {
            }
            break;

        case Qt::Key_Down:
            if (isPress)
            {
            }
            else
            {
            }
            break;

        case Qt::Key_Left:
            if (isPress)
            {
            }
            else
            {
            }
            break;

        case Qt::Key_Right:
            if (isPress)
            {
            }
            else
            {
            }
            break;

        case Qt::Key_PageDown:
            if (isPress)
            {
            }
            else
            {
            }
            break;

        case Qt::Key_0:
            if (isPress)
            {
                on_cmdSendEdit_0_returnPressed();
            }
            else
            {
            }
            break;
        case Qt::Key_1:
            if (isPress)
            {
                on_cmdSendEdit_1_returnPressed();
            }
            else
            {
            }
            break;
        case Qt::Key_2:
            if (isPress)
            {
                on_cmdSendEdit_2_returnPressed();
            }
            else
            {
            }
            break;
        case Qt::Key_3:
            if (isPress)
            {
                on_cmdSendEdit_3_returnPressed();
            }
            else
            {
            }
            break;
        case Qt::Key_4:
            if (isPress)
            {
                on_cmdSendEdit_4_returnPressed();
            }
            else
            {
            }
            break;
        case Qt::Key_5:
            if (isPress)
            {
                on_cmdSendEdit_5_returnPressed();
            }
            else
            {
            }
            break;
        case Qt::Key_6:
            if (isPress)
            {
                on_cmdSendEdit_6_returnPressed();
            }
            else
            {
            }
            break;
        case Qt::Key_7:
            if (isPress)
            {
                on_cmdSendEdit_7_returnPressed();
            }
            else
            {
            }
            break;
        case Qt::Key_8:
            if (isPress)
            {
                on_cmdSendEdit_8_returnPressed();
            }
            else
            {
            }
            break;
        case Qt::Key_9:
            if (isPress)
            {
                on_cmdSendEdit_9_returnPressed();
            }
            else
            {
            }
            break;
        default:
            break;
        }

        return true;
    }

    return false;
}

void MainWindow::timerSlot()
{
    // Update status label
    if (mStatusInfoTime)
    {
        mStatusInfoTime--;
        if (!mStatusInfoTime)
        {
            mStatusLabel->setStyleSheet(qApp->styleSheet());
        }
    }
    else
    {
        QString str = mVesc->getConnectedPortName();
        if (str != mStatusLabel->text())
        {
            mStatusLabel->setText(mVesc->getConnectedPortName());
            static QString statusLast = "";
            if (str != statusLast)
            {
                mPageDebugPrint->printConsole("Status: " + str + "<br>");
                statusLast = str;
            }
        }
    }
}

void MainWindow::showStatusInfo(QString info, bool isGood)
{
    if (isGood)
    {
        mStatusLabel->setStyleSheet("QLabel { background-color : lightgreen; color : black; }");
        mPageDebugPrint->printConsole("Status: " + info + "<br>");
    }
    else
    {
        mStatusLabel->setStyleSheet("QLabel { background-color : red; color : black; }");
        mPageDebugPrint->printConsole("<font color=\"red\">Status: " + info + "</font><br>");
    }

    mStatusInfoTime = 80;
    mStatusLabel->setText(info);
}

void MainWindow::showMessageDialog(const QString &title, const QString &msg, bool isGood, bool richText)
{
    (void)richText;

    if (isGood)
    {
        QMessageBox::information(this, title, msg);
    }
    else
    {
        QMessageBox::warning(this, title, msg);
    }
}

void MainWindow::serialPortNotWritable(const QString &port)
{
    (void)port;

#ifdef Q_OS_LINUX
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this,
                                 tr("Connect Serial Port"),
                                 tr("The serial port is not writable. This can usually be fixed by "
                                    "adding your user to the dialout, uucp and/or lock groups. Would "
                                    "you like to do that?"),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    if (reply == QMessageBox::Yes)
    {
        QString name = qgetenv("USER");
        if (name.isEmpty())
        {
            name = qgetenv("USERNAME");
        }

        bool hasDialout = !runCmd("getent", QStringList() << "group"
                                                          << "dialout")
                               .isEmpty();
        bool hasUucp = !runCmd("getent", QStringList() << "group"
                                                       << "uucp")
                            .isEmpty();
        bool hasLock = !runCmd("getent", QStringList() << "group"
                                                       << "lock")
                            .isEmpty();

        QString grps;
        if (hasDialout)
        {
            grps += "dialout";
        }

        if (hasUucp)
        {
            if (!grps.isEmpty())
            {
                grps += ",";
            }
            grps += "uucp";
        }

        if (hasLock)
        {
            if (!grps.isEmpty())
            {
                grps += ",";
            }
            grps += "lock";
        }

        QProcess process;
        process.setEnvironment(QProcess::systemEnvironment());
        process.start("pkexec", QStringList() << "usermod"
                                              << "-aG" << grps << name);
        waitProcess(process);
        if (process.exitCode() == 0)
        {
            showMessageDialog(tr("Command Result"),
                              tr("Result from command:\n\n"
                                 "%1\n"
                                 "You have to reboot for this "
                                 "change to take effect.")
                                  .arg(QString(process.readAllStandardOutput())),
                              true, false);
        }
        else
        {
            showMessageDialog(tr("Command Result"),
                              tr("Running command failed."),
                              false, false);
        }
        process.close();
    }
#endif
}

void MainWindow::on_actionReconnect_triggered()
{
    mVesc->reconnectLastPort();
}

void MainWindow::on_actionDisconnect_triggered()
{
    mVesc->disconnectPort();
}

void MainWindow::on_actionExit_triggered()
{
    qApp->exit();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "Tool Box", Utility::aboutText());
}

void MainWindow::addPageItem(QString name, QString icon, QString groupIcon, bool bold, bool indented)
{
    QListWidgetItem *item = new QListWidgetItem();
    ui->pageList->addItem(item);
    PageListItem *li = new PageListItem(name, icon, groupIcon, this);
    li->setBold(bold);
    li->setIndented(indented);
    ui->pageList->setItemWidget(item, li);
}

void MainWindow::showPage(const QString &name)
{
    for (int i = 0; i < ui->pageList->count(); i++)
    {
        PageListItem *p = (PageListItem *)(ui->pageList->itemWidget(ui->pageList->item(i)));
        if (p->name() == name)
        {
            ui->pageList->setCurrentRow(i);
            break;
        }
    }
}

void MainWindow::reloadPages()
{
    // Remove pages (if any)
    ui->pageList->clear();
    while (ui->pageWidget->count() != 0)
    {
        QWidget *widget = ui->pageWidget->widget(0);
        ui->pageWidget->removeWidget(widget);
        widget->deleteLater();
    }

    mPageWelcome = new PageWelcome(this);
    mPageWelcome->setVesc(mVesc);
    ui->pageWidget->addWidget(mPageWelcome);
    addPageItem(tr("Welcome & Wizards"), "://res/icons/Home-96.png", "", true);

    mPageConnection = new PageConnection(this);
    mPageConnection->setVesc(mVesc);
    ui->pageWidget->addWidget(mPageConnection);
    addPageItem(tr("Connection"), "://res/icons/Connected-96.png", "", true);

    //    mPageFirmware = new PageFirmware(this);
    //    mPageFirmware->setVesc(mVesc);
    //    ui->pageWidget->addWidget(mPageFirmware);
    //    addPageItem(tr("VESC Firmware"), "://res/icons/Electronics-96.png", "", true);

    mPageDataAnalysis = new PageDataAnalysis(this);
    mPageDataAnalysis->setVesc(mVesc);
    ui->pageWidget->addWidget(mPageDataAnalysis);
    addPageItem(tr("Data Analysis"), "://res/icons/Line Chart-96.png", "", true);

    mPageSerialAnalysis = new PageSerialAnalysis(this);
    mPageSerialAnalysis->setVesc(mVesc);
    ui->pageWidget->addWidget(mPageSerialAnalysis);
    addPageItem(tr("Serial Analysis"), "://res/icons/Waypoint Map-96.png", "", false, true);

    mPageImu = new PageImu(this);
    mPageImu->setVesc(mVesc);
    ui->pageWidget->addWidget(mPageImu);
    addPageItem(tr("IMU Data"), "://res/icons/Line Chart-96.png", "", false, true);

    mPagePath = new PagePath(this);
    mPagePath->setVesc(mVesc);
    ui->pageWidget->addWidget(mPagePath);
    addPageItem(tr("路径规划"), "://res/icons/Line Chart-96.png", "", false, true);

    mPageNone = new PageNone(this);
    mPageNone->setVesc(mVesc);
    ui->pageWidget->addWidget(mPageNone);
    addPageItem(tr("Page None"), "://res/icons/Line Chart-96.png", "", false, true);

    mPageDebugPrint = new PageDebugPrint(this);
    ui->pageWidget->addWidget(mPageDebugPrint);
    addPageItem(tr("Debug Console"), "://res/icons/Bug-96.png", "", true);

    mPageSettings = new PageSettings(this);
    ui->pageWidget->addWidget(mPageSettings);
    addPageItem(tr("Settings"), "://res/icons/Settings-96.png", "", true);

    // Adjust sizes
    QFontMetrics fm(this->font());
    int width = fm.width("Welcome & Wizards++++++");
    int height = fm.height();

    for (int i = 0; i < ui->pageList->count(); i++)
    {
        QListWidgetItem *item = ui->pageList->item(i);
        item->setSizeHint(QSize(item->sizeHint().width(), height));
    }

    ui->pageList->setMinimumWidth(width);
    ui->pageList->setMaximumWidth(width);
    ui->pageLabel->setMaximumWidth(width);
    ui->pageLabel->setMaximumHeight((394 * width) / 1549);

    ui->pageList->setCurrentRow(0);
    ui->pageWidget->setCurrentIndex(0);
}

void MainWindow::checkUdev()
{
    // Check if udev rules for modemmanager are installed
#ifdef Q_OS_LINUX
    QFileInfo fi_mm("/lib/udev/rules.d/77-mm-usb-device-blacklist.rules");
    if (fi_mm.exists())
    {
        QFileInfo fi_vesc("/lib/udev/rules.d/45-vesc.rules");
        if (!fi_vesc.exists())
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::information(this,
                                             tr("Modemmenager"),
                                             tr("It looks like modemmanager is installed on your system, and that "
                                                "there are no VESC udev rules installed. This will cause a delay "
                                                "from when you plug in the VESC until you can use it. Would you like "
                                                "to add a udev rule to prevent modemmanager from grabbing the VESC?"),
                                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

            if (reply == QMessageBox::Yes)
            {
                QFile f_vesc(QDir::temp().absoluteFilePath(fi_vesc.fileName()));
                if (!f_vesc.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    showMessageDialog(tr("Create File Error"),
                                      f_vesc.errorString(),
                                      false, false);
                    return;
                }

                f_vesc.write("# Prevent modemmanager from grabbing the VESC\n"
                             "ATTRS{idVendor}==\"0483\", ATTRS{idProduct}==\"5740\", ENV{ID_MM_DEVICE_IGNORE}=\"1\"\n");
                f_vesc.close();

                QFileInfo fi_new(f_vesc);
                QProcess process;
                process.setEnvironment(QProcess::systemEnvironment());
                process.start("pkexec", QStringList() << "mv" << fi_new.absoluteFilePath() << fi_vesc.absolutePath());
                waitProcess(process);

                if (process.exitCode() == 0)
                {
                    QMessageBox::StandardButton reply;
                    reply = QMessageBox::information(this,
                                                     tr("Modemmenager"),
                                                     tr("The udev rule was created successfully. Would you like "
                                                        "to reload udev to apply the new rule?"),
                                                     QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

                    if (reply == QMessageBox::Yes)
                    {
                        QProcess process;
                        process.setEnvironment(QProcess::systemEnvironment());
                        process.start("pkexec", QStringList() << "udevadm"
                                                              << "control"
                                                              << "--reload-rules");
                        waitProcess(process);

                        if (process.exitCode() == 0)
                        {
                            showMessageDialog(tr("Command Result"),
                                              tr("Reloaded udev rules sucessfully."),
                                              true, false);
                        }
                        else
                        {
                            QString out = process.readAll();

                            if (out.isEmpty())
                            {
                                showMessageDialog(tr("Command Result"),
                                                  tr("Could not reload udev rules. A reboot is probably "
                                                     "required for this change to take effect."),
                                                  false, false);
                            }
                        }
                        process.close();
                    }
                }
                else
                {
                    showMessageDialog(tr("Command Result"),
                                      tr("Could not move rules file:\n\n"
                                         "%1")
                                          .arg(QString(process.readAllStandardOutput())),
                                      false, false);
                }
                process.close();
            }
        }
    }
#endif
}

bool MainWindow::waitProcess(QProcess &process, bool block, int timeoutMs)
{
    bool wasEnables = isEnabled();
    bool killed = false;

    if (block)
    {
        setEnabled(false);
    }

    process.waitForStarted();

    QEventLoop loop;
    QTimer timeoutTimer;
    timeoutTimer.setSingleShot(true);
    timeoutTimer.start(timeoutMs);
    connect(&process, SIGNAL(finished(int)), &loop, SLOT(quit()));
    connect(&timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));
    loop.exec();

    if (process.state() == QProcess::Running)
    {
        process.kill();
        process.waitForFinished();
        killed = true;
    }

    setEnabled(wasEnables);

    return !killed;
}

QString MainWindow::runCmd(QString cmd, QStringList args)
{
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.start(cmd, args);
    waitProcess(process);
    QString res = process.readAllStandardOutput();
    process.close();
    return res;
}

void MainWindow::on_pageList_currentRowChanged(int currentRow)
{
    if (currentRow >= 0)
    {
        ui->pageWidget->setCurrentIndex(currentRow);
    }
}

void MainWindow::on_actionVESCToolChangelog_triggered()
{
    HelpDialog::showHelp(this, "Tool Box Changelog", Utility::vescToolChangeLog());
}

void MainWindow::on_cmdSendButton_1_clicked()
{
    if (mVesc)
    {
        if (mVesc->getTxProtocolState())
        {
            mVesc->commands()->sendSerialCmd(ui->cmdSendEdit_1->text());
        }
        else
        {
            mVesc->commands()->sendSerialCmdNoProtocol(ui->cmdSendEdit_1->text());
        }
    }
}

void MainWindow::on_cmdSendButton_2_clicked()
{
    if (mVesc)
    {
        if (mVesc->getTxProtocolState())
        {
            mVesc->commands()->sendSerialCmd(ui->cmdSendEdit_2->text());
        }
        else
        {
            mVesc->commands()->sendSerialCmdNoProtocol(ui->cmdSendEdit_2->text());
        }
    }
}

void MainWindow::on_cmdSendButton_3_clicked()
{
    if (mVesc)
    {
        if (mVesc->getTxProtocolState())
        {
            mVesc->commands()->sendSerialCmd(ui->cmdSendEdit_3->text());
        }
        else
        {
            mVesc->commands()->sendSerialCmdNoProtocol(ui->cmdSendEdit_3->text());
        }
    }
}

void MainWindow::on_cmdSendButton_4_clicked()
{
    if (mVesc)
    {
        if (mVesc->getTxProtocolState())
        {
            mVesc->commands()->sendSerialCmd(ui->cmdSendEdit_4->text());
        }
        else
        {
            mVesc->commands()->sendSerialCmdNoProtocol(ui->cmdSendEdit_4->text());
        }
    }
}

void MainWindow::on_cmdSendButton_5_clicked()
{
    if (mVesc)
    {
        if (mVesc->getTxProtocolState())
        {
            mVesc->commands()->sendSerialCmd(ui->cmdSendEdit_5->text());
        }
        else
        {
            mVesc->commands()->sendSerialCmdNoProtocol(ui->cmdSendEdit_5->text());
        }
    }
}

void MainWindow::on_cmdSendButton_6_clicked()
{
    if (mVesc)
    {
        if (mVesc->getTxProtocolState())
        {
            mVesc->commands()->sendSerialCmd(ui->cmdSendEdit_6->text());
        }
        else
        {
            mVesc->commands()->sendSerialCmdNoProtocol(ui->cmdSendEdit_6->text());
        }
    }
}

void MainWindow::on_cmdSendButton_7_clicked()
{
    if (mVesc)
    {
        if (mVesc->getTxProtocolState())
        {
            mVesc->commands()->sendSerialCmd(ui->cmdSendEdit_7->text());
        }
        else
        {
            mVesc->commands()->sendSerialCmdNoProtocol(ui->cmdSendEdit_7->text());
        }
    }
}

void MainWindow::on_cmdSendButton_8_clicked()
{
    if (mVesc)
    {
        if (mVesc->getTxProtocolState())
        {
            mVesc->commands()->sendSerialCmd(ui->cmdSendEdit_8->text());
        }
        else
        {
            mVesc->commands()->sendSerialCmdNoProtocol(ui->cmdSendEdit_8->text());
        }
    }
}

void MainWindow::on_cmdSendButton_9_clicked()
{
    if (mVesc)
    {
        if (mVesc->getTxProtocolState())
        {
            mVesc->commands()->sendSerialCmd(ui->cmdSendEdit_9->text());
        }
        else
        {
            mVesc->commands()->sendSerialCmdNoProtocol(ui->cmdSendEdit_9->text());
        }
    }
}

void MainWindow::on_cmdSendButton_0_clicked()
{
    if (mVesc)
    {
        if (mVesc->getTxProtocolState())
        {
            mVesc->commands()->sendSerialCmd(ui->cmdSendEdit_0->text());
        }
        else
        {
            mVesc->commands()->sendSerialCmdNoProtocol(ui->cmdSendEdit_0->text());
        }
    }
}

void MainWindow::on_cmdSendButton_11_clicked()
{
    if (mVesc)
    {
        if (mVesc->getTxProtocolState())
        {
            mVesc->commands()->sendSerialCmd(ui->cmdSendEdit_11->text());
        }
        else
        {
            mVesc->commands()->sendSerialCmdNoProtocol(ui->cmdSendEdit_11->text());
        }
    }
}

void MainWindow::on_cmdSendButton_12_clicked()
{
    if (mVesc)
    {
        if (mVesc->getTxProtocolState())
        {
            mVesc->commands()->sendSerialCmd(ui->cmdSendEdit_12->text());
        }
        else
        {
            mVesc->commands()->sendSerialCmdNoProtocol(ui->cmdSendEdit_12->text());
        }
    }
}

void MainWindow::on_cmdSendEdit_1_returnPressed()
{
    on_cmdSendButton_1_clicked();
}

void MainWindow::on_cmdSendEdit_2_returnPressed()
{
    on_cmdSendButton_2_clicked();
}

void MainWindow::on_cmdSendEdit_3_returnPressed()
{
    on_cmdSendButton_3_clicked();
}

void MainWindow::on_cmdSendEdit_4_returnPressed()
{
    on_cmdSendButton_4_clicked();
}

void MainWindow::on_cmdSendEdit_5_returnPressed()
{
    on_cmdSendButton_5_clicked();
}

void MainWindow::on_cmdSendEdit_6_returnPressed()
{
    on_cmdSendButton_6_clicked();
}

void MainWindow::on_cmdSendEdit_7_returnPressed()
{
    on_cmdSendButton_7_clicked();
}

void MainWindow::on_cmdSendEdit_8_returnPressed()
{
    on_cmdSendButton_8_clicked();
}

void MainWindow::on_cmdSendEdit_9_returnPressed()
{
    on_cmdSendButton_9_clicked();
}

void MainWindow::on_cmdSendEdit_0_returnPressed()
{
    on_cmdSendButton_0_clicked();
}

void MainWindow::on_cmdSendEdit_11_returnPressed()
{
    on_cmdSendEdit_11_returnPressed();
}

void MainWindow::on_cmdSendEdit_12_returnPressed()
{
    on_cmdSendEdit_12_returnPressed();
}

//void MainWindow::on_actionRudderBase_triggered()
//{
//    //this->hide();//主界面关闭
//    PageVrepRudderBase *mPageVrepRudderBase = new PageVrepRudderBase(this);//新建子界面
//    connect(mPageVrepRudderBase,SIGNAL(showMainWindow()),this,SLOT(reshow()));
//    connect(mPageVrepRudderBase,SIGNAL(hideMainWindow()),this,SLOT(hide()));
//    //connect(videodlg,SIGNAL(sendsignal()),this,SLOT(reshow()));//当点击子界面时，调用主界面的reshow()函数
//    mPageVrepRudderBase->show();//子界面出现
//}
//void MainWindow::reshow(){
//    this->show();
//}

//void MainWindow::on_actionOmni_Wheel_triggered()
//{
//    //this->hide();//主界面关闭
//    PageOmniWheel *mPageOmniWheel = new PageOmniWheel(this);//新建子界面
//    connect(mPageOmniWheel,SIGNAL(showMainWindow()),this,SLOT(reshow()));
//    connect(mPageOmniWheel,SIGNAL(hideMainWindow()),this,SLOT(hide()));
//    //connect(videodlg,SIGNAL(sendsignal()),this,SLOT(reshow()));//当点击子界面时，调用主界面的reshow()函数
//    mPageOmniWheel->show();//子界面出现
//}

void MainWindow::on_actionTxPControl_triggered(bool checked)
{
    mVesc->setTxProtocolState(checked);
}

void MainWindow::on_actionRxPControl_triggered(bool checked)
{
    mVesc->setRxProtocolState(checked);
}
