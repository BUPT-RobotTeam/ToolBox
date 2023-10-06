#include "pageserialanalysis.h"
#include "ui_pageserialanalysis.h"

PageSerialAnalysis::PageSerialAnalysis(QWidget *parent) : QWidget(parent),
                                                          ui(new Ui::PageSerialAnalysis)
{
    ui->setupUi(this);
    mVesc = 0;

    mTimer = new QTimer(this);
    mTimer->start(5);

    mSecondCounter = 0.0;
    mLastUpdateTime = 0;
    mMaxPoints = 1000;
    mXaxisStep = 0.005;
    ui->maxPointsSpinBox->setValue(mMaxPoints);
    ui->xAxisStepDoubleSpinBox->setValue(mXaxisStep);

    mUpdateGeneralPlot = false;
    mUpdateButtonCheck = true;
    //ui->verticalLayout->set
    ui->generalPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    //general plot with ten channals
    QFont legendFont = font();
    legendFont.setPointSize(9);

    ui->generalPlot->legend->setVisible(true);
    ui->generalPlot->legend->setFont(legendFont);
    ui->generalPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignLeft);
    ui->generalPlot->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
    ui->generalPlot->xAxis->setLabel("Second (s)");

    if (mSettings.contains("lastcsvfile"))
    {
        ui->csvFileEdit->setText(mSettings.value("lastcsvfile").toString());
    }
    if (mSettings.contains("CH0_checkStatus"))
    {
        ui->checkBox_0->setChecked(mSettings.value("CH0_checkStatus").toBool());
    }
    if (mSettings.contains("CH1_checkStatus"))
    {
        ui->checkBox_1->setChecked(mSettings.value("CH1_checkStatus").toBool());
    }
    if (mSettings.contains("CH2_checkStatus"))
    {
        ui->checkBox_2->setChecked(mSettings.value("CH2_checkStatus").toBool());
    }
    if (mSettings.contains("CH3_checkStatus"))
    {
        ui->checkBox_3->setChecked(mSettings.value("CH3_checkStatus").toBool());
    }
    if (mSettings.contains("CH4_checkStatus"))
    {
        ui->checkBox_4->setChecked(mSettings.value("CH4_checkStatus").toBool());
    }
    if (mSettings.contains("CH5_checkStatus"))
    {
        ui->checkBox_5->setChecked(mSettings.value("CH5_checkStatus").toBool());
    }
    if (mSettings.contains("CH6_checkStatus"))
    {
        ui->checkBox_6->setChecked(mSettings.value("CH6_checkStatus").toBool());
    }
    if (mSettings.contains("CH7_checkStatus"))
    {
        ui->checkBox_7->setChecked(mSettings.value("CH7_checkStatus").toBool());
    }
    //    if (mSettings.contains("CH8_checkStatus")) {
    //        ui->checkBox_8->setChecked(mSettings.value("CH8_checkStatus").toBool());
    //    }
    //    if (mSettings.contains("CH9_checkStatus")) {
    //        ui->checkBox_9->setChecked(mSettings.value("CH9_checkStatus").toBool());
    //    }
    if (mSettings.contains("enableLogStatus"))
    {
        ui->csvEnableLogBox->setChecked(mSettings.value("enableLogStatus").toBool());
    }
    if (ui->csvEnableLogBox->isChecked())
    {
        if (mVesc)
        {
            mVesc->openRtLogFile(ui->csvFileEdit->text());
        }
    }

    connect(mTimer, SIGNAL(timeout()),
            this, SLOT(timerSlot()));
    connect(ui->generalPlot, &QCustomPlot::mouseMove, this, &PageSerialAnalysis::myMoveEvent);

    //    QCPCurve *fermatSpiral1 = new QCPCurve(ui->xyplot->xAxis,ui->xyplot->yAxis); //创建实例对象
    //    const int pointCount = 500;                                          //数据量
    //    QVector<QCPCurveData> dataSpiral1(pointCount);                 //元素数组
    //        for (int i=0; i<pointCount; ++i)
    //        {

    //           double phi = i/(double)(pointCount-1)*8*3.14159;
    //           double theta = i/(double)(pointCount-1)*2*3.14159;
    //           dataSpiral1[i] = QCPCurveData(i, qSqrt(phi)*qCos(phi), qSqrt(phi)*qSin(phi));
    //           //dataSpiral1[i] = QCPCurveData(i, key, value);
    //           //t->生成点的个数，key->x轴，value->y轴
    //        }
    //        // pass the data to the curves; we know t (i in loop above) is ascending, so set alreadySorted=true (saves an extra internal sort):
    //        fermatSpiral1->data()->set(dataSpiral1, true);
    //        // color the curves:
    //        fermatSpiral1->setPen(QPen(Qt::blue));
    //        fermatSpiral1->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 4);
}

