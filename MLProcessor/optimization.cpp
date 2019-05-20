#include "optimization.h"
#include "segmentation.h"
#include "sigmoid.h"

/*
 * Function: costFunctionInside
 * Usage: returns the inside of a cost function
 * --------------------------------------------
 * The formula for the cost function is:
 * J(theta)=(1/m)*sumAcrossAllobservations(costFunctionInside)
 * This function refers to just one observation, so we need to reapeat if fot all observations
 */
double costFunctionInside(DoubleArray parameter, DoubleArray variable, double y){

  //int m=obNum;    /*`m` stands for the number of observations*/
  double hypothesis=sigmoidFunction(vectorMultiplication(parameter,variable));
  double insideOfSum=y*log(hypothesis)+(1-y)*log(1-hypothesis);

  return insideOfSum;
}

double costFunctionInside2(vector<double> parameter, vector<double> variable, double y){

  //int m=obNum;    /*`m` stands for the number of observations*/
  double hypothesis=sigmoidFunction(vectorMultiplication2(parameter,variable));
  double insideOfSum=y*log(hypothesis)+(1-y)*log(1-hypothesis);

  return insideOfSum;
}

/*
 * Function: gradientCostFunctionInside
 * Usage: returns the gradient of a cost function
 * ----------------------------------------------
 * posJ indicate the jth variable
 * "gradient" means we take the forst order derivative of J(theta) and get another function
 * this "inside" is the inside of the gradient cost function
 */
double gradientCostFunctionInside(DoubleArray parameter, DoubleArray variable, double y, int posJ){

  double hypothesis=sigmoidFunction(vectorMultiplication(parameter,variable));
  double insideOfSum=(hypothesis-y)*variable.get(posJ);

  return insideOfSum;
}

double gradientCostFunctionInside2(vector<double> parameter, vector<double> variable, double y, int posJ){

  double hypothesis=sigmoidFunction(vectorMultiplication2(parameter,variable));
  double insideOfSum=(hypothesis-y)*variable[posJ];

  return insideOfSum;
}

/*
 * Function: runningAverageCostFunciotn
 * Usage: returns the cost function across all observations
 * ----------------------------------------------
 * `runningAverage` takes the sum across all observations and return the average
 * Notice that this function applies to cost funciont
 * `obNum` stands for the number of observations
 * segment the original dataset into `datasetVariable`(X's) and `datasetY`(Y's)
 */
double runningAverageCostFunciotn(vector<DoubleArray> datasetVariable, vector<double> datasetY,
                                  DoubleArray parameter){

  /*`obNum` stands for the number of observations*/
  int obNum=datasetY.size();
  double sumValue=0;

  for (int i=0; i<obNum; i++)
    {
      DoubleArray variable=datasetVariable[i];
      double y=datasetY[i];
      sumValue+=costFunctionInside(parameter, variable, y);
    }

  return (-1)*sumValue/obNum;
}


double runningAverageCostFunciotn2(vector<vector<double>> datasetVariable, vector<double> datasetY,
                                  vector<double> parameter){

  /*`obNum` stands for the number of observations*/
  int obNum=datasetY.size();
  double sumValue=0;

  for (int i=0; i<obNum; i++)
    {
      vector<double> variable=datasetVariable[i];
      double y=datasetY[i];
      sumValue+=costFunctionInside2(parameter, variable, y);
    }

  return (-1)*sumValue/obNum;
}


/*
 * Function: updateParameter
 * Usage: returns the cost function across all observations
 * ----------------------------------------------
 * The method updates all parameters "ONCE"! (only once).
 * It is important that here we should update all theta's simultaneously,
 * not one by one so we will not (still) use the pointer or reference.
 * `learningRate` is the alpha in ML.
 * The formula for parameter updating is:
 * theta(j)=theta(j)-alpha/m*sumAcrossAllObservatons(gradientCostFunctionInside)
 * `j` corresponds to `posJ` in `gradientCostFunctionInside`
 */
DoubleArray updateParameter(DoubleArray parameter, double learningRate,
                 vector<DoubleArray> datasetVariable, vector<double> datasetY){

  DoubleArray parameterUpdated(100);

  for (int j=0; j<parameter.size(); j++)
    {
      double sumValue=0;
      for (int i=0; i<datasetY.size(); i++)
        {
          DoubleArray observationsI=datasetVariable[i];
          double yOfobservationsI=datasetY[i];
          sumValue+=gradientCostFunctionInside(parameter, observationsI, yOfobservationsI, j);
        }
      double thetaJ=parameter.get(j)-learningRate*sumValue/parameter.size();
      parameterUpdated.put(j,thetaJ);
    }

  return parameterUpdated;
}

vector<double> updateParameter2(vector<double> parameter, double learningRate,
                 vector<vector<double>> datasetVariable, vector<double> datasetY){

  vector<double> parameterUpdated;

  for (int j=0; j<parameter.size(); j++)
    {
      double sumValue=0;
      for (int i=0; i<datasetY.size(); i++)
        {
          vector<double> observationsI=datasetVariable[i];

          double yOfobservationsI=datasetY[i];
          sumValue+=gradientCostFunctionInside2(parameter, observationsI, yOfobservationsI, j);
        }
      double thetaJ=parameter[j]-learningRate*sumValue/parameter.size();
      parameterUpdated.push_back(thetaJ);
    }

  return parameterUpdated;
}

/*
 * Function: fmin
 * Usage: use recursion strategy to optimize the parameters
 * until convergence; return the new paramter sets
 * ----------------------------------------------
 * reapeat until all parameters converge
 * it is possible that the convergene process goes too slowly: change alpha
 * it is possible that we cannot achieve convergene: change alpha convergence limit
 */
DoubleArray fmin(DoubleArray parameter, vector<DoubleArray> datasetVariable, vector<double> datasetY){

  double learningRate=0.01;
  DoubleArray parameterNew=updateParameter(parameter,learningRate,datasetVariable,datasetY);

  for (int i=0; i<parameter.size(); i++)
    {
      double x=abs(parameter.get(i)-parameterNew.get(i));
      //condition for repeat
      if (x>0.001) {
          parameterNew=fmin(parameterNew,datasetVariable,datasetY);
        }
      break;
    }

  //this is the parameter vector used to do the prediction after training
  return parameterNew;
}


vector<double> fmin2(vector<double> parameter, vector<vector<double>> datasetVariable, vector<double> datasetY){

  double learningRate=0.01;
  vector<double> parameterNew=updateParameter2(parameter,learningRate,datasetVariable,datasetY);

  for (int i=0; i<parameter.size(); i++)
    {
      double x=abs(parameter[i]-parameterNew[i]);
      //condition for repeat
      if (x>0.001) {
          parameterNew=fmin2(parameterNew,datasetVariable,datasetY);
        }
      break;
    }

  //this is the parameter vector used to do the prediction after training
  return parameterNew;
}
