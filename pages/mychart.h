#ifndef MYCHART_H
#define MYCHART_H

#include <QWidget>
#include <QChartView>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class Mychart;
}

class Mychart : public QWidget
{
    Q_OBJECT

public:
    explicit Mychart(QWidget *parent = nullptr);
    ~Mychart();

private:
    Ui::Mychart *ui;
    QChart *chart;
    QLineSeries *series_path, *series_pos;
    QValueAxis *axis_x, *axis_y;
};

#endif // MYCHART_H
