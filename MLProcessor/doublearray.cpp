#include "doublearray.h"

using namespace std;

/*
 * Function: constructor
 * Usage: initializes an empty array
 */
DoubleArray::DoubleArray(const int inputInitialCapacity){
  capacity=inputInitialCapacity-1;
  array=new double[capacity];
  for (count=0; count<=capacity; count++){
     array[count]=0;
    }
}

/*
 * Function: destructor
 * Usage: claer useless memory
 */

/*
DoubleArray::~DoubleArray(){
  delete[] array;
}
*/

/*
 * Function: size
 * Usage: return the size of the array
 */
int DoubleArray::size() const{
  return count;
}

/*
 * Function: get
 * Usage: return the value at a specific position of the array
 */
double DoubleArray::get(int k_get) const{
  if (k_get>capacity) {
      //error("get: Attempting to get an element outside the IntArray bounds");
      cout<<"get: Attempting to get an element outside the IntArray bounds";
    }
  return array[k_get];
}

/*
 * Function: size
 * Usage: put the value at a specific position of the array
 */
void DoubleArray::put(int k_put, double value){
  if (k_put>capacity) {
      //first expand the capacity to meet the requirement of k_put
      expandCapacity();
      put(k_put, value);
      count=k_put;
    } else {
      array[k_put]=value;
    }
}

/*
 * Function: max
 * Usage: initialize parameters and call for sortForMax
 */
double DoubleArray::max() const {
  int initialPosition=0;
  int initialValue=0;
  return sortForMax(initialValue,initialPosition);
}

/*
 * Function: sortForMax
 * Usage: return the max value of an array
 */
double DoubleArray::sortForMax(double maxValue, int pos) const {
  double currentValue=array[pos];
  if (pos<=count) {
      if (currentValue>maxValue){
          return sortForMax(currentValue, pos+1);
        } else {
          return sortForMax(maxValue, pos+1);
        }
    } else {
      return maxValue;
    }
}

/*
 * Function: expandCapacity
 * Usage: expands the capacity of an array
 */
void DoubleArray::expandCapacity() {
  capacity *= 2;
  double* oldArray = array;
  array = new double[capacity];
  for (int i = 0; i < count; i++) {
      array[i] = oldArray[i];
    }
  delete[] oldArray;
}

/*
 * Function: clear
 * Usage: clear an array
 */
void DoubleArray::clear(){
    delete[] array;
}
