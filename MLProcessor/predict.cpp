#include "predict.h"


//输入一组变量得到的y_hat（单个observation)
int predict(vector<double> parameters, vector<double> variables){

  double sum=0;
  int y=0;

  for (int i=0; i<parameters.size(); i++)
    {
      sum+=parameters[i]*variables[i];
    }

  if (sum>0.5) { y=1; }

  return y;
}

int predict2(vector<double> parameters, vector<double> variables, double threshold){

  double sum=0;
  int y=0;

  for (int i=0; i<parameters.size(); i++)
    {
      sum+=parameters[i]*variables[i];
    }

  if (sum>threshold) { y=1; }

  return y;
}

//测试所有输入并计算预测准确的比例
double accuracy(vector<vector<double>> test_data_frame, vector<double> y, vector<double> parameters){

  double correction=0;

  for (int i=0; i<test_data_frame.size(); i++)
    {

      vector<double> current_ob=test_data_frame[i];
      //DoubleArray current_ob_transformed=transform(current_ob);
      int result=predict(parameters,current_ob);

      if (result==y[i]){
          correction++;
        }

    }

  double total=y.size();

  double accuracy=correction/total;

  return accuracy;
}
