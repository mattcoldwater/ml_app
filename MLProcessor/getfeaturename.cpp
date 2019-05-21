#include <iostream>
#include <vector>
#include <string>
#include "getfeaturename.h"
#include "getfeatures.h"
using namespace std;

/*
 * Function: allName
 * Usage: allName();
 * -----------------
 * Gets all names for all the original features including AAC, CKSAAP, and N5C5_AAC,
 * and also there is a line for class labels.
 */

vector<string> allName() {
    vector<string> allName;
    allName.insert(allName.end(), NATURAL_AA_STR.begin(), NATURAL_AA_STR.end());
    vector<string> aa_pairs = aaPairs();
    allName.insert(allName.end(), aa_pairs.begin(), aa_pairs.end());
    vector<string> nc_aac = n5c5aac();
    allName.insert(allName.end(),nc_aac.begin(), nc_aac.end());
    return allName;
}

/*
 * Function: aaPairs
 * Usage: aaPairs()
 * ----------------
 * Gets all 400 kinds of amino acid pairs.
 */
//How to change the output into a const vector?

vector<string> aaPairs() {
    vector<string> aaPairs;
    for (unsigned long i = 0; i < NATURAL_AA_STR.size(); i++) {
        for (unsigned long j = 0; j < NATURAL_AA_STR.size(); j++) {
            string pair = NATURAL_AA_STR[i] + NATURAL_AA_STR[j];
            //cout << pair << " ";
            aaPairs.push_back(pair);
        }
    }
    return aaPairs;
}

vector<string> n5c5aac() {
    vector<string> n5c5aac;
    for (unsigned long i = 0; i < NATURAL_AA_STR.size(); i++) {
        string name = "NC_" + NATURAL_AA_STR[i];
        n5c5aac.push_back(name);
    }
    n5c5aac.push_back("NC_X");
    return  n5c5aac;
}
