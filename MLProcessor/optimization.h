#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H

#include "doublearray.h"
//#include "intarray.h"
#include "sigmoid.h"
#include <cmath>
#include <vector>

using namespace std;

//testing for data structure DoubleArray

double costFunctionInside(DoubleArray parameter, DoubleArray variable, int y);

double gradientCostFunctionInside(DoubleArray parameter, DoubleArray variable, int y, int posJ);

double runningAverageCostFunciotn(vector<DoubleArray> datasetVariable, vector<double> datasetY,
                                  DoubleArray parameter);

DoubleArray updateParameter(DoubleArray parameter, double learningRate,
                 vector<DoubleArray> datasetVariable, vector<double> datasetY);

DoubleArray fmin(DoubleArray parameter, vector<DoubleArray> datasetVariable,
                 vector<double> datasetY);

//testing vector<double>

double costFunctionInside2(vector<double> parameter, vector<double> variable, int y);

double gradientCostFunctionInside2(vector<double> parameter, vector<double> variable, int y, int posJ);

double runningAverageCostFunciotn2(vector<vector<double>> datasetVariable, vector<double> datasetY,
                                  DoubleArray parameter);

vector<double> updateParameter2(vector<double> parameter, double learningRate,
                 vector<vector<double>> datasetVariable, vector<double> datasetY);


vector<double> fmin2(vector<double> parameter, vector<vector<double>> datasetVariable,
                 vector<double> datasetY);


#endif // OPTIMIZATION_H
