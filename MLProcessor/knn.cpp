#include "knn.h"
#include<string>
#include<vector>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <crossvalidation.h>
using namespace::std;

Knn::Knn() {
    vector<vector<double>> training_data;
    vector<int> label;
}

Knn::Knn(vector<vector<double>> input_training_data, vector<int> input_label) {
    training_data = input_training_data;
    label = input_label;
}

int Knn::getK() {
    return k;
}

void Knn::setK(int input_k) {
    k = input_k;
}

void Knn::setTraining(vector<vector<double>> input_training_data, vector<int> input_label) {
    training_data = input_training_data;
    label = input_label;
}

vector<double> Knn::accVsK(vector<vector<double>> testing_data, vector<int> input_label, int input_k) {
    vector<double> accuracy_vec;
    for (int i = 1; i < input_k + 1; i++) {
        k = i;
        vector<int> predict_vec = predictVec(testing_data);
        vector<double> eva = evaluation(predict_vec, input_label);
        double acc = eva[4];
        cout << acc << endl;
        accuracy_vec.push_back(acc);
    }
    return accuracy_vec;
}

int Knn::predictInt(vector<double> data) {
    vector<double> distance_vec;
    vector<double> k_distance;
    vector<int> k_index;
    for (unsigned int i = 0; i < training_data.size(); i++) {
        distance_vec.push_back(distanceNorm2(data, training_data[unsigned(i)]));
    }
    k_distance = distance_vec;
    std::sort (distance_vec.begin(),distance_vec.end());
    double boundary = distance_vec[unsigned(k)];
    for (unsigned int i = 0; i < k_distance.size(); i++) {
        if (k_distance[i] < boundary) {
            k_index.push_back(int(i));
        }
    }

    int class0 = 0;
    int class1 = 0;
    for (unsigned int i = 0; i < k_index.size(); i++) {
        if (label[unsigned(k_index[unsigned(i)])] == 0) {
            class0 = class0 + 1;
        } else {
            class1 = class1 + 1;
        }
    }
    if (class0>class1) {
        return 0;
    } else {
        return 1;
    }
}

vector<int> Knn::predictVec(vector<vector<double>> testing_data) {
    vector<int> predict_vec;
    for (unsigned i = 0; i < testing_data.size(); i++) {
        int predict_int = predictInt(testing_data[i]);
        //cout << predict_int << endl;
        predict_vec.push_back(predict_int);
    }
    return predict_vec;
}

double Knn::distanceNorm2(vector<double> data1, vector<double> data2) {
    double dist = 0.0;
    for (unsigned i = 0; i < data1.size(); i++) {
        dist = dist + pow((data1[i] - data2[i]),2.0);
    }
    dist = sqrt(dist);
    return dist;
}
