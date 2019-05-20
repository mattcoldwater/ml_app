// Haoyu Wu
#ifndef UTILS_WHY_H
#define UTILS_WHY_H
#include <vector>
#include <string>
#include <iostream>
#include <QDebug>
using namespace std;

template<typename T> void outputVector(vector<T> & ivec);

template<typename T>
void outputVector(vector<T> & ivec) {
    cout<<ivec.size()<<endl;
    for(int i=0; i<int(ivec.size()); i++)
        cout << ivec[i] << " ";
}

template<typename T> void check_shape(const vector<vector<T>> & v);

template<typename T>
void check_shape(const vector<vector<T>> & v) {
    qDebug()<<v.size()<<","<<v[0].size();
}

void read_csv(vector<vector<double>> & strArray, vector<int> & labels, string file_name);

template<typename T>
struct MyNode
{
public:
    string feature_name;
    T split_condition;
    MyNode *leftNode, *rightNode;
    MyNode(string key, T spl_con, MyNode<T> *left=NULL, MyNode<T> * right=NULL);
};

template<typename T>
MyNode<T>::MyNode(string key, T spl_con, MyNode<T> *left, MyNode<T> * right) {
    feature_name = key;
    split_condition = spl_con;
    leftNode = left;
    rightNode = right;
}

struct stackMyNode
{
public:
   MyNode<double> *theNode;
   int theLayer;
};

void write_csv(const vector<vector<double>> & strArray, const vector<int> & labels, string file_name);

void imgPathToHtml(QString &path);

void messageOK(QString what);
void messageINFO(QString what);
void messageWARN(QString what);

#endif // UTILS_WHY_H
