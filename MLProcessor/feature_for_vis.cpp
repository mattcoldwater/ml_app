#include <iostream>
#include <vector>
#include <algorithm>
#include "getfeatures.h"
#include "getfeaturename.h"
#include "quick_sort_cksaap.h"
#include "feature_for_vis.h"
using namespace std;

/*
 * Function: pos_peptide
 * ---------------------
 * Return all positive data according to the labels.
 */

vector<string> pos_peptide(vector<int> labels, vector<string> peptides) {
    vector<string> pos_pep;
    for (int i = 0; i < labels.size(); i++) {
        if (labels[i] == 1) {
            pos_pep.push_back(peptides[i]);
        }
    }
    return pos_pep;
}

/*
 * Function: neg_peptide
 * ---------------------
 * Return all negative data according to the labels.
 */

vector<string> neg_peptide(vector<int> labels, vector<string> peptides) {
    vector<string> neg_pep;
    for (int i = 0; i < labels.size(); i++) {
        if (labels[i] == 0) {
            neg_pep.push_back(peptides[i]);
        }
    }
    return neg_pep;
}

/*
 * Function: averageAAC
 * --------------------
 * Returns average values of AAC of peptides.
 */

vector<double> averageAAC(vector<string> peptides) {
    unsigned long size = peptides.size();
    vector< vector<double> > allAAC = getAllAAC(peptides);
    vector<double> averageAAC(20,0);
    for (int i = 0; i < size; i++) {
        vector<double> aac = allAAC[i];
        for (int j = 0; j < 20; j++) {
            averageAAC[j] += aac[j];
        }
    }

    for (int z = 0; z < 20; z++) {
        averageAAC[z] = averageAAC[z] / size;
    }
    return averageAAC;
}

/*
 * Function: averageCKSAAP
 * -----------------------
 * Returns average values of 400 kinds of aa pairs component of peptides.
 */

vector<double> averageCKSAAP(vector<string> peptides) {
    unsigned long size = peptides.size();
    vector< vector<double> > averCKSAAP = getAllCKSAAP(peptides);
    vector<double> averageCKSAAP(400,0);
    for (int i = 0; i < size; i++) {
        vector<double> cksaap = averCKSAAP[i];
        for (int j = 0; j < 400; j++) {
            averageCKSAAP[j] += cksaap[j];
        }
    }

    for (int z = 0; z < 400; z++) {
        averageCKSAAP[z] = averageCKSAAP[z] / size;
    }
    return averageCKSAAP;
}

/*
 * Function: averageN5C5AAC
 * ------------------------
 * Returns average values of N5C5 AAC of peptides.
 */

vector<double> averageN5C5AAC(vector<string> peptides) {
    unsigned long size = peptides.size();
    vector<vector<double> > allN5C5AAC = getAllN5C5AAC(peptides);
    vector<double> averageN5C5AAC(21,0);
    for (int i = 0; i < size; i++) {
        vector<double> n5c5aac = allN5C5AAC[i];
        for (int j = 0; j < 21; j++) {
            averageN5C5AAC[j] += n5c5aac[j];
        }
    }

    for (int z = 0; z < 21; z++) {
        averageN5C5AAC[z] = averageN5C5AAC[z] / size;
    }
    return averageN5C5AAC;
}

/*
 * Function: cksaap_difference
 * ---------------------------
 * Calculates differences between cksaap of positive data and negative data.
 */

vector<double> cksaap_difference(vector<int> labels, vector<string> peptides) {
    vector<double> pos_cksaap = averageCKSAAP(pos_peptide(labels, peptides));
    vector<double> neg_cksaap = averageCKSAAP(neg_peptide(labels, peptides));
    vector<double> cksaap_diff;
    for (int i = 0; i < pos_cksaap.size(); i++) {
        double pos = pos_cksaap[i];
        double neg = neg_cksaap[i];
        cksaap_diff.push_back(pos - neg);
        //cout << "difference is " << pos - neg << endl;
    }
    return cksaap_diff;
}

/*
 * Function: top20_diff_indice
 * ---------------------------
 * Uses quick sort to sort absolute value of cksaap differences
 * and finds corresponding indice of top 20 cksaap differences.
 */

vector<int> top20_diff_indice(vector<int> labels, vector<string> peptides) {
    vector<double> cksaap_diff = cksaap_difference(labels, peptides);
    vector<double> abs_diff;
    vector<int> indice;
    for (int i = 0; i < cksaap_diff.size(); i++) {
        if (cksaap_diff[i] < 0) {
            abs_diff.push_back(-cksaap_diff[i]);
        } else {
            abs_diff.push_back(cksaap_diff[i]);
        }
        indice.push_back(i);
    }

    sort(abs_diff, indice);

    vector<int> top20_diff_indice;
    for (int i = 20; i > 0; i--) {
        top20_diff_indice.push_back(indice[indice.size() - i]);
        //cout << "indice is " << indice[indice.size() - i] << endl;
    }
    return top20_diff_indice;
}

/*
 * Function: top20_diff
 * --------------------
 * Returns values of cksaap with top 20 absolute value.
 */

vector<double> top20_diff(vector<int> labels, vector<string> peptides) {
    vector<double> diff = cksaap_difference(labels,peptides);
    vector<int> indice = top20_diff_indice(labels,peptides);
    vector<double> top20_diff;
    for (int i = 0; i < 20; i++) {
        top20_diff.push_back(diff[indice[i]]);
    }
    return top20_diff;
}

/*
 * Function: top20_diff_name
 * -------------------------
 * Returns names of aa pairs with top 20 absolute value of cksaap.
 */

vector<string> top20_diff_name(vector<int> labels, vector<string> peptides) {
    vector<int> indice = top20_diff_indice(labels,peptides);
    vector<string> top20_name;
    vector<string> all_name = aaPairs();
    for (int i = 0; i < 20; i++) {
        top20_name.push_back(all_name[indice[i]]);
    }
    return top20_name;
}
