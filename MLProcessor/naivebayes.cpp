/* File: naivebayes.cpp
 * ------------------*
 * This file implements the naivebayes.h interface.
 */

#include <list>
#include<vector>
#include<string>
#include<map>
#include<naivebayes.h>
#include <math.h>
#include<iostream>
using namespace std;

/* Implementation notes: priorDist
 * ----------------------------------
 */

vector<int> showResult(vector<vector<double>> training_data, vector<vector<double>> testing_data, vector<int> label) {
    vector<vector<double>> bayesP = naiveBayes(training_data, testing_data, label);
    vector<int> result;
    for (unsigned int i = 0; i < bayesP.size(); i++) {
        if (bayesP[i][0] >= bayesP[i][1]) {
            result.push_back(0);
        } else {
            result.push_back(1);
        }
    }
    return result;
}

vector<vector<double>> naiveBayes(vector<vector<double>> training_data, vector<vector<double>> testing_data, vector<int> label) {
    vector<double> prior_dist;
    vector<double> cond_dist_0;
    vector<double> cond_dist_1;
    vector<vector<double>> bayes_model = bayesModel(training_data, label);
    prior_dist = bayes_model[2];
    cond_dist_0 = bayes_model[0];
    cond_dist_1 = bayes_model[1];
    
    vector<vector<double>> testP;
    for (unsigned int i = 0; i < testing_data.size(); i++) {
        vector<double> data_testP;
        unsigned int m = testing_data[i].size();
        double prob1 = 1;
        double prob2 = 1;
        for (unsigned int j = 0; j < m; j++) {
            if (cond_dist_0[i] > 0 && cond_dist_1[i] > 0) {
                prob1 = prob1 * pow(cond_dist_0[i], testing_data[i][j]);
                prob2 = prob2 * pow(cond_dist_1[i], testing_data[i][j]);
            } else {
                prob1 = prob1 * pow(0.3, testing_data[i][j]);
                prob2 = prob2 * pow(0.3, testing_data[i][j]);
            }

        }
        prob1 = prob1 * prior_dist[0];
        prob2 = prob2 * prior_dist[1];
        data_testP.push_back(prob1);
        data_testP.push_back(prob2);
        testP.push_back(data_testP);
    }
    
    return testP;
}

vector<vector<double>> bayesModel(vector<vector<double>> training_data, vector<int> label) {
    vector<vector<double>> bayes_model;
    vector<double> prior = priorDist(label);
    vector<double> cond0 = conditionalDist(training_data, label, 0);
    vector<double> cond1 = conditionalDist(training_data, label, 1);
    bayes_model.push_back(cond0);
    bayes_model.push_back(cond1);
    bayes_model.push_back(prior);
    return  bayes_model;
}

vector<double> priorDist(vector<int> label) {
    unsigned int vec_len = label.size();
    int c0_count = 0;
    int c1_count = 0;
    for (unsigned int i = 0; i < vec_len; i++) {
        if (label[i] == 1) {
            c1_count = c1_count + 1;
        } else if (label[i] == 0) {
            c0_count = c0_count + 1;
        }
    }
    double c1_p = c1_count/double(vec_len);//int(vec_len);
    double c0_p = c0_count/double(vec_len);//int(vec_len);
    vector<double> prior;
    prior.push_back(c0_p);
    prior.push_back(c1_p);
    return prior;
}

vector<double> conditionalDist(vector<vector<double>> training_data, vector<int> label, int test_label) {
    unsigned int attribute_size = training_data[0].size();
    unsigned int data_size = training_data.size();
    vector<double> conditionalAttr;
    for (unsigned int i = 0; i < attribute_size; i++) {
        double prob = 1;
        int label_count = 0;
        for (unsigned int j = 0; j < data_size; j++) {
            if (label[j] == test_label) {
                label_count = label_count + 1;
                prob = prob + training_data[j][i];
            }
        }
        prob = prob/double(label_count);
        conditionalAttr.push_back(prob);
    }
    return conditionalAttr;
}

int testProb(vector<vector<double>> bayes_model, vector<double> test_data) {
    unsigned int m = test_data.size();
    double prob1 = 1;
    double prob2 = 1;
    vector<double> cond_prob1 = bayes_model[0];
    vector<double> cond_prob2 = bayes_model[1];
    vector<double> prior = bayes_model[2];
    for (unsigned int i = 0; i < m; i++) {
        if (cond_prob1[i] > 0) {
            prob1 = prob1 * pow(cond_prob1[i], test_data[i]);
        } else {
            prob1 = prob1 * pow(0, test_data[i]);
        }
        if (cond_prob2[i] > 0) {
            prob2 = prob2 * pow(cond_prob2[i], test_data[i]);
        } else {
            prob2 = prob2 * pow(0, test_data[i]);
        }
    }
    prob1 = prob1 * prior[0];
    prob2 = prob2 * prior[1];
    if (prob1 > prob2) {
        return 0;
    } else {
        return 1;
    }
}
