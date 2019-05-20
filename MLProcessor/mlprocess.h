// Haoyu Wu
#ifndef MLProcess_H
#define MLProcess_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QToolBar>
#include <QFontComboBox>
#include <QToolButton>
#include <QTextCharFormat>
#include <string>
#include <vector>
#include "showwidget.h"
#include "dialog.h"
#include "pca.h"
#include "naivebayes.h"
#include "svm.h"
#include "knn.h"
#include "kmean_pca.h"

using namespace std;

class MLProcess : public QMainWindow
{
    Q_OBJECT

public:
    MLProcess(QWidget *parent = 0);
    ~MLProcess();
    void createActions(); //actions
    void createMenus(); //menus
    void createToolBars(); //toolbars
    void loadFile(QString filename);
    void tree_predicting(const vector<double> & v);
    void svm_predicting(const vector<double> & v);
    void log_predicting(const vector<double> & v);
    void bayes_predicting(const vector<double> & v);
    void knn_predicting(const vector<double> & v);
    double pred_label;
    vector<vector<double>> raw_features, features;
    vector<string> raw_feature_names;
    vector<int> label_peptides;
    vector<string> raw_peptides;
    //PCA *animo;
    KMEANS_PCA *animo;
    svm *my_svm;
    Knn *my_knn;
    vector<vector<double>> bayes_model;
    vector<double>  parameters_trained;
private:
    QString test_x;
    QString model_name;
    // file menu
    QMenu *fileMenu;
    QAction *openFileAction;
    QAction *exitAction;
    ShowWidget *showWidget;
    // data menu
    QMenu *dataMenu;
    QAction *featureExtractionAction;
    QAction *dataPreprocessingAction;
    vector<string> preprocessed_feature;
    // model menu
    QMenu *modelMenu;
    QAction *treeModelAction;
    QAction *svmModelAction;
    QAction *logModelAction;
    QAction *bayesModelAction;
    QAction *knnModelAction;
    // predict menu
    QMenu *predictMenu;
    QAction *PredictAction, *ModelvisAction;
    // help menu
    QMenu *helpMenu;
    QAction *helpAction;
    // tool bar
    QToolBar *fileTool;
    // ordering protect
    bool loadfile_done, extraction_done, preprocessing_done, treemodel_done, svmmodel_done, logmodel_done, bayesmodel_done, knnmodel_done;
private slots:
    void welcome();
    void ShowOpenFile();
    void aboutML();
    void extraction();
    void preprocessing();
    // models
    void treemodel();
    void svmmodel();
    void logmodel();
    void bayesmodel();
    void knnmodel();
    // predict
    void evaluation();
    void predicting();
    // information flows
    void receiveData(map<string, vector<QString>> data);
};

#endif // MLProcess_H