VescInterface *PageSerialAnalysis::vesc() const
{
    return mVesc;
}

void PageSerialAnalysis::setVesc(VescInterface *vesc)
{
    mVesc = vesc;

    if (mVesc)
    {
        connect(mVesc->commands(), SIGNAL(monitorReceived(MONITOR_VALUES, uint)),
                this, SLOT(monitorReceived(MONITOR_VALUES, uint)));
        connect(mVesc->commands(), SIGNAL(printCmdFeedback(QString)),
                this, SLOT(printCmdFeedback(QString)));
    }
}

void PageSerialAnalysis::monitorReceived(MONITOR_VALUES values, unsigned mask)
{
    //qDebug()<<"received"<<values.ch0<<"  "<<values.ch1;
    (void)mask;
    updateMonitorLabel(values);
    // const int maxS = 1000;

    appendDoubleAndTrunc(&mCH0, values.ch0, mMaxPoints);
    //mCH1.append(values.ch0);
    //mCH1.append(values.ch0);
    appendDoubleAndTrunc(&mCH1, values.ch1, mMaxPoints);
    appendDoubleAndTrunc(&mCH2, values.ch2, mMaxPoints);
    appendDoubleAndTrunc(&mCH3, values.ch3, mMaxPoints);
    appendDoubleAndTrunc(&mCH4, values.ch4, mMaxPoints);
    appendDoubleAndTrunc(&mCH5, values.ch5, mMaxPoints);
    appendDoubleAndTrunc(&mCH6, values.ch6, mMaxPoints);
    appendDoubleAndTrunc(&mCH7, values.ch7, mMaxPoints);
    appendDoubleAndTrunc(&mCH8, values.ch8, mMaxPoints);
    appendDoubleAndTrunc(&mCH9, values.ch9, mMaxPoints);

    qint64 tNow = QDateTime::currentMSecsSinceEpoch();

    double elapsed = double((tNow - mLastUpdateTime)) / 1000.0;
    if (elapsed > 1.0)
    {
        elapsed = 1.0;
    }
    if (mXaxisStep == 0)
    {
        mSecondCounter += elapsed;
    }
    else
    {
        mSecondCounter += mXaxisStep;
    }

    appendDoubleAndTrunc(&mSeconds, mSecondCounter, mMaxPoints);

    mLastUpdateTime = tNow;

    mUpdateGeneralPlot = true;
}

void PageSerialAnalysis::appendDoubleAndTrunc(QVector<double> *vec, double num, int maxSize)
{
    vec->append(num);

    if (vec->size() > maxSize)
    {
        vec->remove(0, vec->size() - maxSize);
    }
}

