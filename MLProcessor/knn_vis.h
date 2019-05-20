// Dinglin Xia, Haoyu Wu
#ifndef KNN_VIS_H
#define KNN_VIS_H

#include <QMainWindow>

using namespace std;

namespace Ui {
class knn_vis;
}

class knn_vis : public QMainWindow
{
    Q_OBJECT

public:
    explicit knn_vis(QWidget *parent = nullptr);
    ~knn_vis();
    void base_vis(const vector<vector<double>> & my_features, const vector<int> & my_labels);

private:
    Ui::knn_vis *ui;
};

#endif // KNN_VIS_H
