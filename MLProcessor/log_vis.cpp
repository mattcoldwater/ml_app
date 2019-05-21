// Nuoyao Yang, Haoyu Wu
#include "log_vis.h"
#include "ui_log_vis.h"
#include <QtCharts>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QDebug>

#include <vector>
#include "optimization.h"
#include "utils_why.h"

#include <QApplication>
#include<iostream>
#include "doublearray.h"
#include "optimization.h"
#include "predict.h"
#include "segmentation.h"
#include "sigmoid.h"

log_vis::log_vis(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::log_vis)
{
    ui->setupUi(this);
}

log_vis::~log_vis()
{
    delete ui;
}

void log_vis::base_vis(const vector<vector<double>> & features, const vector<double> & labels)
{
    vector<double> parameters_initial;
    for (int i=0; i<features[0].size(); i++){
        parameters_initial.push_back(0.02);
    }

    vector<double> parameters_trained=fmin2(parameters_initial, features, labels);
    qDebug()<<parameters_trained.size()<<"para";
//    selectionSort(parameters_trained);
    qDebug()<<parameters_trained.size()<<"para";

    double p3=parameters_trained[parameters_trained.size()-1];

    double p2=parameters_trained[parameters_trained.size()-2];

    double p1=parameters_trained[parameters_trained.size()-3];
    QBarSet *set0 = new QBarSet("parameter");
    *set0 << 0.0999971 << 0.0999937 << 0.1 ;//在这修改

    //initialize series
    QBarSeries *series = new QBarSeries();
    series->append(set0);


    //create chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("The priority of parameters");
    chart->setAnimationOptions(QChart::SeriesAnimations);


    //initialize the x-axis
    QStringList categories;
    categories << "Parameter1" << "Parameter2" << "Parameter3";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axisX, series);


    //initialize the y-axis
    QValueAxis *axisY = new QValueAxis();
    chart->axisY()->setRange(0.0999,0.1000);
    //chart->addAxis(axisY, Qt::AlignLeft); //eleminate a redundant y-axis
    series->attachAxis(axisY);

    //initialize the Qchart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(400,300);
    chartView->show();
}

void selectionSort(vector<double> & vec) {

   int n = vec.size();

   for (int lh = 0; lh < n; lh++) {

      int rh = lh;

      for (int i = lh + 1; i < n; i++) {

         if (vec[i] < vec[rh]) rh = i;

      }

      int temp = vec[lh];

      vec[lh] = vec[rh];

      vec[rh] = temp;
}
}
