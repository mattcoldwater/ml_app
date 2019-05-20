// HaoyuWu
#include "svm.h"
#include "ui_svm.h"
#include <QDebug>
#include <QThread>
#include <math.h>
#include <iostream>
#include <QTime>
using namespace std;

svm::svm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::svm)
{
    ui->setupUi(this);
    svm_background = QImage(2000, 2000, QImage::Format_ARGB32);
    svm_background.fill(QColor(255,255,255));
    threshold = -2;
    qDebug()<<"initialize svm";
}

svm::~svm()
{
    delete ui;
}

void svm::predict_X() {
    for (int i = 0; i < theSize; i++)
        {
            pre_Y[i] = 0;
            for(int j=0; j < theSize; j++)
            {
                pre_Y[i] += alphas[j] * labels[j] * svm_multiply(i, j);
            }
            pre_Y[i] += b;
    }
}

int svm::predict(vector<double> test_feature) {
    double pred = 0;
    for(int j=0; j < theSize; j++)
    {
        double result = 0;
        for (int k = 0; k < featureSize; k++)
        {
            result += test_feature[k] * features[j][k];
        }
        pred += alphas[j] * labels[j] * result;
    }
    pred += b;
    pred = (pred + 1.) / 2.0;
    if (pred < threshold) {
        return 0;
    } else {
        return 1;
    }
}

void svm::read_data(const vector<vector<double>> & pre_features, const vector<int> & label_peptides) {
    qDebug()<<"reading svm";
    for (unsigned int i=0; i<label_peptides.size(); i++) {
        if (label_peptides[i]==0) {
            labels.push_back(-1);
        } else {
            labels.push_back(1);
        }
    }
    vector<double> feature;
    for (unsigned int i=0; i<pre_features.size();i++) {
        feature.clear();
        feature.push_back(pre_features[i][0]);
        feature.push_back(pre_features[i][2]);
        features.push_back(feature);
    }
    qDebug()<<"read svm done";
}

double svm::svm_multiply(int i, int j) {
    double result = 0;
    for (int k = 0; k < featureSize; k++)
    {
        result += features[i][k] * features[j][k];
    }
    return result;
}

double svm::boundary(int x) {

    double boundary = 0;
    int i, j;
    for (i = 0; i < theSize; i++)
    {
        if (alphas[i]>0 && alphas[i] < C)
        {
            j = i;
            boundary = labels[j];
            break;
        }
    }
    for (i = 0; i < theSize; i++)
    {
        boundary -= alphas[i] * labels[i] * svm_multiply(i, j);
    }
    for (i = 0; i < theSize; i++)
    {
        boundary += alphas[i] * labels[i] * svm_multiply(x, i);
    }
    return boundary;
}

void svm::svm_update(int i1, int i2, double x1, double x2) {

    double b1_new = -(pre_Y[i1] - labels[i1]) - labels[i1] * svm_multiply(i1, i1)*(alphas[i1] - x1)  - labels[i2] * svm_multiply(i2, i1)*(alphas[i2] - x2) + b;
    double b2_new = -(pre_Y[i2] - labels[i2]) - labels[i1] * svm_multiply(i1, i2)*(alphas[i1] - x1)  - labels[i2] * svm_multiply(i2, i2)*(alphas[i2] - x2) + b;
    if (fabs(alphas[i1]) < eps || fabs(alphas[i1] - C) < eps || fabs(alphas[i2]) < eps || fabs(alphas[i2] - C) < eps)
        b = (b1_new + b2_new) / 2;
    else
        b = b1_new;
    predict_X();
}

int svm::Alpha2(int i1) {
    bool pos = (pre_Y[i1] - labels[i1] > 0);
        double tmp = pos ? 100000000 : -100000000;
        double ei = 0; int a2 = -1;
        for (int i = 0; i < theSize; i++)
        {
            ei = pre_Y[i] - labels[i];
            if (pos &&  ei < tmp || !pos && ei > tmp)
            {
                tmp = ei;
                a2 = i;
            }
        }
        return a2;
}

void svm::train(bool vis) {
    if ((threshold+1)<0.01) {
        set_threshold(0.5);
    }
    if (vis) this->show();
    this->inside_train(vis);
}

