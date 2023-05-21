#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <string>
#include <iostream>
#include <random>
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

vector<double> testingValues;
vector<vector<double>> input;

double weight[] = {0.2, 0.2, 0.2, 0.2};
double learningRate = 0.001;
ll epoch = 10;
double e = 2.71828;

double sigmoid(double z);
void updateWeight(double predicted, double expected, vector<double> inputs);
void calculateAccuracy();
void test();

double sigmoid(double z)
{
  double ret;
  double cal1 = (-1 * z);
  double cal2 = 1 + pow(e, cal1);
  ret = 1 / cal2; 
  return ret;
}

void updateWeight(double predictedValue, double testingValues, vector<double> inputValue)
{
  for (int i = 0; i < inputValue.size(); i++)
  {
    double gradientDescent;
    double k = (predictedValue - testingValues);
    gradientDescent = k * inputValue[i];
    double m = (learningRate * gradientDescent);
    
    weight[i] = weight[i] - m;
  }

  return;
}

void calculateAccuracy()
{

  ll totalCorrect = 0;
  ll totalCases = input.size();

  for (int i = 0; i < input.size(); i++)
  {
    double predictedValue, z = 0;
    for (int j = 0; j < input[0].size(); j++)
    {
      z += input[i][j] * weight[j];
    }

    predictedValue = sigmoid(z);

    if (predictedValue < 0.5)
    {
      predictedValue = 0;
    }
    else
    {
      predictedValue = 1;
    }

    if (predictedValue == testingValues[i])
    {
      totalCorrect++;
    }
  }

  printf("Accuracy is: %f percent\n",100*(totalCorrect *1.0) / (totalCases*1.0));

  return;
}

void test()
{
  double z = 0;
  printf("Enter the values[sepal length,sepal width,petal length,petal width] for predicting : \n");
  for (int i = 0; i < 4; i++)
  {
    double temp;
    cin >> temp;
    double cal =  weight[i] * temp;;
    z += cal;
  }

  double predictedValue = sigmoid(z);

  if (predictedValue < 0.5)
  {
    cout << "Not a Iris setosa flower\n" << '\n';
  }
  else
  {
    cout << "This is Iris setosa flower\n" << '\n';
  }

  return;
}

int logistic_Regression()
{
  testingValues.clear();
  input.clear();

  //system("cls");

  string line;
  ll i;
  ll j; 
  ifstream infile;
  infile.open("IrisFlower.csv");

  while (getline(infile, line))
  {
    //input nibe

    i = 0;
    while (line[i] != ',')
    {
      i++;
    }
    i++;

    int token; // je values gula nibe 
    vector<double> inputRow;

    double output;

    inputRow.clear();

    for (token = 0; token < 4; token++)
    {
      double value;
      string val = "";
      while (line[i] != ',')
      {
        val += line[i];
        i++; 
      }
      i++; 
      value = stod(val);
      inputRow.push_back(value);
    }

    i++; 

    string outputStr = "";

    outputStr = line[line.size() - 1];

    output = stod(outputStr);

    testingValues.push_back(output);

    input.push_back(inputRow);
  }
  //cout << "input shesh\n";
  // check values for proper input into vectors

  // for(j = 0; j < input.size(); j++) {
  //   for(i = 0; i < 4; i++) {
  //     cout<<input[j][i]<<" ";
  //   }
  //   cout<<'\n';
  // }

  while (epoch--)
  {
    calculateAccuracy();
    for (i = 0; i < input.size(); i++)
    {
      double predictedValue;
      double z = 0;
      for (j = 0; j < input[0].size(); j++)
      {
        z += weight[j] * input[i][j];
      }
      predictedValue = sigmoid(z);

      updateWeight(predictedValue, testingValues[i], input[i]);
    }
  }

  calculateAccuracy();

  test();

  return 0;
}