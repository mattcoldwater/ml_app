// Lirong Wang & Haoyu Wu
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "importPeptide.h"
#include "utils_why.h"
using namespace std;


/*
 * Function: importPeptide
 * Usage: importPeptide(string fileRoute);
 * ---------------------------------------
 * Reads text file containing one peptide sequence in a line;
 * Stores all peptide sequences in a vector of string;
 * Show users their original sequences.
 */

//Here, I assume our console has already got the fileRoute and judge whether it is available
//承接：user import fileRoute in console --> judge whether it exists or not; it's a txt or not
//I need to judge whether the file is in right form or not (one peptide in one line);
//also need to judge whether there exist unnatural amino acid or not
//In all, 4 judges.

void importPeptide(vector<int> *label_peptides, vector<string> *peptides, string txtRoute) {
    ifstream infile;
    infile.open(txtRoute);

    string peptide, raw_peptide;
    char label;

    while (getline(infile,raw_peptide)) {
        label = raw_peptide[0];
        peptide = raw_peptide.substr(2);
        if ((label != '0' && label != '1') || containUnnaturalPeptide(peptide) == false ) {
           cout <<peptide;
           printWarning();
           messageWARN("Wrong data format!");
           break;
        }
        if (label == '0') {
            label_peptides->push_back(0);
        }
        else {
            label_peptides->push_back(1);
        }
        peptides->push_back(peptide);
    }
}

/*
 * Function: containUnnaturalPeptide
 * Usage: if (containUnnaturalPeptide == false)
 * --------------------------------------------
 * Judge whether there exists a line contains unnatural amino acid;
 * if so, should return comments that our code cannot be applied to
 * this situation.
 */

//debug
bool containUnnaturalPeptide(string peptide){
    for (unsigned long i = 0; i < peptide.length(); i++) {
        bool judge = false;
        char ch = peptide[i];
        for (unsigned long j = 0; j < NATURAL_AA.size(); j++) {
            if (ch == NATURAL_AA[j]) {
                judge = true;
                break;
            }
        }
        if (judge == false) {
            return judge;
        }
    }
    return true;
}

/*
 * Function: printWarning
 * Usage: printWarning();
 * ----------------------
 * Returns warnings while the text file is in the improper form.
 */

void printWarning() {
    cout << "Warning:" << endl;
    cout << "Your file is in improper form, please check it and return a file in proper form instead." << endl;
    cout << "Please notice, the form which can be applied to this Binary Peptide Classifier should be, " << endl;
    cout << "1. There should be one and only one peptide sequence in a line;" << endl;
    cout << "2. There should only be natural amino acid in the sequences." << endl;
    cout << "Thanks a lot for your cooperation!" << endl;
}
