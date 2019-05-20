#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include "pca.h"
#include <QDebug>
using namespace std;

PCA::PCA() {
  sample_size = 0;
  feature_num = 0;
}


PCA::~PCA() {
}


int PCA::load_data(vector< vector<double> >& data, vector<double>& labels){
    sample_size = data.size();
    this-> feature_num = data[0].size();
    this-> data.resize(this-> sample_size);
    for (int i = 0; i < this->sample_size; i++){
        this-> data[i].resize(this-> feature_num);
        memcpy(this->data[i].data(),data[i].data(),sizeof (double)*this->feature_num);
    }
    this-> labels.resize(this-> feature_num);
    memcpy(this-> labels.data(),labels.data(),sizeof (double)*this-> sample_size);

    return 0;
}

/*
 * Function: cal_covmatrix
 * -----------------------
 * Calculate the covariance matrix of data
 */

void PCA::cal_covmatrix(vector< vector<double> >& covar, bool scale ){
    vector<double> mean;
    const int rows = sample_size;
    const int cols = feature_num;
    const int nsample = rows;
    double ini_scale = 1.;
    if (scale) ini_scale = 1./nsample;

    covar.resize(cols);
    for (int i=0; i<cols; ++i){
        covar[i].resize(cols,0);
    }

    /* Calculate the mean * nsamples */
    mean.resize(cols,0);
    for (int m=0; m<cols; ++m){
        for (int n=0; n<rows; ++n){
            mean[m] += data[n][m];
        }
    }

    /* Calculate covariance between 2 variables */
    for (int i=0; i<cols; ++i){
        vector<double> value(rows, 0);
        for (int p=0; p<rows; ++p){
            value[p] = data[p][i]-mean[i];
        }
        for (int j=0; j<cols; ++j){
            double cov = 0;
            for (int q=0 ;q<rows; ++q){
                cov += value[q]*(data[q][j]-mean[j]);
            }
            covar[i][j] = cov;
        }
    }

}

/*
 * Function: eigen
 * --------------------
 * Use the Jocobi iteration.
 * (1) Initialize the eigen vector matrix V, a diag(1.......1)
 * (2) Find the the largest absoulte value of the elements in matrix A, except the diagonal elements Apq
 * (3) Calculate tan(2theta), sin(theta) and cos(theta) and matrix Upq
 * (4) Calculate A1; calculate the eigen vector matrix = V * Upq
 * (5) If the max |Apq| < some threshold, stop the preocess; otherwise, A = A1, iterate the (2)-(5)
 */

