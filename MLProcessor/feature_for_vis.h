#ifndef VISUALIZEFEATURES_H
#define VISUALIZEFEATURES_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "getfeatures.h"
#include "getfeaturename.h"
#include "quick_sort_cksaap.h"
using namespace std;

/* Function prototypes */
vector<string> pos_peptide(vector<int> labels, vector<string> peptides);
vector<string> neg_peptide(vector<int> labels, vector<string> peptides);

vector<double> averageAAC(vector<string> peptides);
vector<double> averageCKSAAP(vector<string> peptides);
vector<double> averageN5C5AAC(vector<string> peptides);

vector<double> cksaap_difference(vector<int> labels, vector<string> peptides) ;
vector<int> top20_diff_indice(vector<int> labels, vector<string> peptides);
vector<double> top20_diff(vector<int> labels, vector<string> peptides);
vector<string> top20_diff_name(vector<int> labels, vector<string> peptides);

#endif // VISUALIZEFEATURES_H
