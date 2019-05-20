/* File: crossvalidation.cpp
 * ------------------*
 * This file implements the crossvalidation.h interface.
 */

#include "naivebayes.h"
#include<crossvalidation.h>
#include<vector>
#include<string>
#include<iostream>
#include<math.h>
#include <algorithm>
#include <svm.h>
#include "doublearray.h"
#include "optimization.h"
#include "predict.h"
#include "segmentation.h"
#include "sigmoid.h"
using std::random_shuffle;
using namespace std;

/* Implementation notes: crossValidation
 * ----------------------------------
 */

vector<double> thresholdSelection(vector<vector<double>> training_data, vector<int> label, int k, vector<double> thresholds) {
    vector<double> acc_vec;
    for (int i = 0; i<thresholds.size(); i++) {
        double acc = crossValidation_log(training_data, label, 12, thresholds[i]);
        acc_vec.push_back(acc);
    }
    return acc_vec;
}

double crossValidation_log(vector<vector<double>> training_data, vector<int> label, int k, double threshold) {
    /* The following line juedge whether the data can be divided into k partitions equally. If
       it could not, it will allow user to input another k.
       ----------------------------------------------------
     */
    int n = int(training_data.size());
    cout<< n << endl;
    while (n % k != 0) {
        cout << "The dataset can't be divided equally." << endl;
        cout << "Please input the number of training fold:";
        cin >> k;
    }
    
    vector<int> shuffle_index;
    for (int i = 0; i < n; i++) {
        shuffle_index.push_back(i);
    }
    random_shuffle(shuffle_index.begin(), shuffle_index.end());

    /*
     * all_performance records all performance (including parameters and evaluation of model), which looks like
     * ------------------------------------------------------------------------------------------
     * | parameter[0] | parameter[1] | parameter[2] | ...... | parameter[n] | TP | TN | FP | FN |
     * ------------------------------------------------------------------------------------------
     */
    vector<vector<double>>  all_performance;  // Variable storing parameter and performance of each experiment
    vector<double> avr_performance;
    for (int i = 0; i < n; i++) {
        vector<double> nth_performance = nthExperiment_log(training_data, label, i, k, threshold, shuffle_index);// collect coefficients and performanceof
        all_performance.push_back(nth_performance);
    }
        
    int allvector_len = int(all_performance.size());
    int vector_len = int(all_performance.back().size());
    for (int i = 0; i < vector_len; i++) {
        double avr = 0;
        for (int j = 0; j < allvector_len; j++) {
            avr = avr + all_performance[unsigned(j)][unsigned(i)];
        }
        avr = avr/k;
        avr_performance.push_back(avr);
    }
    double avr_acc = avr_performance[avr_performance.size()-4];
    return avr_acc;
}

vector<vector<double>> crossValidation_bayes(vector<vector<double>> training_data, vector<int> label, int k) {
    int n = int(training_data.size());
    /*while (n % k != 0) {
        cout << "The dataset can't be divided equally." << endl;
        cout << "Please input the number of training fold:";
        cin >> k;
    }*/

    vector<int> shuffle_index;
    for (int i = 0; i < n; i++) {
        shuffle_index.push_back(i);
    }
    random_shuffle(shuffle_index.begin(), shuffle_index.end());

    //vector<vector<vector<double>>>  all_performance;  // Variable storing parameter and performance of each experiment
    vector<vector<double>> avr_performance;
    for (int i = 0; i < k; i++) {
        if (i == 0) {
            avr_performance = nthExperiment_bayes(training_data, label, i, k, shuffle_index);
        } else {
            vector<vector<double>> new_performance = nthExperiment_bayes(training_data, label, i, k, shuffle_index);
            for (unsigned int j = 0; j < new_performance.size(); j++) {
                for (unsigned int k = 0; k < new_performance[j].size(); k++) {
                    avr_performance[j][k] = avr_performance[j][k] + new_performance[j][k];
                }
            }
        }
        //vector<vector<double>> nth_performance = nthExperiment_bayes(training_data, label, i, k, shuffle_index);// collect coefficients and performanceof
        //all_performance.push_back(nth_performance);
    }

    /*for (unsigned int i = 0; i < all_performance.size(); i++){
        if (i == 0) {
            avr_performance = all_performance[i];
        } else {
            for (unsigned int j = 0; j < all_performance[i].size(); j++){
                for (unsigned int k = 0; k < all_performance[0][j].size(); k++) {
                    avr_performance[j][k] = avr_performance[j][k] + all_performance[i][j][k];
                }
            }
        }
    }*/
    for (unsigned int i = 0; i < avr_performance.size(); i++) {
        for (unsigned int j = 0; j < avr_performance[i].size(); j++) {
            avr_performance[i][j] = avr_performance[i][j]/double(k);
        }
    }
    return avr_performance;
}

