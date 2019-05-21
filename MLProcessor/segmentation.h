#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include "doublearray.h"
#include <vector>

using namespace std;

DoubleArray transform(vector<double> rawDataSet);

vector<DoubleArray> transformDataset(vector<vector<double>>);

#endif // SEGMENTATION_H
