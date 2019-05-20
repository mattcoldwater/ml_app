//Lirong Wang & Dinglin Xia
#include <iostream>
#include <vector>
#include "crossvalidation.h"
#include "knn.h"
#include "predict.h"
#include "svm.h"
#include "naivebayes.h"
#include "model_evaluation.h"
using namespace std;

vector<double> all_predict_knn(vector< vector<double> > features, vector<int> labels) {
    Knn my_knn(features, labels);
    vector<int> pre_knn = my_knn.predictVec(features);
    vector<double> evaluation_vec = evaluation(pre_knn, labels);
    return evaluation_vec;
}

/*vector<double> all_predict_los(vector< vector<double> > features , vector<int> labels){
    vector<int> pre_los;
    vector<double> parameters_initial;
    for (int i = 0; i < features[0].size(); i++) {
        parameters_initial.push_back(0.1);
    }
    vector<double> labels_d;
    for (int j = 0; j < parame)
    vector<double> parameter = fmin2(parameters_initial, features, labels);
    vector<int> predict_result;
    for (int i = 0; i < features.size(); i++) {
        predict_result.push_back(predict(parameters_initial))
    }

    return pre_los;
}*/

vector<double> all_predict_svm(vector< vector<double> > features, vector<int> labels) {
    vector<int> pre_svm;
    svm my_svm;
    my_svm.read_data(features, labels);
    my_svm.train(false);
    for (int i = 0; i < features.size(); i++) {
        vector<double> feature = features[i];
        pre_svm.push_back(my_svm.predict(feature));
    }
    vector<double> evaluation_svm = evaluation(pre_svm,labels);
    return evaluation_svm;
}

vector<double> all_predict_bayes(vector< vector<double> > features, vector<int> labels) {
    vector<int> pre_bayes = showResult(features,features,labels);
    vector<double> evaluation_bayes = evaluation(pre_bayes,labels);
    return evaluation_bayes;
};

