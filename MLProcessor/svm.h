#ifndef SVM_H
#define SVM_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QThread>
#include <vector>
using namespace std;

namespace Ui {
class svm;
}

class svm : public QMainWindow
{
    Q_OBJECT

public:
    explicit svm(QWidget *parent = nullptr);
    ~svm();
    void read_data(const vector<vector<double>> & pre_features, const vector<int> & label_peptides);
    void train(bool vis=true); // SMO
    int predict(vector<double> test_feature);
    void set_threshold(double x);
    vector<vector<double>> features;
    vector<int> labels;

protected:
    QImage svm_background;
    vector<double> alphas;
    double b, threshold;
    vector<double> pre_Y;
    int theSize, featureSize;

    void after_train();
    void inside_train(const bool & vis);
    void paintEvent(QPaintEvent* e);
    int Alpha2(int i);
    void predict_X();
    void svm_update(int i, int j, double i_x, double j_x);
    double svm_multiply(int i, int j);
    double min(double a, double b);
    double max(double a, double b);
    bool epoch(int i1, int i2);
    double boundary(int x);

    const double C = 100;
    const double eps = 0.01;

private:
    void DelayMs(int ms);
    Ui::svm *ui;
};

#endif // SVM_H
