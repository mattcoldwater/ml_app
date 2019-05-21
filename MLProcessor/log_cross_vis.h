#ifndef LOG_CROSS_VIS_H
#define LOG_CROSS_VIS_H
#include <QApplication>
#include <QtCharts>
#include <QMainWindow>

using namespace std;

namespace Ui {
class log_cross_vis;
}

class log_cross_vis : public QMainWindow
{
    Q_OBJECT

public:
    explicit log_cross_vis(QWidget *parent = nullptr);
    ~log_cross_vis();
    void base_vis(const vector<vector<double>> & features, const vector<int> & label_peptides);

private:
    Ui::log_cross_vis *ui;
};

#endif // LOG_CROSS_VIS_H
