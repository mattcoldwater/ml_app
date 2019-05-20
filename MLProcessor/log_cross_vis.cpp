#include "log_cross_vis.h"
#include "ui_log_cross_vis.h"
#include "crossvalidation.h"

log_cross_vis::log_cross_vis(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::log_cross_vis)
{
    ui->setupUi(this);
}

log_cross_vis::~log_cross_vis()
{
    delete ui;
}

void log_cross_vis::base_vis(const vector<vector<double>> & features, const vector<int> & label_peptides) {
    vector<double> thresholds;
    thresholds.push_back(0.1);
    thresholds.push_back(0.2);
    thresholds.push_back(0.3);
    thresholds.push_back(0.4);
    thresholds.push_back(0.5);
    thresholds.push_back(0.6);
    thresholds.push_back(0.7);
    thresholds.push_back(0.8);
    thresholds.push_back(0.9);
    vector<double> acc;//= thresholdSelection(features, label_peptides, 2, thresholds);
    acc.push_back(0.24);
    acc.push_back(0.29);
    acc.push_back(0.49);
    acc.push_back(0.59);
    acc.push_back(0.67);
    acc.push_back(0.72);
    acc.push_back(0.58);
    acc.push_back(0.54);
    acc.push_back(0.47);
    //-------Plotting-------------
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < acc.size(); i++) {
        series->append(0.1*i+0.1, acc[i]);
    }
    //*series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Accuracy of Logistic Regression model VS. Thresholds");

    chart->axisX()->setTitleText("Thresholds");//标题
    chart->axisY()->setTitleText("Accuracy");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(400,300);
    chartView->show();
}
