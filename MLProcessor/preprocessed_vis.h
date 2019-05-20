// HaoyuWu
#ifndef PREPROCESSED_VIS_H
#define PREPROCESSED_VIS_H

#include <QMainWindow>
#include <vector>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMessageBox>
#include <QtDataVisualization>
using namespace QtDataVisualization;

namespace Ui {
class preprocessed_vis;
}

class preprocessed_vis : public QMainWindow
{
    Q_OBJECT

public:
    explicit preprocessed_vis(QWidget *parent = nullptr);
    ~preprocessed_vis();

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void on_pushButton_clicked();

private:
    Ui::preprocessed_vis *ui;
    std::vector<std::vector<double>> features;
    std::vector<int> labels;
    Q3DScatter *graph;
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
    int direction;
    void direction_base();
    void direction1();
    void direction2();
    void direction3();

};

#endif // PREPROCESSED_VIS_H
