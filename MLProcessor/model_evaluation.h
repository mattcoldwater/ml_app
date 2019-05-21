//Lirong Wang & Dinglin Xia
/*
 * File: model_evaluation.h
 * ------------------------
 * This file is used to accumulate all the predicted results of
 * knn, svm, naivebayes and logistic regression; later calculate
 * TP, TN, FP, FN to further evaluate models.
 */

#ifndef MODEL_EVALUATION_H
#define MODEL_EVALUATION_H

#include <iostream>
#include <vector>
#include "crossvalidation.h"
#include "knn.h"
#include "predict.h"
#include "svm.h"
#include "naivebayes.h"

vector<double> all_predict_knn(vector< vector<double> > features, vector<int> labels);
vector<double> all_predict_svm(vector< vector<double> > features, vector<int> labels);
vector<double> all_predict_bayes(vector< vector<double> > features, vector<int> labels);

#endif // MODEL_EVALUATION_H
