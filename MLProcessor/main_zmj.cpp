#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "importPeptide.h"
#include "getfeaturename.h"
#include "getfeatures.h"
#include "pca.h"
#include "utils_why.h"
#include <numeric> //for test of features
using namespace std;

int main_zmj() {
    vector<int> label_peptides;
    vector<string> st;
    importPeptide(& label_peptides, & st, "D:\\project\\MLProcessor\\texts\\data.txt");
    vector< vector<double> > allData = getAll(st);

    PCA animo;
    vector <double> labels(allData.size(),0);
    animo.load_data(allData,labels);
    vector< vector<double> > out = animo.output(allData);
//    for (vector<double> temp : out){
//        outputVector(temp);
//    }
    vector< vector<double> > newData;
    newData.push_back(allData[0]);
    vector< vector<double> > new_out = animo.new_output(newData);
    for (vector<double> temp : new_out){
        outputVector(temp);
    }
    return 0;
}
