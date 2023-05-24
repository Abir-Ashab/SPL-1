#include <bits/stdc++.h>
#include "random_forest.h"
#include "kmeans_algo.h"
#include "knn_algo.h"
#include "logistic_Regression.h"
#include <windows.h>
#include <direct.h>

using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    setcolor1(6);
    printf("\tkmeans ");
    setcolor1(7);
    printf("for k-means algorithm\n") ;
    setcolor1(6);
    printf("\tknn ");
    setcolor1(7);
    printf("for KNN algorithm\n") ;
    setcolor1(6);
    printf("\tlogistic ");
    setcolor1(7);
    printf("for logistic regression algorithm\n") ;
    setcolor1(6);
    printf("\trandom ");
    setcolor1(7);
    printf("for random forest algorithm\n") ;
    setcolor1(6);
    printf("\tdecision ");
    setcolor1(7);
    printf("for decision tree algorithm\n") ;
    //setcolor3(11);
    setcolor1(9);
    printf("\ttype the name : ");
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
