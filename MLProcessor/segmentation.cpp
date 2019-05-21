#include "segmentation.h"

/*
 * Function: transform
 * Usage: tranform a vector<double> into DoubleArray
 */
DoubleArray transform(vector<double> rawDataSet){

  DoubleArray tempvectorOfArray(100);

  for (int i=0; i<rawDataSet.size(); i++)
    {
      tempvectorOfArray.put(i,rawDataSet[i]);
    }

  return tempvectorOfArray;
}

/*
 * Function: transformDataset
 * Usage: tranform a vector<vector<double>> into a dataframe
 * ---------------------------------------------------------
 * each row represents an observation (a DoubleArray)
 *
 */
vector<DoubleArray> transformDataset(vector<vector<double>> dataframe){

  int totalSize=dataframe.size();

  vector<DoubleArray> dataframeTransformed;

  //DoubleArray tempArray(100);

  for (int i=0; i<totalSize; i++){

      DoubleArray* tempArray=new DoubleArray(100);

      *tempArray=transform(dataframe[i]);

      dataframeTransformed.push_back(*tempArray);

    }

  return dataframeTransformed;
}

