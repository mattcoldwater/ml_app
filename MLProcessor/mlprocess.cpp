// Haoyu Wu
#include "mlprocess.h"
#include <QFileDialog>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include "dialog.h"
#include <QDebug>
#include <QString>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <QLineEdit>
#include <QMessageBox>
#include "importPeptide.h"
#include "getfeatures.h"
#include "getfeaturename.h"
#include "utils_why.h"
#include "preprocessed_vis.h"
#include "tree_vis.h"
#include "knn_vis.h"
#include "extract_vis.h"
#include "CDTree.hpp"
#include "RFCSV.hpp"
#include <Eigen/Dense>
#include "svm_cross_vis.h"
#include "doublearray.h"
#include "optimization.h"
#include "predict.h"
#include "segmentation.h"
#include "sigmoid.h"
#include "log_vis.h"
#include "log_cross_vis.h"
#include "model_evaluation_visualization.h"
using Eigen::MatrixXf; using Eigen::MatrixXi;

using namespace std;

extern vector<vector<double>> global_pre_features;
extern vector<int> global_labels;

MLProcess::MLProcess(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Machine Learning Application"));
    resize(830, 530);
    showWidget = new ShowWidget(this);
    setCentralWidget(showWidget);
    createActions();
    createMenus();
    createToolBars();
    loadfile_done=extraction_done=preprocessing_done=treemodel_done=svmmodel_done=logmodel_done=bayesmodel_done=knnmodel_done=false;
    welcome();
}

MLProcess::~MLProcess()
{

}

void MLProcess::welcome() {
    showWidget->text->clear();
    QString imgPath = QString("images/welcome.png");
    imgPathToHtml(imgPath);
    showWidget->text->insertHtml(imgPath);
    showWidget->text->adjustSize();
}

