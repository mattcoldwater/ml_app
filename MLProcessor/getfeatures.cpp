#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "getfeaturename.h"
#include "getfeatures.h"
#include "importPeptide.h"
using namespace std;


/*
 * Function: getAll
 * Usage: getAll();
 * ------------------------
 * Combines all features including AAC, CKSAAP, N5C5 AAC and class lables into a
 * vector<vector> structure for later preposessing.
 * One observation in each inside vector of vector<vector> structure.
 */

vector< vector<double> > getAll(vector<string> peptides){
    vector< vector<double> > allAAC = getAllAAC(peptides);
    vector< vector<double> > allCKSAAP = getAllCKSAAP(peptides);
    vector< vector<double> > allN5C5AAC = getAllN5C5AAC(peptides);
    vector< vector<double> > allData(peptides.size());
    for (unsigned long i = 0; i < peptides.size(); i++) {
        allData[i].insert(allData[i].end(),allAAC[i].begin(),allAAC[i].end());
        allData[i].insert(allData[i].end(),allCKSAAP[i].begin(),allCKSAAP[i].end());
        allData[i].insert(allData[i].end(),allN5C5AAC[i].begin(),allN5C5AAC[i].end());
    }
    return allData;
}


/*
 * Function: getAllAAC
 * Usage: getAllAAC(all_peptides);
 * -------------------------------
 * Stores Amino Acid Composition of each peptide into a vector<vector> structure.
 */
//Later, it will be used to compute AAC of the whole positive or negative set
//and draw histograms of AAC.

vector< vector<double> > getAllAAC(vector<string> peptides) {
    unsigned long num_of_row = peptides.size();
    vector< vector<double> > allAAC(num_of_row);
    for (unsigned long i = 0; i < num_of_row; i++) {
        string pep = peptides[i];
        vector<double> aac = getAAC(pep);
        allAAC[i] = aac;
    }
    return allAAC;
}


/*
 * Function: getAllCKSAAP
 * Usage: getAllCKSAAP(all_peptides);
 * ----------------------------------
 * Stores CKSAAP of each peptide into a vector<vector> structure.
 */
//Used for later histogram drawing of CKSAAP

vector< vector<double> > getAllCKSAAP(vector<string> peptides) {
    unsigned long num_of_row = peptides.size();
    vector< vector<double> > allCKSAAP(num_of_row);
    for (unsigned long i = 0; i < num_of_row; i++) {
        string pep = peptides[i];
        vector<double> cksaap = getCKSAAP(pep);
        allCKSAAP[i] = cksaap;
    }
    return allCKSAAP;
}


/*
 * Function: getAllN5C5AAC
 * Usage: getAllN5C5AAC(all_peptides);
 * ----------------------------------
 * Stores N5C5 AAC of each peptide into a vector<vector> structure.
 */
//Used for later histogram drawing of N5C5 AAC

vector< vector<double> > getAllN5C5AAC(vector<string> peptides) {
    unsigned long num_of_row = peptides.size();
    vector< vector<double> > allN5C5AAC(num_of_row);
    for (unsigned long i = 0; i < num_of_row; i++) {
        string pep = peptides[i];
        vector<double> n5c5aac = getN5C5AAC(pep);
        allN5C5AAC[i] = n5c5aac;
    }
    return allN5C5AAC;
}


/*
 * Function: getAAC
 * Usage: vector<double> aac = getAAC(pep);
 * ----------------------------------------
 * Computes amino acid composition of each peptide.
 */

vector<double> getAAC(string peptide) {
    vector<double> aac(20,0);
    int size = peptide.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 20; j++) {
            if (peptide[i] == NATURAL_AA[j]) {
                aac[j]++;
                break;
            }
        }
    }
    for (int k = 0; k < 20; k++) {
        aac[k] = aac[k]/size;
    };
    return aac;
}

/*
 * Function: getCksaap
 * Usage: vector<double> cksaap = getCksaap(pep);
 * ----------------------------------------------
 * Computes compositions of k-spaced amino acid paris.
 */
//Here only get one situation of k = 0.

vector<double> getCKSAAP(string peptide) {
    //Here, only consider k=0 now
    vector<string> pairs = getPairs(peptide,0);
    vector<string> aa_pairs = aaPairs();
    vector<double> cksaap(400,0);
    if (pairs.size() == 0) return cksaap;
    for (unsigned long i = 0; i < pairs.size(); i++) {
        for (unsigned long j = 0; j < aa_pairs.size(); j++) {
            if (pairs[i] == aa_pairs[j]) {
                cksaap[j]++;
                break;
            }
        }
    }
    for (unsigned long k = 0; k < aa_pairs.size(); k++) {
        cksaap[k] = cksaap[k]/pairs.size();
    }
    return cksaap;
}

/*
 * Function: getN5C5AAC
 * Usage: vector<double> n5c5aac = getN5C5AAC(pep);
 * ------------------------------------------------
 * Computes Amino Acid Composition of N5 and C5 of a peptide.
 * If there are less than 10 amino acid of a peptide, then add X instead.
 */

vector<double> getN5C5AAC(string peptide) {
    string n5c5;
    if (peptide.size() < 10) {
        n5c5 = addX(peptide);
    } else if (peptide.size() == 10) {
        n5c5 = peptide;
    } else {
        n5c5 = getN5C5(peptide);
    }

    vector<double> n5c5aac(21,0);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 21; j++) {
            if (n5c5[i] == AA_X[j]) {
                n5c5aac[j]++;
                break;
            }
        }
    }
    for (int k = 0; k < 21; k++) {
        n5c5aac[k] = n5c5aac[k]/10;
    }
    return n5c5aac;
}


/*
 * Function: getPairs
 * Usage: vector<string> pairs = getPairs(peptide);
 * ------------------------------------------------
 * Obtains all amino acid pairs within a peptide.
 * Later to compute CKSAAP.
 */
//Only the situation with k = 0 now;
//How to handle eg: k = 5 and peptide_length < 7??

vector<string> getPairs(string peptide, int k) {
    vector<string> aaPairs;
    if (peptide.size() < k + 2) return aaPairs;
    for (int i = 0; i < peptide.size() - k - 1; i++) {
        string aa_1 = charToString(peptide[i]);
        string aa_2 = charToString(peptide[i+k+1]);
        string pair = aa_1 + aa_2;
        aaPairs.push_back(pair);
    }
    return aaPairs;
}

/*
 * Function: charToString
 * Usage: string aa_1 = charToString(peptide[i]);
 *        string aa_2 = charToString(peptide[i+k+1]);
 *---------------------------------------------------
 * Changes type character into type string so that they can combine and form
 * new strings.
 */

string charToString(char ch) {
    string str;
    stringstream ss;
    ss << ch;
    str = ss.str();
    return str;
}

/*
 * Function: addX
 * Usage: n5c5 = addX(peptide);
 * ----------------------------
 * Adds X as an unknown amino acid to the end of a peptide whose length is less
 * than 10.
 */

string addX(string peptide) {
    string new_pep = peptide;
    while (new_pep.size() < 10) {
        new_pep = new_pep + "X";
    }
    return new_pep;
}

/*
 * Function: getN5C5
 * Usage: n5c5 = getN5C5(peptide);
 * -------------------------------
 * Gets amino acids of N and C terminals of a peptide.
 */

string getN5C5(string peptide) {
    int len = peptide.size();
    string n5c5 = peptide.substr(0,5) + peptide.substr(len-5,5);
    return n5c5;
}

