// Dinglin Xia, Haoyu Wu
#include "knn_vis.h"
#include "ui_knn_vis.h"
#include <QApplication>
#include <QtCharts>
#include "knn.h"
#include "utils_why.h"
#include "naivebayes.h"
#include "crossvalidation.h"
#include <iostream>

knn_vis::knn_vis(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::knn_vis)
{
    ui->setupUi(this);
}

knn_vis::~knn_vis()
{
    delete ui;
}

void knn_vis::base_vis(const vector<vector<double>> & features, const vector<int> & labels)
{
    Knn knn_model = Knn(features, labels);
    knn_model.setK(7);
    vector<int> test = knn_model.predictVec(features);
    vector<double> acc = knn_model.accVsK(features, labels, 10);
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < acc.size(); i++) {
        series->append(i+2, acc[i]);
    }
    //*series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Accuracy of KNN model VS. K");
    chart->axisX()->setTitleText("K Value");
    chart->axisY()->setTitleText("Accuracy");
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(400,300);
    chartView->show();
}
