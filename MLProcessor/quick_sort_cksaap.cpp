/*
 * File: quick_sort_cksaap.cpp
 * ---------------------------
 * This file contains function to achieve qquick sort of abosolute
 * cksaap difference data while changing the order of correspondeing
 * indice in order to get ordered names of aa pairs.
 */

#include <iostream>
#include <vector>
#include "quick_sort_cksaap.h"
using namespace std;

/*
 * Implementation notes: sort
 * --------------------------
 * This function sorts the elements of the vector into
 * increasing numerical order using the Quicksort algorithm.
 * In this implementation, sort is a wrapper function that
 * calls quicksort to do all the work.
 */

void sort(vector<double> & vec, vector<int> & indice) {
    quicksort(vec, indice, 0, vec.size() - 1);
}

/*
 * Implementation notes: quicksort
 * -------------------------------
 * Sorts the elements in the vector between index positions
 * start and finish, inclusive.  The Quicksort algorithm begins
 * by "partitioning" the vector so that all elements smaller
 * than a designated pivot element appear to the left of a
 * boundary and all equal or larger values appear to the right.
 * Sorting the subsidiary vectors to the left and right of the
 * boundary ensures that the entire vector is sorted.
 */

void quicksort(vector<double> & vec, vector<int> & indice, int start, int finish) {
    if (start >= finish) return;
    int boundary = partition(vec, indice, start, finish);
    quicksort(vec, indice, start, boundary - 1);
    quicksort(vec, indice, boundary + 1, finish);
}

/*
 * Implementation notes: partition
 * -------------------------------
 * This function rearranges the elements of the vector so that the
 * small elements are grouped at the left end of the vector and the
 * large elements are grouped at the right end.  The distinction
 * between small and large is made by comparing each element to the
 * pivot value, which is initially taken from vec[start].  When the
 * partitioning is done, the function returns a boundary index such
 * that vec[i] < pivot for all i < boundary, vec[i] == pivot
 * for i == boundary, and vec[i] >= pivot for all i > boundary.
 */

int partition(vector<double> & vec, vector<int> & indice, int start, int finish) {
    double pivot = vec[start];
    int p_index = indice[start];
    int lh = start + 1;
    int rh = finish;
    while (true) {
        while (lh < rh && vec[rh] >= pivot) rh--;
        while (lh < rh && vec[lh] < pivot) lh++;
        if (lh == rh) break;
        double tmp = vec[lh];
        vec[lh] = vec[rh];
        vec[rh] = tmp;
        int index = indice[lh];
        indice[lh] = indice[rh];
        indice[rh] = index;
    }
    if (vec[lh] >= pivot) return start;
    vec[start] = vec[lh];
    vec[lh] = pivot;
    indice[start] = indice[lh];
    indice[lh] = p_index;
    return lh;
}
