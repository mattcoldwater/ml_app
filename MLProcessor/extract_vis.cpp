// Lirong Wang & Haoyu Wu
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>

#include "getfeaturename.h"
#include "getfeatures.h"
#include "importPeptide.h"
#include "feature_for_vis.h"

#include "extract_vis.h"
#include "ui_extract_vis.h"

using namespace std;
QT_CHARTS_USE_NAMESPACE

#include <numeric> //for test of features

extract_vis::extract_vis(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::extract_vis)
{
    ui->setupUi(this);
    direction = 1;
}

extract_vis::~extract_vis()
{
    delete ui;
}

void extract_vis::read_data(const vector<string> & st, const vector<int> & labels) {
    this->st = st;
    this->labels = labels;
        base_vis();
}

void extract_vis::base_vis() {
    //The route of the file should be able change accrording to the input of the user

    vector<string> pos_st;
    vector<string> neg_st;

    //labels = importPeptide_label("/Users/wanglirong/Downloads/Term6/CSC3002/Final_Project/data.txt");
    pos_st = pos_peptide(labels,st);
    neg_st = neg_peptide(labels,st);

    vector<double> aver_pos_aac = averageAAC(pos_st);
    vector<double> aver_neg_aac = averageAAC(neg_st);
    //vector<double> aver_pos_cksaap = averageCKSAAP(pos_st);
    //vector<double> aver_neg_cksaap = averageCKSAAP(neg_st);
    //vector<double> aver_pos_n5c5aac = averageN5C5AAC(pos_st);
    //vector<double> aver_neg_n5c5aac = averageN5C5AAC(neg_st);

    QBarSet *set_pos = new QBarSet("Positive");
    QBarSet *set_neg = new QBarSet("Negative");

    for (int i = 0; i < aver_pos_aac.size(); i++) {
        *set_pos << aver_pos_aac[i];//need to change name to aver_pos_cksaap or aver_pos_n5c5aac
        *set_neg << aver_neg_aac[i];//need to change name to aver_neg_cksaap or aver_neg_n5c5aac
    }

    QBarSeries *series = new QBarSeries();
    series->append(set_pos);
    series->append(set_neg);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Comparison of Positive and Negative Data");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    for (int j = 0; j < aver_pos_aac.size(); j++) {
        QString name = QString::fromStdString(NATURAL_AA_STR[j]);
        categories << name;
    }
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(700, 600);

    baseLayout = new QGridLayout(ui->widget);
    baseLayout->addWidget(chartView, 1, 0);
    ui->widget->setLayout(baseLayout);
    chartView->show();
}

void extract_vis::direction1() {
    //The route of the file should be able change accrording to the input of the user

    vector<string> pos_st;
    vector<string> neg_st;

    //labels = importPeptide_label("/Users/wanglirong/Downloads/Term6/CSC3002/Final_Project/data.txt");
    pos_st = pos_peptide(labels,st);
    neg_st = neg_peptide(labels,st);

    vector<double> aver_pos_aac = averageAAC(pos_st);
    vector<double> aver_neg_aac = averageAAC(neg_st);
    //vector<double> aver_pos_cksaap = averageCKSAAP(pos_st);
    //vector<double> aver_neg_cksaap = averageCKSAAP(neg_st);
    //vector<double> aver_pos_n5c5aac = averageN5C5AAC(pos_st);
    //vector<double> aver_neg_n5c5aac = averageN5C5AAC(neg_st);

    QBarSet *set_pos = new QBarSet("Positive");
    QBarSet *set_neg = new QBarSet("Negative");

    for (int i = 0; i < aver_pos_aac.size(); i++) {
        *set_pos << aver_pos_aac[i];//need to change name to aver_pos_cksaap or aver_pos_n5c5aac
        *set_neg << aver_neg_aac[i];//need to change name to aver_neg_cksaap or aver_neg_n5c5aac
    }

    QBarSeries *series = new QBarSeries();
    series->append(set_pos);
    series->append(set_neg);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Comparison of Positive and Negative AAC");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    for (int j = 0; j < aver_pos_aac.size(); j++) {
        QString name = QString::fromStdString(NATURAL_AA_STR[j]);
        categories << name;
    }
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView->close();
    chartView->setChart(chart);
    chartView->show();
}

void extract_vis::direction2() {
    //The route of the file should be able change accrording to the input of the user

    vector<double> top20_cksaap = top20_diff(labels,st);
    vector<string> top20_name = top20_diff_name(labels,st);

    QBarSet *set = new QBarSet("|Pos - Neg|");

    for (int i = 0; i < top20_cksaap.size(); i++) {
        *set << top20_cksaap[i];//need to change name to aver_pos_cksaap or aver_pos_n5c5aac
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Top20 differences of Positive and Negative CKSAAP");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    for (int j = 0; j < top20_cksaap.size(); j++) {
        QString name = QString::fromStdString(top20_name[j]);
        categories << name;
    }
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView->close();
    chartView->setChart(chart);
    chartView->show();
}

void extract_vis::direction3() {
    //The route of the file should be able change accrording to the input of the user

    vector<string> pos_st;
    vector<string> neg_st;

    //labels = importPeptide_label("/Users/wanglirong/Downloads/Term6/CSC3002/Final_Project/data.txt");
    pos_st = pos_peptide(labels,st);
    neg_st = neg_peptide(labels,st);

    vector<double> aver_pos_n5c5aac = averageN5C5AAC(pos_st);
    vector<double> aver_neg_n5c5aac = averageN5C5AAC(neg_st);

    QBarSet *set_pos = new QBarSet("Positive");
    QBarSet *set_neg = new QBarSet("Negative");

    for (int i = 0; i < aver_pos_n5c5aac.size(); i++) {
        *set_pos << aver_pos_n5c5aac[i];
        *set_neg << aver_neg_n5c5aac[i];
    }

    QBarSeries *series = new QBarSeries();
    series->append(set_pos);
    series->append(set_neg);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Comparison of Positive and Negative N5C5 AAC");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    for (int j = 0; j < aver_pos_n5c5aac.size(); j++) {
        QString name = QString::fromStdString(AA_X_STR[j]);
        categories << name;
    }
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView->close();
    chartView->setChart(chart);
    chartView->show();
}

void extract_vis::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if (arg1=="AAC") {
        direction = 1;
    } else if (arg1=="CKSAAP") {
        direction = 2;
    } else {
        direction = 3;
    }
}

void extract_vis::on_pushButton_clicked()
{
    if (direction==1) {
        direction1();
    } else if (direction==2) {
        direction2();
    } else {
        direction3();
    }
}
