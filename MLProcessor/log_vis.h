// Nuoyao Yang, Haoyu Wu
#ifndef LOG_VIS_H
#define LOG_VIS_H

#include <QMainWindow>

using namespace std;

namespace Ui {
class log_vis;
}

class log_vis : public QMainWindow
{
    Q_OBJECT

public:
    explicit log_vis(QWidget *parent = nullptr);
    ~log_vis();
    void base_vis(const vector<vector<double>> & features, const vector<double> & labels);


private:
    Ui::log_vis *ui;
};

void selectionSort(vector<double> & vec);

#endif // LOG_VIS_H
