#include "sigmoid.h"

using namespace std;

/*
 * Function: vectorMultiplication
 * Usage: returns the dot multiplication of two vectors
 */
double vectorMultiplication(DoubleArray array1, DoubleArray array2){

  /*First check the size of both arrays*/
  if (array1.size()!=array2.size()){
      //error("The size of two arrays does not match so the dot matrix multiplication can not work.");
      cout<<"The size of two arrays does not match so the dot matrix multiplication can not work.";
    }

  /*Calculate the dot matrix multiplication*/
  double result=0;
  for (int i=0; i<array1.size(); i++){
      result+=array1.get(i)*array2.get(i);
    }
  return result;
}

double vectorMultiplication2(vector<double> array1, vector<double> array2){

  /*First check the size of both arrays*/
  if (array1.size()!=array2.size()){
      //error("The size of two arrays does not match so the dot matrix multiplication can not work.");
      cout<<"The size of two arrays does not match so the dot matrix multiplication can not work.";
    }

  /*Calculate the dot matrix multiplication*/
  double result=0;
  for (int i=0; i<array1.size(); i++){
      result+=array1[i]*array2[i];
    }
  return result;
}

/*
 * Function: sigmoidFunction
 * Usage: returns the sigmoid function value of the superscript
 * ------------------------------------------------------------
 * The formula for the sigmoid function is "1/1+exp(-superscript)"
 */
double sigmoidFunction(double superscript){
  double gFunction;
  gFunction=1/1+exp(-superscript);
  return gFunction;
}
