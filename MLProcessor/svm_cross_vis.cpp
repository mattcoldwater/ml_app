#include "svm_cross_vis.h"
#include "ui_svm_cross_vis.h"
#include "svm.h"
#include "crossvalidation.h"
#include <QApplication>
#include <QtCharts>

svm_cross_vis::svm_cross_vis(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::svm_cross_vis)
{
    ui->setupUi(this);
}

svm_cross_vis::~svm_cross_vis()
{
    delete ui;
}

void svm_cross_vis::base_vis(const vector<vector<double>> & features, const vector<int> & labels) {
    svm* svm_model = new svm();
    svm_model->read_data(features, labels);
    vector<double> acc = crossValidation_svm(features, labels, 1, svm_model);
    //-------Plotting-------------
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < acc.size(); i++) {
        series->append(0.1*i+0.3, acc[i]);
    }
    //*series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Accuracy of SVM model VS. Thresholds");

    chart->axisX()->setTitleText("Thresholds");//标题
    //chart->axisX()->setLabelFormat("%.1f"); //标签格式：每个单位保留几位小数

    chart->axisY()->setTitleText("Accuracy");
    //chart->axisY()->setLabelFormat("%.2f"); //标签格式

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(400,300);
    chartView->show();
}
