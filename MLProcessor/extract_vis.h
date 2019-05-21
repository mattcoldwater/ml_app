// Lirong Wang & Haoyu Wu
#ifndef EXTRACT_VIS_H
#define EXTRACT_VIS_H

#include <QMainWindow>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtCharts/QChartView>

using namespace std;
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class extract_vis;
}

class extract_vis : public QMainWindow
{
    Q_OBJECT

public:
    explicit extract_vis(QWidget *parent = nullptr);
    ~extract_vis();
    void read_data(const vector<string> & raw, const vector<int> & la);
    void base_vis();

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void direction1();
    void direction2();
    void direction3();
    void on_pushButton_clicked();

private:
    QChartView *chartView;
    QGridLayout *baseLayout;
    int direction;
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
    Ui::extract_vis *ui;
    vector<string> st;
    vector<int> labels;
};

#endif // EXTRACT_VIS_H