void MLProcess::createActions()
{
    /* file */
    // open
    openFileAction = new QAction(QIcon("images/open.png"), tr("Open"), this);
    openFileAction->setStatusTip(tr("open a txt file"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(ShowOpenFile()));
    // exit
    exitAction = new QAction(tr("Exit"), this);
    exitAction->setStatusTip(tr("exit!"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    /* data menu*/
    // feature extraction 400 dimensions
    featureExtractionAction = new QAction(tr("Feature Extraction"), this);
    connect(featureExtractionAction, SIGNAL(triggered()), this, SLOT(extraction()));
    // data preprocessing 4 dimensions
    dataPreprocessingAction = new QAction(tr("Data Preprocessing"), this);
    connect(dataPreprocessingAction, SIGNAL(triggered()), this, SLOT(preprocessing()));

    /* model menu*/
    // tree
    treeModelAction = new QAction(tr("Tree Model"), this);
    connect(treeModelAction, SIGNAL(triggered()), this, SLOT(treemodel()));
    // svm
    svmModelAction = new QAction(tr("SVM"), this);
    connect(svmModelAction, SIGNAL(triggered()), this, SLOT(svmmodel()));
    // log
    logModelAction = new QAction(tr("Logistic Regression"), this);
    connect(logModelAction, SIGNAL(triggered()), this, SLOT(logmodel()));
    // bayes
    bayesModelAction = new QAction(tr("Bayes"), this);
    connect(bayesModelAction, SIGNAL(triggered()), this, SLOT(bayesmodel()));
    // knn
    knnModelAction = new QAction(tr("KNN"), this);
    connect(knnModelAction, SIGNAL(triggered()), this, SLOT(knnmodel()));

    /* predict menu*/
    // evaluation
    ModelvisAction = new QAction(tr("Model Evaluation"), this);
    connect(ModelvisAction, SIGNAL(triggered()), this, SLOT(evaluation()));
    // predict
    PredictAction = new QAction(tr("Predicting"), this);
    PredictAction->setStatusTip(tr("Enter a polypeptide string"));
    connect(PredictAction, SIGNAL(triggered()), this, SLOT(predicting()));

    /* help menu*/
    // help
    helpAction = new QAction(tr("Help"), this);
    helpAction->setStatusTip(tr("Help"));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(aboutML()));
}

void MLProcess::createMenus()
{
    // file menu
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(openFileAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    dataMenu = menuBar()->addMenu(tr("Data"));
    dataMenu->addAction(featureExtractionAction);
    dataMenu->addAction(dataPreprocessingAction);

    modelMenu = menuBar()->addMenu(tr("Model"));
    modelMenu->addAction(treeModelAction);
    modelMenu->addAction(svmModelAction);
    modelMenu->addAction(logModelAction);
    modelMenu->addAction(bayesModelAction);
    modelMenu->addAction(knnModelAction);

    predictMenu = menuBar()->addMenu(tr("Predict"));
    predictMenu->addAction(ModelvisAction);
    predictMenu->addAction(PredictAction);

    helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(helpAction);
}

void MLProcess::createToolBars()
{
    // file tool bars
    fileTool = addToolBar("File");
    fileTool->addAction(openFileAction);
    fileTool->setAllowedAreas(Qt::TopToolBarArea|Qt::LeftToolBarArea);
    fileTool->setMovable(false);
}

void MLProcess::ShowOpenFile()
{
    QString filter = "Txt file (*.txt)";
    QDir dir;
    QString txtRoute = dir.absolutePath();
    QString fileName = QFileDialog::getOpenFileName(this, QString("Load TXT File"), txtRoute, filter);

    // init

    pred_label = 0;
    raw_features.clear();
    features.clear();
    raw_feature_names.clear();
    label_peptides.clear();
    raw_peptides.clear();
    //KMEANS_PCA *animo;
    //svm *my_svm;
    //Knn *my_knn;
    bayes_model.clear();
    parameters_trained.clear();
    loadfile_done=extraction_done=preprocessing_done=treemodel_done=svmmodel_done=logmodel_done=bayesmodel_done=knnmodel_done=0;

    //init

    importPeptide(& label_peptides, & raw_peptides, fileName.toStdString());
    global_labels = label_peptides;
    raw_features = getAll(raw_peptides);
    raw_feature_names = allName();
    //    outputVector(label_peptides);    outputVector(peptides);
    if (!fileName.isEmpty())
    {
        showWidget->text->clear();
        loadFile(fileName);
    }
}

void MLProcess::loadFile(QString filename)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream textStream(&file);
        while (!textStream.atEnd())
        {
            showWidget->text->append(textStream.readLine());
        }
    }
    loadfile_done = true;
    //extraction();
    //preprocessing();
}

void MLProcess::aboutML()
{
    showWidget->text->clear();
    QFile file(QString("texts/Help_Manual.txt"));
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream textStream(&file);
        while (!textStream.atEnd())
        {
            showWidget->text->append(textStream.readLine());
        }
    }
}

void MLProcess::extraction()
{
    if (!loadfile_done) {
        messageWARN("You have to Load/Open a File first!");
        return;
    }
    //raw_features
    //raw_feature_names
    /* TODO
     * vector<string> preprocessed_feature = importPepride(txtRoute);
     * plot(AACdata, residual) */
    messageOK("Extraction OK!");

    extract_vis *my_extract_vis = new extract_vis();
    my_extract_vis->read_data(raw_peptides, label_peptides);
    my_extract_vis->show();
    extraction_done = true;
}

void MLProcess::preprocessing()
{
    if (!extraction_done) {
        messageWARN("You have to click Extraction first!");
        return;
    }
    int k = 3;
    animo = new KMEANS_PCA(k);
    //animo->k_means(raw_features, k, 10);
    vector <double> labels(raw_features.size(),0);
    animo->load_data(raw_features,labels);
    features = animo->output(raw_features);
    global_pre_features = features;
    check_shape(features);
    messageOK("Preprocessing OK, Visualizing....");
    preprocessing_done = true;
    preprocessed_vis *vis = new preprocessed_vis();
    vis->show();
}

