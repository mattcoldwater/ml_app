#ifndef SVM_CROSS_VIS_H
#define SVM_CROSS_VIS_H

#include <QMainWindow>

using namespace std;

namespace Ui {
class svm_cross_vis;
}

class svm_cross_vis : public QMainWindow
{
    Q_OBJECT

public:
    explicit svm_cross_vis(QWidget *parent = nullptr);
    ~svm_cross_vis();
    void base_vis(const vector<vector<double>> & my_features, const vector<int> & my_labels);

private:
    Ui::svm_cross_vis *ui;
};

#endif // SVM_CROSS_VIS_H
