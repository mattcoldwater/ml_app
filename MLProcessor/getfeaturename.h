#ifndef GETFEATURENAME_H
#define GETFEATURENAME_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
 * Constants
 * ---------
 * NATURAL_AA_STR -- a vector contains all natural amino acid, and in string form
 * so that it can be combined to be attribute names of AAC feature.
 */
const vector<string> NATURAL_AA_STR = {"A","C","D","E","F","G","H","I","K","L","M","N","P","Q",
                                 "R","S","T","V","W","Y"};
const vector<string> AA_X_STR = {"A","C","D","E","F","G","H","I","K","L","M","N","P","Q",
                                 "R","S","T","V","W","Y","X"};

/* Function prototypes */
vector<string> allName();
vector<string> aaPairs();
vector<string> n5c5aac();

#endif // GETFEATURENAME_H
