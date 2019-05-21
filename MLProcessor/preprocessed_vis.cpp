// HaoyuWu
#include "preprocessed_vis.h"
#include "ui_preprocessed_vis.h"
#include <QColor>
#include <QDebug>
#include <QtDataVisualization>
#include "mlprocess.h"
using namespace QtDataVisualization;

std::vector<std::vector<double>> global_pre_features;
std::vector<int> global_labels;

preprocessed_vis::preprocessed_vis(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::preprocessed_vis)
{
    ui->setupUi(this);
    direction = 1;
    features = global_pre_features;
    labels = global_labels;
    direction_base();
}

preprocessed_vis::~preprocessed_vis()
{
    delete ui;
}

void preprocessed_vis::direction_base() {

    graph = new Q3DScatter();
    graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFrontLow);

    graph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);

    graph->axisX()->setRange(0, 0.5);
    graph->axisY()->setRange(0, 0.5);
    graph->axisZ()->setRange(0, 0.5);

    graph->axisX()->setSegmentCount(int(4));
    graph->axisY()->setSegmentCount(int(4));
    graph->axisZ()->setSegmentCount(int(4));

    graph->activeTheme()->setType(Q3DTheme::ThemeQt);

//    graph->axisX()->setLabelFormat("X");
//    graph->axisY()->setLabelFormat("Y");
//    graph->axisZ()->setLabelFormat("Z");

    //点
    QScatter3DSeries *series = new QScatter3DSeries;
    QScatter3DSeries *series2 = new QScatter3DSeries;
    //label
    series->setItemLabelFormat("@xTitle: @xLabel @yTitle: @yLabel @zTitle: @zLabel");
    series2->setItemLabelFormat("@xTitle: @xLabel @yTitle: @yLabel @zTitle: @zLabel");
    // color
    QColor background_color = QColor();
    background_color.setNamedColor("red");
    series->setBaseColor(background_color);
    background_color.setNamedColor("blue");
    series2->setBaseColor(background_color);

    series->setItemSize(float(0.06));
    series2->setItemSize(float(0.06));

    QScatterDataArray data;
    QScatterDataArray data2;

    QWidget *container = QWidget::createWindowContainer(graph);

    if (!graph->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
    }

    hLayout = new QHBoxLayout(ui->widget);
    vLayout = new QVBoxLayout();

    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);

    // add data
    for (int i_=0; i_<int(labels.size());i_++) {
        unsigned int i = unsigned(i_);
        //qDebug()<<i<<":"<<labels[i];
        float x_, y_, z_;
        x_ = float(features[i][0]);
        y_ = float(features[i][1]);
        z_ = float(features[i][2]);
        if (labels[i]==0) {
            data.append(QVector3D(x_, y_, z_));
        } else {
            data2.append(QVector3D(x_, y_, z_));
        }
    }
    //data.append(QVector3D(2.0f, 12.0f, 19.0f));
    //data2.append(QVector3D(10, 2, 0.5f));

    series->dataProxy()->addItems(data);
    series2->dataProxy()->addItems(data2);
    graph->addSeries(series);
    graph->addSeries(series2);
    //chart->setAnimationOptions(QChart::SeriesAnimations);
    graph->show();
}

void preprocessed_vis::direction1() {
    graph->close();
    graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFrontLow);
    graph->show();
}

void preprocessed_vis::direction2() {
    graph->close();
    graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetDirectlyAbove);
    graph->show();
}

void preprocessed_vis::direction3() {
    graph->close();
    graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetBehindBelow);
    graph->show();
}

void preprocessed_vis::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if (arg1=="Direction1") {
        direction = 1;
    } else if (arg1=="Direction2") {
        direction = 2;
    } else {
        direction = 3;
    }
}

void preprocessed_vis::on_pushButton_clicked()
{
    if (direction==1) {
        direction1();
    } else if (direction==2) {
        direction2();
    } else {
        direction3();
    }
}
