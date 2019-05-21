#ifndef GETFEATURES_H
#define GETFEATURES_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "getfeaturename.h"
using namespace std;

/* Constants */

//const vector<string> AA_PAIRS = aaPairs();
//const vector<string> N5C5_AAC = n5c5aac();
const vector<char> AA_X = {'A','C','D','E','F','G','H','I','K','L','M','N','P','Q',
                                 'R','S','T','V','W','Y','X'};

/* Function prototypes */

vector< vector<double> > getAll(vector<string> peptides);
vector< vector<double> > getAllAAC(vector<string> peptides);
vector< vector<double> > getAllCKSAAP(vector<string> peptides);
vector< vector<double> > getAllN5C5AAC(vector<string> peptides);
vector<double> getAAC(string peptide);
vector<double> getCKSAAP(string peptide);
vector<double> getN5C5AAC(string peptide);
vector<string> getPairs(string peptide,int k);
string charToString(char ch);
string addX(string peptide);
string getN5C5(string peptide);


#endif // GETFEATURES_H
