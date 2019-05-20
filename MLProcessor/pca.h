#ifndef PCA_H
#define PCA_H

#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include "cluster.h"
using namespace std;


class PCA {
public:
    PCA();
    ~PCA();
    int load_data(vector< vector<double> >& data, vector<double>& labels);
    vector< vector<double> > output(vector< vector<double> >& data);
    vector< vector<double> > new_output(vector< vector<double> > & data);

    int eigen(vector< vector<double> >& covar, bool sort_ = true, int max_iter = 100, double threshold = 0.05);
    void cal_covmatrix(vector< vector<double> >& cov, bool scale = false);
    
    vector< vector<double> > data;
    vector<double> labels;
    int sample_size;
    int feature_num;
    vector< double > eigen_values;
    vector< vector<double> > eigen_vectors;

};


#endif // PCA_H