int PCA::eigen(vector< vector<double> >& covar, bool sort_, int max_iter, double threshold){
    auto n = covar.size();

    /* check whether the matrix is a square matrix */
    for (int i = 0; i < n; ++i){
        if (covar[i].size() != n){
            fprintf(stderr,"mat should be a square matrix");
        }
    }

    /* Initialize the eigen vectors matrix V and eigen values */
    vector< vector<double> > V(n);
    for (int i = 0; i < n; i++){
        V[i].resize(n);
    }
    for (int i = 0; i < n; i++){
        V[i][i] = 1;
        eigen_values.push_back(covar[i][i]);
    }
    int iter_num = 0;

    while(1){
        /* Find the biggest element in covariance matrix(absolute value, not diagnol) */
        double max = covar[0][1];
        int nRow = 0;
        int nCol = 1;
        for (int i = 0; i < n; i++){              /* row */
            for (int j = 0; j < n; j++){          /* column */
                if ( (i != j) && (abs(covar[i][j])) ){
                    max = covar[i][j];
                    nRow = i;   /* p */
                    nCol = j;   /* q */
                }
            }
        }

        if (max > threshold)                   /* When the maximum element in A is less than the threshold,break */
            break;
        if (iter_num > max_iter)               /* When #interation is bigger than the max, break */
            break;
        iter_num ++;

        /* Calculate the rotate angle and the rotate matrix covar' */
        double Apq = covar[nRow][nCol];
        double Aqq = covar[nCol][nCol];
        double App = covar[nRow][nRow];

        double theta = 0.5*atan2(-2*Apq,Aqq-App);
        double sintheta = sin(theta);
        double costheta = cos(theta);
        double sin2theta = sin(2*theta);
        double cos2theta = cos(2*theta);

        covar[nRow][nRow] = App*costheta*costheta + Aqq*sintheta*sintheta + 2*Apq*costheta*sintheta;
        covar[nCol][nCol] = App*sintheta*sintheta + Aqq*sintheta*sintheta - 2*Apq*costheta*sintheta;
        covar[nRow][nCol] = covar[nCol][nRow] = 0.5*(Aqq-App)*sin2theta + Apq*cos2theta;
        for (int i = 0; i < n; i++){
            if ( (i != nRow)&&(i != nCol) ){
                covar[nRow][i] = costheta*covar[nRow][i] + sintheta*covar[nCol][i];
                covar[nCol][i] = -sintheta*covar[nRow][i] + costheta*covar[nCol][i];
                covar[i][nRow] = costheta*covar[i][nRow] + sintheta*covar[i][nRow];
                covar[i][nCol] = -sintheta*covar[i][nCol] + costheta*covar[i][nCol];
            }
        }

        /* Calculate the eigen vectors : V * U */
        for (int k = 0; k < n; k++){
            V[nRow][k] = costheta*V[nRow][k] + sintheta*V[nRow][k];
            V[nCol][k] = -sintheta*V[nCol][k] + costheta*V[nCol][k];
        }

        }
    /* sort the eigen values */
    if (sort_){
        for (int k = 0 ; k < n-1; k++){
            int m = k;
            for (int i = k+1; i < n; i++){
                if (eigen_values[i] > eigen_values[m]) m = i;
            }
            if (m != k) {
                swap(eigen_values[m],eigen_values[k]);
                swap(V[m],V[k]);
            }
        }
    }
    eigen_vectors.resize(n);
    for (int i = 0; i < n; ++i){
        eigen_vectors[i].resize(n);
        for (int j = 0; j < n; ++j){
            eigen_vectors[i][j] = V[i][j];
        }
    }
    return 0;
}

/*
 * Function:output
 * ---------------------
 * Return a new vector< vector<T> > that represents principal components.
 * Equals to data * eigenvector
 */

vector< vector<double> > PCA::output(vector< vector<double> >& data){
    vector < vector <double> > cov(data[0].size());
    for (int i = 0; i < data[0].size();i++){
        cov[i].resize(data[0].size(),0);
    }
    cal_covmatrix(cov,false);
    eigen(cov,true,100,0.05);

    vector< vector<double> > output;
    int n = data.size();
    int p = data[0].size();
    output.resize(n);
    for (int i = 0; i < n; i++){
        output[i].resize(6,0);
    }
    for (int i = 0; i < n; i++){                   //For each observation y
        for (int j = 0; j < 6; j++){               //For each dimension in one observation
            for (int m = 0; m < p; m++){
                output[i][j] += data[i][m] * eigen_vectors[j][m];
            }
        }
    }
    return output;
}

vector< vector<double> > PCA::new_output(vector< vector<double> > & data){
//    vector < vector <double> > cov(data[0].size());
//    for (int i = 0; i < data[0].size();i++){
//        cov[i].resize(data[0].size(),0);
//    }
//    cal_covmatrix(cov,false);
//    eigen(cov,true,100,0.05);

    vector< vector<double> > output;
    int n = data.size();
    int p = data[0].size();
    output.resize(n);
    for (int i = 0; i < n; i++){
        output[i].resize(6,0);
    }
    for (int i = 0; i < n; i++){                   //For each observation y
        for (int j = 0; j < 6; j++){               //For each dimension in one observation
            for (int m = 0; m < p; m++){
                output[i][j] += data[i][m] * eigen_vectors[j][m];
            }
        }
    }
    return output;
}
