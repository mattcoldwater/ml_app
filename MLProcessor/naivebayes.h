#ifndef NAIVEBAYES_H
#define NAIVEBAYES_H
#include <list>
#include<vector>
#include<string>
#include<map>
using namespace std;

vector<int> showResult(vector<vector<double>> training_data, vector<vector<double>> testing_data, vector<int> label);

vector<vector<double>> naiveBayes(vector<vector<double>> training_data, vector<vector<double>> testing_data, vector<int> label);

vector<vector<double>> bayesModel(vector<vector<double>> training_data, vector<int> label);

vector<double> priorDist(vector<int> label);

vector<double> conditionalDist(vector<vector<double>> training_data, vector<int> label, int data_label);

int testProb(vector<vector<double>> bayes_model, vector<double> test_data);
#endif // NAIVEBAYES_H