void svm::DelayMs(int ms) {
    QTime dieTime= QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void svm::inside_train(const bool & vis) {
    /*for (int i=0; i<2;i++) {
        QThread::sleep(3);
        after_train();
        QThread::sleep(3);
        svm_background.fill(QColor(255,255,255));
        repaint();
    }*/

    bool theUpdate = true;
    vector<int> visited(labels.size());
    int num = 1;
    int i1, i2, k;
    int count = 0;
    int iters = 0;

    qDebug()<<"training";
    while (num>0) {
        iters++;
        if (vis && iters > 25) break;
        if (!vis && iters > 4) break;
        if (vis) this->DelayMs(10);
        num = 0;
        count =0;
        for (int i=0; i<theSize;i++){
            if (theUpdate) {
                count = 0;
                for (int j=0; j<theSize;j++) {
                    if (alphas[j]>eps && alphas[j]<C-eps) {
                        count++;
                        visited[count]=j;
                    };
                }
                theUpdate = false;
             }
            if (alphas[i]>eps && alphas[i]<C-eps) {
                i1 = i;
                if (fabs(labels[i1] * pre_Y[i1] - 1)>eps) {
                    i2 =Alpha2(i1);
                    theUpdate = epoch(i1, i2);
                    if (theUpdate) {
                        num++;
                        continue;
                    } else {
                        for (int j=0; j<count; j++) {
                            if (visited[j]==i) continue;
                            i2 = visited[j];
                            theUpdate = epoch(i1, i2);
                            if (theUpdate) {
                                num++;
                                break;
                            }
                        }
                        if (theUpdate) continue;
                        k=0;
                        for (int j=0; j<theSize; j++) {
                            if (visited[k]==j) {
                                k++;
                                continue;
                            }
                            i2 = j;
                            theUpdate = epoch(i1, i2);
                            if (theUpdate) {
                                num++;
                                break;
                            }
                        }
                    }
                }
            }
        }

        if (theUpdate) {
            theUpdate = false;
            continue;
        }

        for (int i=0; i<theSize;i++) {
            i1 = i;
            if (fabs(alphas[i]) < eps && labels[i] * pre_Y[i] < 1 || fabs(alphas[i] - C) < eps && labels[i] * pre_Y[i] > 1) {
                i2 =Alpha2(i1);
                theUpdate = epoch(i1, i2);
                if (theUpdate) {
                    num++;
                    continue;
                } else {
                    for (int j=0; j<count; j++) {
                        if (visited[j]==i) continue;
                        i2 = visited[j];
                        theUpdate = epoch(i1, i2);
                        if (theUpdate) {
                            num++;
                            break;
                        }
                    }
                    if (theUpdate) continue;
                    k=0;
                    for (int j=0; j<theSize; j++) {
                        if (visited[k]==j) {
                            k++;
                            continue;
                        }
                        i2 = j;
                        theUpdate = epoch(i1, i2);
                        if (theUpdate) {
                            num++;
                            break;
                        }
                    }
                }
            }

        }

        if (vis) after_train();
    }

    qDebug()<<"training done";
//    for (int i=0; i<labels.size();i++) {
//        vector<double> row = features[i];
//        qDebug()<<row[0]<<" "<<row[1]<<" "<<predict(row)<<" "<<labels[i];
//    }
}

bool svm::epoch(int i1_, int i2_) {

    unsigned int i1 = i1_;
    unsigned int i2 = i2_;
    if (i1 < 0) return false;

    double x1, x2, L, H, s;
    x2 = alphas[i2];
    x1 = alphas[i1];

    s = labels[i1] * labels[i2];
    L = s < 0 ? max(0, alphas[i2] - alphas[i1]) : max(0, alphas[i2] + alphas[i1] - C);
    H = s < 0 ? min(C, C + alphas[i2] - alphas[i1]) : min(C, alphas[i2] + alphas[i1]);
    if (L >= H) return false;
    double eta = svm_multiply(i1, i1) + svm_multiply(i2, i2) - 2 * svm_multiply(i1, i2);

    if (eta > 0)
    {
        alphas[i2] = x2 + labels[i2] * (pre_Y[i1] - labels[i1] - pre_Y[i2] + labels[i2]) / eta;
        if (alphas[i2] < L) alphas[i2] = L;
        else if (alphas[i2] > H) alphas[i2] = H;
    }
    else
    {
        alphas[i2] = L;
        double Lobj = boundary(i2_);
        alphas[i2] = H;
        double Hobj = boundary(i2_);
        if (Lobj < Hobj - eps)
            alphas[i2] = L;
        else if (Lobj > Hobj + eps)
            alphas[i2] = H;
        else
            alphas[i2] = x2;
    }

    if (fabs(alphas[i2] - x2) < eps*(alphas[i2] + x2 + eps))
    {
        alphas[i2] = x2;
        return false;
    }

    alphas[i1] = x1 + s*(x2 - alphas[i2]);
    svm_update(i1_, i2_, x1, x2);
    return true;
}

double svm::min(double a, double b) {
    if (a<b) return a;
    return b;
}

double svm::max(double a, double b) {
    if (a>b) return a;
    return b;
}

void svm::after_train(){
    int w, h;
    w = ui->centralwidget->width();
    h = ui->centralwidget->height();
    for(int x=50; x<w; x++)
    {
        for(int y=50; y<h; y++)
        {
            vector<double> test_feature;
            double x1 = (x-50.)/(w-50.);
            double y1 = (y-50.)/(h-50.);
            test_feature.push_back(x1);
            test_feature.push_back(y1);
            int test_label = predict(test_feature);
//            qDebug()<<x1<<" "<<y1<<endl;
            if (test_label < threshold) {
                svm_background.setPixel(x, y , qRgba(255,70,70,100));
            } else {
                svm_background.setPixel(x, y , qRgba(70,70,250,100));
            };
        };
    };
    repaint();
}

void svm::paintEvent(QPaintEvent* e) {
    qDebug()<<"painting svm";
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    QColor rgb[3] = {QColor(255,0,0),QColor(0,255,0),QColor(0,0,255)};

    qDebug()<<"painting svm";
    painter.drawImage(0,0,this->svm_background);

    QPointF point;
    for(unsigned int i=0; i<labels.size(); i++)
    {
        painter.setBrush(QBrush(rgb[labels[i]+1]));
        point = QPointF(features[i][0]*ui->centralwidget->width()+50, features[i][1]*ui->centralwidget->height()+50);
//        point = QPointF(features[i][0]*10+50, features[i][1]*10+50);
        painter.drawEllipse(point, 3, 3);
    }
    qDebug()<<"painting svm";
}

void svm::set_threshold(double x) {
    threshold = x;

    alphas = vector<double>(labels.size(), 0);
    pre_Y = vector<double>(labels.size(), 0);
    theSize = labels.size();
    featureSize = features[0].size();
    b = 0;
}
