// HaoyuWu
#ifndef TREE_VIS_H
#define TREE_VIS_H

#include <QWidget>
#include "utils_why.h"

class tree_vis : public QWidget
{
    Q_OBJECT

public:
    explicit tree_vis(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);
    int tree_Height(MyNode<double> *partial_root);
    const double PI=3.1415926;
    MyNode<double> *root, *test_root;
private:
    int max(const int a,const int & b);

};

#endif // TREE_VIS_H
