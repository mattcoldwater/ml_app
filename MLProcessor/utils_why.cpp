// Haoyu Wu

#include "utils_why.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>
#include <QMessageBox>
#include <QList>
using namespace std;

void imgPathToHtml(QString &path)
 {
      path = QString("<img src=\"%1\"/>").arg(path);
 }

void read_csv(vector<vector<double>> & strArray, vector<int> & labels, string file_name) {
    vector<vector<double>> features;
    ifstream inFile(file_name, ios::in);
    string lineStr;
    ;
    vector<vector<double>> matrix;
    int j = 0;
    while (getline(inFile, lineStr))
    {
        j++;
        stringstream ss(lineStr);
        string str;
        vector<double> lineArray;
        if (j==1) continue;
        // 按照逗号分隔
        int i = 0;
        while (getline(ss, str, ',')) {
            i++;
            if (i==1) continue;
            if (i==2) {
                labels.push_back(atoi(str.c_str())-1);
            } else lineArray.push_back(atof(str.c_str()));
        }
//        cout << lineArray[0] << " "<< lineArray[1] << " "<< lineArray[2] << endl;
        strArray.push_back(lineArray);
    }

//    matrix = strArray;
//    vector<vector<double>> v(matrix[0].size(),vector<double>());
//    for(int i = 0; i < int(matrix.size()); i++)
//    {
//        for (int j = 0; j < int(matrix[0].size()); j++)
//        {
//            v[j].push_back(matrix[i][j]);
//        }
//    }
}

void write_csv(const vector<vector<double> > &strArray, const vector<int> &labels, string file_name)
{
    ofstream outFile; //输出文件流(输出到文件)
    outFile.open(file_name,ios::out);//打开模式可省略
    cout << "num: " << strArray.size() << "ar num: " << strArray[0].size() <<  "data num: " << labels.size() << endl;
    //随机取10条
    srand(time(0));
    int num  = 10;//每次随机取10个
    QList<int> temp;
    for(int i = 0; i < 10; i++){
        int randnum = rand()%(492);
        qDebug() << "随机数：" << randnum;
        temp.push_back(randnum);
    }
    if (outFile.is_open()){

        for(int i = 0; i < labels.size(); i++){
            if(temp.contains(i)){
                for(int j = 0; j < strArray[i].size(); j++){
                    outFile << strArray[i][j] << ',';
                }
                outFile << labels[i] << endl;
            }
        }
        outFile.close();
    }
}

void messageOK(QString what) {
    QMessageBox *msgBox;
    msgBox = new QMessageBox("Machine Learning (simple version)",
            what,
            QMessageBox::Information,
            QMessageBox::Ok | QMessageBox::Default,
            QMessageBox::Cancel | QMessageBox::Escape,
            0);
     msgBox->show();
}

void messageWARN(QString what) {
    QMessageBox *msgBox;
    msgBox = new QMessageBox("Machine Learning (simple version)",
            what,
            QMessageBox::Warning,
            QMessageBox::Ok | QMessageBox::Default,
            QMessageBox::Cancel | QMessageBox::Escape,
            0);
     msgBox->show();
}

void messageINFO(QString what) {
    QMessageBox *msgBox;
    msgBox = new QMessageBox("Prediction",
            what,
            QMessageBox::NoIcon,
            QMessageBox::Ok | QMessageBox::Default,
            QMessageBox::Cancel | QMessageBox::Escape,
            0);
     msgBox->show();
}

