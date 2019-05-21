#ifndef DOUBLEARRAY_H
#define DOUBLEARRAY_H

//#include "error.h"
#include <iostream>

class DoubleArray {

public:
  /*
   * DoubleArray constructor and destructor
   * ------------------------------------
   * The constructor initializes an empty stack. The destructor
   * is responsible for freeing heap storage.
   */

  DoubleArray(const int inputInitialCapacity=100);
  //~DoubleArray();
  
  void clear();

  /*
   * Methods: size, get, put, size, max
   * ----------------------------------------
   * These methods work exactly as they do for the array class.
   */

  int size() const; //return the size of the DoubleArray

  double get(int k_get) const; //get the element at the kth position

  void put(int k_put, double value); //put the value at the kth position in the DoubleArray

  double max() const; //get the maximum value in the DoubleArray

private:

  /* Instance variables */

  double* array;         /* Dynamic array of doubles   */
  int capacity;          /* Allocated size of DoubleArray  */
  int count;             /* Current count of DoubleArray     */

  /* Private functions */

  double sortForMax(double maxValue, int pos) const;   /* Find out the maximum value by binary search*/

  void expandCapacity();      /*Expand the capacity of the DoubleArray*/

};

#endif // DOUBLEARRAY_H
