//Lirong Wang
#ifndef MODEL_EVALUATION_VISUALIZATION_H
#define MODEL_EVALUATION_VISUALIZATION_H

#include <QMainWindow>
#include <QApplication>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTableView>
#include <vector>
#include "model_evaluation.h"
using namespace std;

namespace Ui {
class model_evaluation_visualization;
}

class model_evaluation_visualization : public QMainWindow
{
    Q_OBJECT

public:
    explicit model_evaluation_visualization(QWidget *parent = nullptr);
    ~model_evaluation_visualization();
    void read_data(const vector< vector<double> > & features, const vector<int> & labels);
    void base_vis();

private:
    vector< vector<double> > features;
    vector<int> labels;

    Ui::model_evaluation_visualization *ui;
};

#endif // MODEL_EVALUATION_VISUALIZATION_H
