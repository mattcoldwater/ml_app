#ifndef REDUNDANCY_H
#define REDUNDANCY_H

#include<pca.h>
#include <vector>
#include<math.h>
using namespace std;

/*
 * Class: REDUNDANCY
 * ------------------------------------------
 * This class aims to find the redundancy and delete some variables.
 * Since we need to use the covariance matrix that same as in the class PCA, we use inheritance.
 */
template <typename T>
class REDUNDANCY:public PCA{
public:
    void cal_pearson(vector< vector<T> > & r, const vector< vector<T> > &data);
    void t_test(vector< vector<double> > & r,vector <vector<double> > & data );

};

template <typename T>
/*
 * Function: cal_pearson
 * -----------------------
 * This function calculate Pearson Correlation Coefficients between every two dimentions.
 * r = cov(x,y)/[n * sqrt(VarX)*sqrt(VarY)]
 */
void REDUNDANCY<T> ::cal_pearson(vector< vector<T> > & r, const vector< vector<T> > &data){
    vector < vector <T> > cov(data[0].size());
    for (int i = 0; i < data[0].size();i++){
        cov[i].resize(data[0].size(),0);
    }
    cal_covmatrix(cov,false);

    int feature_num = cov.size();
    r.resize(feature_num, 0);
    for (int i = 0; i < feature_num; i++){
        r[i].resize(feature_num,0);
    }

    for (int i = 0; i < feature_num; i++){
        for (int j = 0; j < feature_num; j++){
            r[i][j] = cov[i][j] / sqrt(cov[i][i]*cov[j][j]);
        }
    }

}

template <typename T>
/*
 * Function:t_test
 * ------------------
 * This function uses t-test to identify whether two variables are correlated.
 * t = r*sqrt(n-2)/sqrt(1-r^2) where r is the Pearson Correlation Coefficient.
 */
void REDUNDANCY<T> :: t_test(vector< vector<double> > &r, vector< vector<double> > & data){
    double stvalue = 1.645;    // Since the sample size is large, the tvale under 0.05 significant level is 1.645
    int sample_size = data.size();
    int feature_num = r.size();

    for (int i = 0; i < feature_num; i++){
        for (int j = 0; j < feature_num; j++){
            double tvalue = r[i][j]*sqrt(sample_size-2)/sqrt(1-pow(r[i][j],2));
            if (tvalue > stvalue){
                for (int k = 0; k < sample_size; k++){
                    data[k].erase(data[k].begin()+i);
                }
            }
        }
    }

}

#endif // REDUNDANCY_H
