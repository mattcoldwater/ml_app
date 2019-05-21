/*
 * File: quick_sort_cksaap.h
 * -------------------------
 * This file is transformed a little of the QuickSort.cpp in order
 * to change the order of indices of aa pairs at the same time.
 */

#ifndef QUICK_SORT_CKSAAP_H
#define QUICK_SORT_CKSAAP_H

#include <iostream>
#include <vector>
using namespace std;

/* Function prototypes */
void sort(vector<double> & vec, vector<int> & indice);
void quicksort(vector<double> & vec, vector<int> & indice, int start, int finish);
int partition(vector<double> & vec, vector<int> & indice, int start, int finish);

#endif // QUICK_SORT_CKSAAP_H