vector<double> crossValidation_svm(vector<vector<double>> training_data, vector<int> label, int k, svm* svm_modelp) {
    int n = int(training_data.size());
    vector<double> threshold;
    threshold.push_back(0.3);
    threshold.push_back(0.4);
    threshold.push_back(0.5);
    threshold.push_back(0.6);
    threshold.push_back(0.7);
    /*while (n % k != 0) {
        cout << "The dataset can't be divided equally." << endl;
        cout << "Please input the number of training fold:";
        cin >> k;
    }

    vector<int> shuffle_index;
    for (int i = 0; i < n; i++) {
        shuffle_index.push_back(i);
    }
    random_shuffle(shuffle_index.begin(), shuffle_index.end());

    //vector<vector<vector<double>>>  all_performance;  */
    vector<double> avr_performance;
    int thresize = threshold.size();
    for (int j = 0; j < thresize; j++) {
        double performance;
        vector<int> predict_vec;
        svm_modelp->set_threshold(threshold[j]);
        svm_modelp->train(false);
        for (int i = 0; i < n; i++) {
            int single_predict = svm_modelp->predict(training_data[i]);
            predict_vec.push_back(single_predict);
        }
        vector<double> all_performance = evaluation(predict_vec, label);
        avr_performance.push_back(all_performance[4]);
    }
    return avr_performance;
}

vector<double> nthExperiment_log(vector<vector<double>> training_data, vector<int> label, int n, int k, double threshold, vector<int> index) {
    int data_len = int(training_data.size());
    //int data_wid = int(training_data[0].size());
    int section_len = data_len/k;
    vector<vector<double>> n_training_data;
    vector<int> n_training_label;
    vector<vector<double>> n_testing_data;
    vector<int> n_testing_label;
    for (int i = 0; i < k; i++) {
        for (int j = i * section_len; j < i * (section_len + 1); j++) {
            if (i == n) {
                n_testing_data.push_back(training_data[unsigned(index[unsigned(j)])]);
                n_testing_label.push_back(label[unsigned(index[unsigned(j)])]);
            } else {
                n_training_data.push_back(training_data[unsigned(index[unsigned(j)])]);
                n_training_label.push_back(label[unsigned(index[unsigned(j)])]);
            }
        }
    }

    vector<double> parameters_initial;
    for (int i=0; i<n_training_data[0].size(); i++){
        //initialize parameters to be 0.1
        parameters_initial.push_back(0.1);
      }
    vector<double> n_training_lebel_d;
    for (int i = 0; i < n_training_label.size(); i++) {
        n_training_label.push_back(double(n_training_label[i]));
    }
    vector<double> trained_parameter = fmin2(parameters_initial, n_training_data, n_training_lebel_d);
    vector<int> train_result; //= test(vector<vector<double>> n_training_data, model, vector<vector<double>> n_testing_data);
    for (unsigned int i = 0; i < n_testing_label.size(); i++){
        int test_sample = predict2(trained_parameter, n_testing_data[i], threshold);
        train_result.push_back(test_sample);
    }
    vector<double> evaluation_vec = evaluation(train_result, n_testing_label);
    for (unsigned int i = 0; i < 8; i++) {
        trained_parameter.push_back(evaluation_vec[i]);
    }

    return trained_parameter;
}

