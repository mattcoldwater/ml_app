// Lirong Wang
#ifndef IMPORTPEPTIDE_H
#define IMPORTPEPTIDE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/*
 * Constants
 * ---------
 * NATURAL_AA -- a vector contains all natural amino acid
 */

const vector<char> NATURAL_AA = {'A','C','D','E','F','G','H','I','K','L','M','N','P','Q',
                                 'R','S','T','V','W','Y'};

/* Function Prototypes */
void importPeptide(vector<int> *label_peptides, vector<string> *peptides, string txtRoute);
bool containUnnaturalPeptide(string peptide);
void printWarning();


#endif