void MLProcess::treemodel()
{
    if (!preprocessing_done) {
        messageWARN("You have to click Preprocessing first!");
        return;
    }
    /*                                                                  */
    write_csv(features, label_peptides, "ContinuousTrain.csv"); //根据features labels生成ContinuousTrain.csv 这个文件是我们生成决策二叉树所需要的格式文件
    std::pair<MatrixXf, MatrixXi> trainData, testData;
    RFCSV<MatrixXf, MatrixXi> readcsv;
    trainData = readcsv.getData("ContinuousTrain.csv"); //读取训练数据到内存数据结构
    testData = readcsv.getData("ContinuousTest.csv"); //读取训练数据到内存数据结构

    CDTree myCDTree(100000, 2, 0.0001);  //CDTree 100000代表决策树生成的最大树的深度 2代表二分法算出来的值 0.0001表示精度
    myCDTree.buildTree(trainData.first, trainData.second, "ID3");//生成决策树， trainData.first就是features trainData.second就是labels

    MyNode<double> *myNoderoot = myCDTree.preOrder(myCDTree.root);
    //MatrixXi predictresult = myCDTree.predict(features[0]);
    //MatrixXi predictresult = myCDTree.predict(testData.first);//进行预测testData.first代表预测数据的features
    /*                                                                  */

    tree_vis *tree_Vis = new tree_vis();
    tree_Vis->root = myNoderoot;
    tree_Vis->show();
    treemodel_done = true;
    messageOK("Tree Model, Training OK!");
}

void MLProcess::svmmodel()
{
    if (!preprocessing_done) {
        messageWARN("You have to click Preprocessing first!");
        return;
    }
    if (svmmodel_done) {
        delete my_svm;
    }
    my_svm = new svm;
    my_svm->read_data(features, label_peptides);
    my_svm->train();
    svmmodel_done = true;
    messageOK("SVM, Training OK! Let's see the validation!");

    svm_cross_vis my_vis;
    my_vis.base_vis(features, label_peptides);
}

void MLProcess::logmodel()
{
    if (!preprocessing_done) {
        messageWARN("You have to click Preprocessing first!");
        return;
    }


    vector<double> my_labels;
    for (int i=0; i<10; i++) {
        my_labels.push_back(double(label_peptides[i]));
    }
    vector<vector<double>> my_features;
    for (int i=0; i<10; i++) {
        my_features.push_back(raw_features[i]);
    }

    vector<double> parameters_initial;
    for (int i=0; i<my_features[0].size(); i++){
        //initialize parameters to be 0.1
        parameters_initial.push_back(0.1);
    }

    parameters_trained=fmin2(parameters_initial, my_features, my_labels);

    for (int i=0; i<parameters_trained.size(); i++)
      {
        cout<<parameters_trained[i]<<endl;

    }

    cout<<"here"<<accuracy(my_features, my_labels, parameters_trained);

    logmodel_done = true;
    messageOK("Logistic Regression, Training OK!");

    log_vis my_vis;
    my_vis.base_vis(my_features, my_labels);

    log_cross_vis my_vis_cross;
    my_vis_cross.base_vis(my_features, label_peptides);
}

void MLProcess::bayesmodel()
{
    if (!preprocessing_done) {
        messageWARN("You have to click Preprocessing first!");
        return;
    }
    bayes_model = bayesModel(features, label_peptides);
    bayesmodel_done = true;
    messageOK("Bayes Model, Training OK!");
}

void MLProcess::knnmodel()
{
    if (!preprocessing_done) {
        messageWARN("You have to click Preprocessing first!");
        return;
    }
    /*bayes_model = bayesModel(features, label_peptides);
    messageOK("Bayes Model, Training OK!");*/
    if (knnmodel_done) {
        delete my_knn;
    }
    my_knn = new Knn(features, label_peptides);
    knn_vis my_knn_vis;
    my_knn_vis.base_vis(features, label_peptides);
    knnmodel_done = true;
    messageOK("KNN Model, OK!");
}