void PageSerialAnalysis::timerSlot()
{

    if (mVesc)
    {
        if (mVesc->isRtLogOpen() != ui->csvEnableLogBox->isChecked())
        {
            ui->csvEnableLogBox->setChecked(mVesc->isRtLogOpen());
        }
    }
    if (mUpdateButtonCheck && mUpdateGeneralPlot)
    {
        int dataSize = mSeconds.size();

        QVector<double> xAxis(dataSize);
        for (int i = 0; i < mSeconds.size(); i++)
        {
            xAxis[i] = mSeconds[i];
        }
        ui->generalPlot->clearGraphs();

        int graphIndex = -1;

        if (ui->checkBox_0->isChecked())
        {
            graphIndex++;
            ui->generalPlot->addGraph();
            ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::red));
            ui->generalPlot->graph(graphIndex)->setName(tr("CH-0"));
            //        ui->generalPlot->graph(graphIndex)->setLineStyle(QCPGraph::LineStyle::lsNone);
            //        ui->generalPlot->graph(graphIndex)->setScatterStyle(QCPScatterStyle::ssDisc);
            ui->generalPlot->graph(graphIndex)->setData(xAxis, mCH0);
        }
        if (ui->checkBox_1->isChecked())
        {
            graphIndex++;
            ui->generalPlot->addGraph();
            ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::blue));
            ui->generalPlot->graph(graphIndex)->setName("CH-1");
            ui->generalPlot->graph(graphIndex)->setData(xAxis, mCH1);
        }
        if (ui->checkBox_2->isChecked())
        {
            graphIndex++;
            ui->generalPlot->addGraph();
            ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::magenta));
            ui->generalPlot->graph(graphIndex)->setName("CH-2");
            ui->generalPlot->graph(graphIndex)->setData(xAxis, mCH2);
        }
        if (ui->checkBox_3->isChecked())
        {
            graphIndex++;
            ui->generalPlot->addGraph();
            ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::green));
            ui->generalPlot->graph(graphIndex)->setName("CH-3");
            ui->generalPlot->graph(graphIndex)->setData(xAxis, mCH3);
        }
        if (ui->checkBox_4->isChecked())
        {
            graphIndex++;
            ui->generalPlot->addGraph();
            ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::cyan));
            ui->generalPlot->graph(graphIndex)->setName("CH-4");
            ui->generalPlot->graph(graphIndex)->setData(xAxis, mCH4);
        }
        if (ui->checkBox_5->isChecked())
        {
            graphIndex++;
            ui->generalPlot->addGraph();
            ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::darkGreen));
            ui->generalPlot->graph(graphIndex)->setName("CH-5");
            ui->generalPlot->graph(graphIndex)->setData(xAxis, mCH5);
        }
        if (ui->checkBox_6->isChecked())
        {
            graphIndex++;
            ui->generalPlot->addGraph();
            ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::darkRed));
            ui->generalPlot->graph(graphIndex)->setName("CH-6");
            ui->generalPlot->graph(graphIndex)->setData(xAxis, mCH6);
        }
        if (ui->checkBox_7->isChecked())
        {
            graphIndex++;
            ui->generalPlot->addGraph();
            ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::black));
            ui->generalPlot->graph(graphIndex)->setName("CH-7");
            ui->generalPlot->graph(graphIndex)->setData(xAxis, mCH7);
        }
        //        if(ui->checkBox_8->isChecked()){
        //        graphIndex++;
        //        ui->generalPlot->addGraph();
        //        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::darkYellow));
        //        ui->generalPlot->graph(graphIndex)->setName("CH-8");
        //        ui->generalPlot->graph(graphIndex)->setData(xAxis,mCH8);
        //}
        //        if(ui->checkBox_9->isChecked()){
        //        graphIndex++;
        //        ui->generalPlot->addGraph();
        //        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::darkMagenta));
        //        ui->generalPlot->graph(graphIndex)->setName("CH-9");
        //        ui->generalPlot->graph(graphIndex)->setData(xAxis,mCH9);
        //}

        if (ui->autoScaleButton->isChecked())
        {
            ui->generalPlot->rescaleAxes();
        }
        //ui->generalPlot->xAxis->setRange(mSecondCounter, 8, Qt::AlignRight);
        //ui->generalPlot->axisRect()->setBackground(QBrush(Qt::black));
        ui->generalPlot->replot();
        mUpdateGeneralPlot = false;
    }
}

PageSerialAnalysis::~PageSerialAnalysis()
{
    mSettings.setValue("lastcsvfile", ui->csvFileEdit->text());
    mSettings.setValue("CH0_checkStatus", ui->checkBox_0->isChecked());
    mSettings.setValue("CH1_checkStatus", ui->checkBox_1->isChecked());
    mSettings.setValue("CH2_checkStatus", ui->checkBox_2->isChecked());
    mSettings.setValue("CH3_checkStatus", ui->checkBox_3->isChecked());
    mSettings.setValue("CH4_checkStatus", ui->checkBox_4->isChecked());
    mSettings.setValue("CH5_checkStatus", ui->checkBox_5->isChecked());
    mSettings.setValue("CH6_checkStatus", ui->checkBox_6->isChecked());
    mSettings.setValue("CH7_checkStatus", ui->checkBox_7->isChecked());
    //    mSettings.setValue("CH8_checkStatus",ui->checkBox_8->isChecked());
    //    mSettings.setValue("CH9_checkStatus",ui->checkBox_9->isChecked());
    mSettings.setValue("enableLogStatus", ui->csvEnableLogBox->isChecked());
    delete ui;
}

