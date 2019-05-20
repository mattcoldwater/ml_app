// Haoyu Wu
#include "utils_why.h"
#include "QDebug"

int main2()
{
    vector<vector<double>> features;
    vector<int> labels;
    read_csv(features, labels, "D:\\project\\MLProcessor\\texts\\data_aac.csv");

    /*
    for (vector<double> feature : features) {
        outputVector(feature);
    }
    outputVector(labels);*/


    /*
     * M = model(features, labels);
     * pred_label = M.predict(features[0]);
     */

    return 0;
}
