// HaoyuWu
#include "tree_vis.h"
#include <QPainter>
#include <stack>
#include <QIcon>
#include <QDebug>

using namespace std;

tree_vis::tree_vis(QWidget *parent) :
    QWidget(parent)
{
    resize(750, 500);
    setWindowTitle("The Visualization of Decision Tree");
    root = NULL;
    MyNode<double> *node0 = new MyNode<double>("feature 1", 0.22);
    MyNode<double> *node1 = new MyNode<double>("feature 2", 0.31);
    MyNode<double> *node2 = new MyNode<double>("feature 3", 0.23);
    MyNode<double> *node3 = new MyNode<double>("feature 4", 0.56);
    MyNode<double> *node4 = new MyNode<double>("feature 5", 0.52);
    MyNode<double> *node5 = new MyNode<double>("feature 6", 0.51);
    MyNode<double> *one = new MyNode<double>("Anti-viral", -1);
    MyNode<double> *zero = new MyNode<double>("NOT\nAnti-viral", -1);
    node0->leftNode = node1;
    node0->rightNode = node2;
    node1->leftNode = node3;
    node1->rightNode = node4;
    node2->leftNode = node5;
    node2->rightNode = one;
    node3->leftNode = zero;
    node3->rightNode = one;
    node4->leftNode = zero;
    node4->rightNode = one;
    node5->leftNode = zero;
    node5->rightNode = one;
    test_root = node0;
}

int tree_vis::max(const int a,const int & b) {
    if (a>b) return a;
    return b;
}

int tree_vis::tree_Height(MyNode<double> *partial_root) {
    int left_h, right_h;
    left_h = 1;
    right_h = 1;
    if (!(partial_root->leftNode==NULL)) {
        left_h += tree_Height(partial_root->leftNode);
    };
    if (!(partial_root->rightNode==NULL)) {
        right_h += tree_Height(partial_root->rightNode);
    };
    return max(left_h, right_h);
}

void tree_vis::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    painter.drawPixmap(rect(), QPixmap("images/leaf.jpg"));

    //FONT
    QFont font;
    font.setPointSize(12);
    font.setBold(true);
    painter.setFont(font);

    //Pen
    QPen penLine;
    penLine.setWidth(2);
    penLine.setColor(Qt::black);
    penLine.setStyle(Qt::SolidLine);
    penLine.setCapStyle(Qt::FlatCap);
    penLine.setJoinStyle(Qt::BevelJoin);
    painter.setPen(penLine);

    double W = this->width();
    double H = this->height();

    int tree_height = tree_Height(root);
    double R = W / (2 * std::pow(2, tree_height) + 2);     // radius of the node
    const int layerHeight = (H-4*R) / (tree_height-1);    // vertical movement

    double r_ = 25;
    QRectF node(QPointF(-r_, -r_), QPointF(r_, r_));
    stack<stackMyNode> right_childs;
    stackMyNode qNode;

    stack<QPointF> points;
    QPointF point;

    double Hoffset;
    MyNode<double> *t = root;
    const double Pi = 3.14159;
    int curLayer = 1;
    int curAngle;
    double deg;

    painter.translate(W/2, 2*R);

    bool going = true;
    while (going)
    {
        painter.drawEllipse(node);

        QString temp;
        string f_name = t->feature_name;
        if (t->split_condition<0) {
            temp = "";
        } else {
            QString temp_split = QString::number(t->split_condition, 'g', 3);
            temp = "\n"+temp_split;
            f_name = string("F") + f_name[f_name.length()-1];
        }      
        painter.drawText(node, Qt::AlignCenter, QString::fromStdString(f_name)+temp);

        Hoffset = std::pow(2, (tree_height - curLayer)) * R;
        deg = std::atan(Hoffset / layerHeight);
        curAngle = int(180 / Pi * deg);

        if (t->rightNode != NULL)
        {
            painter.rotate(-curAngle);
            painter.drawLine(0, int(R), 0, int(layerHeight / cos(deg) - R));
            painter.rotate(curAngle);

            qNode.theNode = t->rightNode;
            qNode.theLayer = curLayer + 1;
            right_childs.push(qNode);

            points.push(QPointF(QPointF(0, 0) + QPointF(Hoffset, layerHeight)));
            painter.save();
        }
        if (t->leftNode != NULL)
        {

            painter.rotate(curAngle);
            painter.drawLine(0, int(R), 0, int(layerHeight / cos(deg) - R));
            painter.rotate(-curAngle);
            painter.translate(QPointF(QPointF(0, 0) + QPointF(-Hoffset, layerHeight)));
            t = t->leftNode;

            curLayer++;
        }
        else {
            if (!right_childs.empty()) {
                qNode = right_childs.top();
                right_childs.pop();
                t = qNode.theNode;
                curLayer = qNode.theLayer;

                painter.restore();
                point = points.top();
                points.pop();
                painter.translate(point);
            } else {
                painter.resetTransform();
                going=false;
            }
        }
    }
}

