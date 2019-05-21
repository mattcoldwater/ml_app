#ifndef PREDICT_H
#define PREDICT_H

#include "optimization.h"
#include "segmentation.h"

int predict(vector<double> parameters, vector<double> variables);

int predict2(vector<double> parameters, vector<double> variables, double threshold);

double accuracy(vector<vector<double>> test_data_frame, vector<double> y, vector<double> parameters);

#endif // PREDICT_H
