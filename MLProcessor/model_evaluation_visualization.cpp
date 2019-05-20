//Lirongg Wang
#include "model_evaluation_visualization.h"
#include "ui_model_evaluation_visualization.h"
#include <QDebug>

model_evaluation_visualization::model_evaluation_visualization(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::model_evaluation_visualization)
{
    ui->setupUi(this);
}

model_evaluation_visualization::~model_evaluation_visualization()
{
    delete ui;
}

void model_evaluation_visualization::read_data(const vector< vector<double> > & features, const vector<int> & labels) {
    this->features = features;
    this->labels = labels;
}

void model_evaluation_visualization::base_vis() {
    QTableWidget * table =  new QTableWidget();
    table->setRowCount(5);
    table->setColumnCount(9);
    table->setWindowTitle("Model Evaluation");
    table->resize(1000,200);
    table->setHorizontalHeaderLabels(QStringList() << "Model" << "TP" << "TN" << "FP" << "FN" << "Accuracy" << "Error_rate" << "Secitivity" << "Specificity");
    table->setItem(0,0,new QTableWidgetItem("KNN"));
    table->setItem(1,0,new QTableWidgetItem("SVM"));
    table->setItem(2,0,new QTableWidgetItem("Naive Bayes"));
    table->setItem(3,0,new QTableWidgetItem("Logistic Regression"));
    table->setItem(4,0,new QTableWidgetItem("Desicion Tree"));


    vector<double> all_knn = all_predict_knn(features,labels);
    qDebug()<<"knn done";
    vector<double> all_los = all_predict_svm(features,labels);
    qDebug()<<"svm done";
    vector<double> all_bayes = all_predict_bayes(features,labels);
    qDebug()<<"bayes done";

    for (int i = 1; i < 9; i++) {
        string knn = to_string(all_knn[i-1]);
        string los = to_string(all_los[i-1]);
        string bayes = to_string(all_bayes[i-1]);
        QString qknn = QString::fromStdString(knn);
        QString qlos = QString::fromStdString(los);
        QString qbayes = QString::fromStdString(bayes);
        table->setItem(0,i,new QTableWidgetItem(qknn));
        table->setItem(1,i,new QTableWidgetItem(qlos));
        table->setItem(2,i,new QTableWidgetItem(qbayes));
    }

    table->show();
}