void PageSerialAnalysis::printCmdFeedback(QString str)
{
    ui->cmdBrowser->append(str.toLatin1());
    //    ui->cmdBrowser->setText(ui->cmdBrowser->toPlainText()+str);
}

void PageSerialAnalysis::updateZoom()
{
    Qt::Orientations plotOrientations = Qt::Orientations(
        ((ui->zoomHButton->isChecked() ? Qt::Horizontal : 0) |
         (ui->zoomVButton->isChecked() ? Qt::Vertical : 0)));
    ui->generalPlot->axisRect()->setRangeZoom(plotOrientations);
}

void PageSerialAnalysis::updateMonitorLabel(MONITOR_VALUES values)
{
    ui->CH0_dataLabel->setText(QString("%1").arg(values.ch0));
    ui->CH1_dataLabel->setText(QString("%1").arg(values.ch1));
    ui->CH2_dataLabel->setText(QString("%1").arg(values.ch2));
    ui->CH3_dataLabel->setText(QString("%1").arg(values.ch3));
    ui->CH4_dataLabel->setText(QString("%1").arg(values.ch4));
    ui->CH5_dataLabel->setText(QString("%1").arg(values.ch5));
    ui->CH6_dataLabel->setText(QString("%1").arg(values.ch6));
    ui->CH7_dataLabel->setText(QString("%1").arg(values.ch7));
    //    ui->CH8_dataLabel->setText(QString("%1").arg(values.ch8));
    //    ui->CH9_dataLabel->setText(QString("%1").arg(values.ch9));
}

void PageSerialAnalysis::on_zoomHButton_toggled(bool checked)
{
    (void)checked;
    updateZoom();
}

void PageSerialAnalysis::on_zoomVButton_toggled(bool checked)
{
    (void)checked;
    updateZoom();
}

void PageSerialAnalysis::on_rescaleButton_clicked()
{
    ui->generalPlot->rescaleAxes();
    ui->generalPlot->replot();
}

//void PageSerialAnalysis::on_cmdClearButton_clicked()
//{
//    ui->cmdBrowser->clear();
//}

void PageSerialAnalysis::on_plotStopButton_toggled(bool checked)
{
    mUpdateButtonCheck = checked;
}

void PageSerialAnalysis::on_plotClearButton_clicked()
{
    mSeconds.clear();
    mSecondCounter = 0.0;
    mLastUpdateTime = 0;
    mCH0.clear();
    mCH1.clear();
    mCH2.clear();
    mCH3.clear();
    mCH4.clear();
    mCH5.clear();
    mCH6.clear();
    mCH7.clear();
    mCH8.clear();
    mCH9.clear();
    ui->generalPlot->clearGraphs();
    ui->generalPlot->replot();
}

void PageSerialAnalysis::on_legendVisibleButton_toggled(bool checked)
{
    ui->generalPlot->legend->setVisible(checked);
    ui->generalPlot->replot();
}

void PageSerialAnalysis::on_pushButton_clicked()
{
    mXaxisStep = ui->xAxisStepDoubleSpinBox->value();
    mMaxPoints = ui->maxPointsSpinBox->value();
    if (mXaxisStep == 0)
    {
        ui->generalPlot->xAxis->setLabel("Second (s)");
    }
    else
    {
        ui->generalPlot->xAxis->setLabel(QString("Step : %1").arg(mXaxisStep));
    }
    on_plotClearButton_clicked();
}

//void PageSerialAnalysis::on_sendCmdButton_14_clicked()
//{
//    if(mVesc){
//        mVesc->commands()->sendSerialCmd(ui->sendCmdText_14->text());
//    }
//}

//void PageSerialAnalysis::on_sendCmdButton_15_clicked()
//{
//    if(mVesc){
//        mVesc->commands()->sendSerialCmd(ui->sendCmdText_15->text());
//    }
//}

