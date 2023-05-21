#include <bits/stdc++.h>
#include "random_forest.h"
#include "kmeans_algo.h"
#include "knn_algo.h"
#include "logistic_Regression.h"

using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    printf("type the name without '[]' : \n");
    printf("\t[knn] for KNN algorithm\n");
    printf("\t[kmeans] for kmeans algorithm \n");
    printf("\t[logistic] for logistic regression algorithm \n");
    printf("\t[random] for random forest algorithm \n");
    printf("\t[decision] for decision tree algorithm \n");
    string s;
    cin >> s;
    if (s == "knn")
    {
        knn_algo();
        test_KNN();
    }
    else if (s == "kmeans")
    {
        kmeans_algo();
    }
    else if (s == "logistic")
    {
        logistic_Regression();
    }
    else if (s == "random")
    {
        random_forest();
        test_random();
    }
    else if (s == "decision")
    {
        DecisionTree();
        test_decision();
    }
}