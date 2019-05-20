#ifndef CROSSVALIDATION_H
#define CROSSVALIDATION_H
#include<vector>
#include<string>
#include<svm.h>
using namespace std;


vector<double> thresholdSelection(vector<vector<double>> training_data, vector<int> label, int k, vector<double> thresholds);
/*
 * Function: crossValidation
 * Usage: list list double average_performance = crossValidation(training_data, k);
 * ----------------------------------------------------
 * returns the average performance of each experiment during the cross validation.
 * The performance includes the average coefficients for the training model and
 * the average accuracy, error rate, precision and recall.
 */
double crossValidation_log(vector<vector<double>> training_data, vector<int> label, int k = 2, double threshold = 0.1);

/*
 * Function: nthExperiment
 * Usage: list list double average_performance = crossValidation(training_data, n);
 * ----------------------------------------------------
 * returns the performance of the nth experiment
 */


vector<vector<double>> crossValidation_bayes(vector<vector<double>> training_data, vector<int> label, int k);

vector<double> crossValidation_svm(vector<vector<double>> training_data, vector<int> label, int k, svm *svm_modelp);
/*
 * Function: nthExperiment
 * Usage: list list double average_performance = crossValidation(training_data, n);
 * ----------------------------------------------------
 * returns the performance of the nth experiment
 */


vector<double> nthExperiment_log(vector<vector<double>> training_data, vector<int> label, int n, int k, double threshold, vector<int> shuffle);

/*
 * Function: nthExperiment
 * Usage: list list double average_performance = crossValidation(training_data, n);
 * ----------------------------------------------------
 * returns the performance of the nth experiment
 */
vector<vector<double>> nthExperiment_bayes(vector<vector<double>> training_data, vector<int> label, int n, int k, vector<int> index);
/*
 * Function: evalutation
 * Usage: evalutation = evaluation(train_label, label);
 * ----------------------------------------------------
 * returns the evalutation of the experiment, including accuracy, error rate,
 * precision and recall. Which should be look like
 * --------------------------------------
 * |accuracy|error rate|precision|recall|
 * --------------------------------------
 */

vector<double> evaluation(vector<int> train_label, vector<int> label);

/*
 * Function: test
 * Usage: list double performance = test(coefficients, model, label);
 * ----------------------------------------------------
 * returns the performance of the experiment, including accuracy, error rate,
 * precision and recall.
 */

vector<double> test_log(vector<vector<double>> training_data, vector<double> coefficients);
/*class crossvalidation
{
public:
    crossvalidation();
};*/

#endif // CROSSVALIDATION_H