//void PageSerialAnalysis::on_channalCmdSendButton_1_clicked()
//{
//    if(mVesc){
//        mVesc->commands()->sendSerialCmd(ui->channalCmdText_1->text());
//    }
//}

//void PageSerialAnalysis::on_channalCmdSendButton_2_clicked()
//{
//    if(mVesc){
//        mVesc->commands()->sendSerialCmd(ui->channalCmdText_2->text());
//    }
//}

//void PageSerialAnalysis::on_channalCmdSendButton_3_clicked()
//{
//    if(mVesc){
//        mVesc->commands()->sendSerialCmd(ui->channalCmdText_3->text());
//    }
//}

//void PageSerialAnalysis::on_pageHelpButton_clicked()
//{
//    if(mVesc){
//        mVesc->commands()->sendSerialCmd("help");
//    }
//}

void PageSerialAnalysis::on_csvChooseDirButton_clicked()
{
    QString tempDir = QFileDialog::getExistingDirectory(this,
                                                        "Choose CSV output directory");
    if (!tempDir.isEmpty())
    {
        ui->csvFileEdit->setText(tempDir);
    }
    else
    {
        on_csvEnableLogBox_clicked(ui->csvEnableLogBox->isChecked());
        return;
    }
}

void PageSerialAnalysis::on_csvEnableLogBox_clicked(bool checked)
{
    if (checked)
    {
        if (mVesc)
        {
            mVesc->openRtLogFile(ui->csvFileEdit->text());
        }
    }
    else
    {
        mVesc->closeRtLogFile();
    }
}

void PageSerialAnalysis::on_newDataFile_clicked()
{
    ui->csvEnableLogBox->setChecked(true);
    if (ui->csvEnableLogBox->isChecked())
    {
        if (mVesc)
        {
            mVesc->openRtLogFile(ui->csvFileEdit->text());
        }
    }
    else
    {
        mVesc->closeRtLogFile();
    }
}

void PageSerialAnalysis::on_loadDataButton_clicked()
{
    if (mVesc)
    {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Load CSV File"), "",
                                                        tr("CSV files (*.csv)"));

        if (!fileName.isEmpty())
        {
            if (loadDataFile(fileName))
            {
                //on_openCurrentButton_clicked();
            }
        }
    }
}

bool PageSerialAnalysis::loadDataFile(QString file)
{

    bool res = false;

    QFile inFile(file);
    QVector<double> xAxis;
    if (inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&inFile);
        int lineNum = 0;

        //           mRtLogData.clear();
        on_plotClearButton_clicked();
        MONITOR_VALUES m;
        while (!in.atEnd())
        {
            QStringList tokens = in.readLine().split(";");

            //               if (tokens.size() >) {
            //                   continue;
            //               }

            if (lineNum > 0)
            {
                xAxis.append(lineNum);
                mCH0.append(tokens.at(1).toDouble());
                mCH1.append(tokens.at(2).toDouble());
                mCH2.append(tokens.at(3).toDouble());
                mCH3.append(tokens.at(4).toDouble());
                mCH4.append(tokens.at(5).toDouble());
                mCH5.append(tokens.at(6).toDouble());
                mCH6.append(tokens.at(7).toDouble());
                mCH7.append(tokens.at(8).toDouble());
                mCH8.append(tokens.at(9).toDouble());
                mCH9.append(tokens.at(10).toDouble());
            }
            lineNum++;
        }

        inFile.close();
        addChannalPlots(xAxis);
        ui->generalPlot->rescaleAxes();
        ui->generalPlot->replot();
        res = true;
        mVesc->emitStatusMessage(QString("Loaded %1 log entries").arg(lineNum - 1), true);
    }
    else
    {
        mVesc->emitMessageDialog("Read Log File",
                                 "Could not open\n" +
                                     file +
                                     "\nfor reading.",
                                 false, false);
    }

    return res;
}

