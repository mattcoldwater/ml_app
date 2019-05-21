#ifndef KNN_H
#define KNN_H
#include<vector>
#include<string>
using namespace std;

class Knn
{
public:
    Knn();
    Knn(vector<vector<double>> input_training_data, vector<int> input_label);
    int getK();
    void setK(int input_k);
    void setTraining(vector<vector<double>> input_training_data, vector<int> input_label);
    vector<int> predictVec(vector<vector<double>> testing_data);
    vector<double> accVsK(vector<vector<double>> testing_data, vector<int> input_label, int k = 10);
    int predictInt(vector<double> data);

private:
    double distanceNorm2(vector<double> data1, vector<double> data2);
    vector<vector<double>> training_data;
    vector<int> label;
    int k = 5;

};

#endif // KNN_H