vector<vector<double>> nthExperiment_bayes(vector<vector<double>> training_data, vector<int> label, int n, int k, vector<int> index) {
    int data_len = int(training_data.size());
    int section_len = data_len/k;
    vector<vector<double>> n_training_data;
    vector<vector<double>> n_testing_data;
    vector<int> n_training_label;
    vector<int> n_testing_label;
    for (int i = 0; i < k; i++) {
        for (int j = i * section_len; j < section_len * (i + 1); j++) {
            if (i == n) {
                n_testing_data.push_back(training_data[unsigned(index[unsigned(j)])]);
                n_testing_label.push_back(label[unsigned(index[unsigned(j)])]);
            } else {
                n_training_data.push_back(training_data[unsigned(index[unsigned(j)])]);
                n_training_label.push_back(label[unsigned(index[unsigned(j)])]);
            }
        }
    }
    /*vector<double> prior_dist = priorDist(label);
    vector<double> cond_dist_0 = conditionalDist(n_training_data, n_training_label, 0);
    vector<double> cond_dist_1 = conditionalDist(n_training_data, n_training_label, 1);
    vector<int> nth_result_vec = showResult(n_training_data, n_testing_data, n_training_label);*/
    vector<vector<double>> nth_result = bayesModel(n_training_data, n_training_label);
    vector<int> nth_result_vec = showResult(n_training_data, n_testing_data, n_training_label);
    vector<double> evaluation_vec = evaluation(nth_result_vec, n_testing_label);
    nth_result.push_back(evaluation_vec);
    cout << evaluation_vec[4] << endl;
    return nth_result;
}

/*
 * The vector stores the performance of the model, which looks:
 * ----------------------------------------------------------------------
 * | TP | TN | FP | FN | accuracy | err | sensitivity | specifity | fpr |
 * ----------------------------------------------------------------------
 */

vector<double> evaluation(vector<int> train_result, vector<int> label) {
    vector<double> evalutation_vec;
    unsigned int data_len = train_result.size();
    int TP = 0;
    int TN = 0;
    int FP = 0;
    int FN = 0;
    for (unsigned int i = 0; i < data_len; i++) {
        if (train_result[unsigned(i)] == 1 && train_result[unsigned(i)] == label[unsigned(i)]) {
            TP = TP + 1;
        } else if (train_result[unsigned(i)] == 1 && train_result[unsigned(i)] != label[unsigned(i)]) {
            FP = FP + 1;
        } else if (train_result[unsigned(i)] == 0 && train_result[unsigned(i)] == label[unsigned(i)]) {
            TN = TN + 1;
        } else /*if (train_result[unsigned(i)] == 0 && train_result[unsigned(i)] != label[unsigned(i)])*/ {
            FN = FN + 1;
        }
    }
    evalutation_vec.push_back(TP);
    evalutation_vec.push_back(TN);
    evalutation_vec.push_back(FP);
    evalutation_vec.push_back(FN);
    double accuracy = double(TP + TN)/double(TP + TN + FP + FN);
    evalutation_vec.push_back(accuracy);
    double err = double(FP + FN)/double(TP + TN + FP + FN);
    evalutation_vec.push_back(err);
    double sensitivity = double(TP)/double(TP + FP);
    evalutation_vec.push_back(sensitivity);
    double specificity = double(TN)/double(TN + FN);
    evalutation_vec.push_back(specificity);
    double fpr = double(FP)/double(FP + TN);
    evalutation_vec.push_back(fpr);
    return evalutation_vec;
}

vector<double> test_log(vector<vector<double>> training_data, vector<double> coefficients) {
    vector<double> test_result;
    int data_len = int(training_data.size());
    vector<double> test_value; //= logisticTest(vector<vector<double>> training_data, vector<vector<double>> training_data);
    for (int i = 0; i < data_len; i++) {
        double test_value;// = 1/(1 + pow(M_E, multiplies(coefficients, training_data[i])));
        if (test_value > coefficients[coefficients.size()-1]) {
            test_result.push_back(1);
        } else {
            test_result.push_back(0);
        }
    }
return test_result;
}