void PageSerialAnalysis::addChannalPlots(QVector<double> xAxis)
{

    ui->generalPlot->clearGraphs();
    int graphIndex = -1;

    if (ui->checkBox_0->isChecked())
    {
        graphIndex++;
        ui->generalPlot->addGraph();
        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::red));
        ui->generalPlot->graph(graphIndex)->setName(tr("CH-0"));
        ui->generalPlot->graph(graphIndex)->setData(xAxis, mCH0);
    }
    if (ui->checkBox_1->isChecked())
    {
        graphIndex++;
        ui->generalPlot->addGraph();
        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::blue));
        ui->generalPlot->graph(graphIndex)->setName("CH-1");
        ui->generalPlot->graph(graphIndex)->setData(xAxis, mCH1);
    }
    if (ui->checkBox_2->isChecked())
    {
        graphIndex++;
        ui->generalPlot->addGraph();
        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::magenta));
        ui->generalPlot->graph(graphIndex)->setName("CH-2");
        ui->generalPlot->graph(graphIndex)->setData(xAxis, mCH2);
    }
    if (ui->checkBox_3->isChecked())
    {
        graphIndex++;
        ui->generalPlot->addGraph();
        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::green));
        ui->generalPlot->graph(graphIndex)->setName("CH-3");
        ui->generalPlot->graph(graphIndex)->setData(xAxis, mCH3);
    }
    if (ui->checkBox_4->isChecked())
    {
        graphIndex++;
        ui->generalPlot->addGraph();
        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::cyan));
        ui->generalPlot->graph(graphIndex)->setName("CH-4");
        ui->generalPlot->graph(graphIndex)->setData(xAxis, mCH4);
    }
    if (ui->checkBox_5->isChecked())
    {
        graphIndex++;
        ui->generalPlot->addGraph();
        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::darkGreen));
        ui->generalPlot->graph(graphIndex)->setName("CH-5");
        ui->generalPlot->graph(graphIndex)->setData(xAxis, mCH5);
    }
    if (ui->checkBox_6->isChecked())
    {
        graphIndex++;
        ui->generalPlot->addGraph();
        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::darkRed));
        ui->generalPlot->graph(graphIndex)->setName("CH-6");
        ui->generalPlot->graph(graphIndex)->setData(xAxis, mCH6);
    }
    if (ui->checkBox_7->isChecked())
    {
        graphIndex++;
        ui->generalPlot->addGraph();
        ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::black));
        ui->generalPlot->graph(graphIndex)->setName("CH-7");
        ui->generalPlot->graph(graphIndex)->setData(xAxis, mCH7);
    }
    //    if(ui->checkBox_8->isChecked()){
    //    graphIndex++;
    //    ui->generalPlot->addGraph();
    //    ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::darkYellow));
    //    ui->generalPlot->graph(graphIndex)->setName("CH-8");
    //    ui->generalPlot->graph(graphIndex)->setData(xAxis,mCH8);
    //}
    //    if(ui->checkBox_9->isChecked()){
    //    graphIndex++;
    //    ui->generalPlot->addGraph();
    //    ui->generalPlot->graph(graphIndex)->setPen(QPen(Qt::darkMagenta));
    //    ui->generalPlot->graph(graphIndex)->setName("CH-9");
    //    ui->generalPlot->graph(graphIndex)->setData(xAxis,mCH9);
    //}
}

void PageSerialAnalysis::on_cmdBrowserClearButton_clicked()
{
    ui->cmdBrowser->clear();
}

void PageSerialAnalysis::myMoveEvent(QMouseEvent *event)
{

    double x = event->pos().x();
    double y = event->pos().y();

    double x_ = ui->generalPlot->xAxis->pixelToCoord(x);
    double y_ = ui->generalPlot->yAxis->pixelToCoord(y);

    QString str = QString("x: %1\ny: %2").arg(QString::number(x_, 10, 3)).arg(QString::number(y_, 10, 3));

    //获取当前图像线上的数据点
    //    for(int i = 0;i<ui->generalPlot->xAxis->graphs().count();i++)
    //    {
    //        double _x = m_plot->graph(0)->data().data()->at(i)->key;
    //        double _y = m_plot->graph(0)->data().data()->at(i)->value;
    //    }
    QToolTip::showText(cursor().pos(), str, ui->generalPlot);
}

void PageSerialAnalysis::on_cmdBrowser_textChanged()
{
    ui->cmdBrowser->moveCursor(QTextCursor::End);
}