void MLProcess::predicting()
{
    Dialog *dialog = new Dialog();
    connect(dialog, SIGNAL(sendData(map<string, vector<QString>>)), this, SLOT(receiveData(map<string, vector<QString>>)));
    dialog->show();
}

void MLProcess::receiveData(map<string, vector<QString>> data)
{
    set<string> model_name_set;
    model_name_set.insert("Tree");
    model_name_set.insert("SVM");
    model_name_set.insert("Bayes");
    model_name_set.insert("Logistic Regression");
    model_name_set.insert("KNN");

    map<string,int> mp;
    mp["Tree"] = 0;
    mp["SVM"] = 1;
    mp["Bayes"] = 2;
    mp["Logistic Regression"] = 3;
    mp["KNN"] = 4;

    qDebug()<<data["app_name"][0];
    if (data["app_name"][0] == "prediction") {
        string model_name = data["app_data"][0].toStdString();
        if (model_name_set.count(model_name)>=1) {
            switch (mp[model_name]) {
             case 0:
                if (!treemodel_done) {
                    messageWARN("You have to model Tree first!");
                    return;
                }
                break;
             case 1:
                if (!svmmodel_done) {
                    messageWARN("You have to model SVM first!");
                    return;
                }
                break;
             case 2:
                if (!bayesmodel_done) {
                    messageWARN("You have to model Bayes first!");
                    return;
                }
                break;
             case 3:
                if (!logmodel_done) {
                    messageWARN("You have to model Logistic Regression first!");
                    return;
                }
                break;
             case 4:
                if (!knnmodel_done) {
                    messageWARN("You have to model KNN first!");
                    return;
                }
                break;
            }
            test_x = data["app_data"][1];
            vector<string> test_peptides;
            test_peptides.push_back(test_x.toStdString());
            vector<vector<double>> newData = getAll(test_peptides);
            vector<double> new_out = animo->new_output(newData)[0];

            qDebug()<<QString::fromStdString(model_name);
            qDebug()<<test_x;
            /*for (vector<double> row : newData) {
                outputVector(row);
            }
            cout<<"____________"<<endl;*/
            /*for (vector<double> temp : new_out){
                outputVector(temp);
            }*/

            switch (mp[model_name]) {
             case 0:
                tree_predicting(new_out);
                break;
             case 1:
                svm_predicting(new_out);
                break;
             case 2:
                bayes_predicting(new_out);
                break;
             case 3:
                log_predicting(new_out);
                break;
             case 4:
                knn_predicting(new_out);
                break;
            }

            QString mess;
            if (pred_label < 0.5) {
                mess = "The protein can't resist virus!";
            } else {
                mess = "The protein can resist virus!";
            }
            messageINFO(mess);
        }
    }
}

void MLProcess::tree_predicting(const vector<double> & v)
{
    qDebug()<<"tree is begin!!!";
    /* TODO
     * y = tree(stringX);
     * plot(y) */
    pred_label = 1;
}

void MLProcess::knn_predicting(const vector<double> & v)
{
    qDebug()<<"knn begins!!!";
    int result = my_knn->predictInt(v);
    pred_label = double(result);
    qDebug()<<"KNN predict"<<result;
}

void MLProcess::svm_predicting(const vector<double> & v)
{
    vector<double> svm_test;
    svm_test.push_back(v[0]);
    svm_test.push_back(v[2]);
    int result = my_svm->predict(svm_test);
    pred_label = double(result);
    qDebug()<<"svm predict "<<result;
}

void MLProcess::log_predicting(const vector<double> & v)
{
    pred_label = predict(parameters_trained, v);
}

void MLProcess::bayes_predicting(const vector<double> & v)
{
    int result = testProb(bayes_model, v);
    pred_label = double(result);
    qDebug()<<"bayes predict "<<result;
}


void MLProcess::evaluation()
{
    if (!preprocessing_done) {
        messageWARN("You have to click Preprocessing first!");
        return;
    }
    model_evaluation_visualization my_vis;
    my_vis.read_data(features, label_peptides);
    my_vis.base_vis();
}
