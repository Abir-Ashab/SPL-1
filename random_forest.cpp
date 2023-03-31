#include "decision_tree.h"
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
random_device rd;
mt19937 gen(rd());


//random values generate kore
int random(int low, int high)
{
    uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

int main()
{
    // cout << "Number of files: ";
    // int k, i, index = 0;
    // cin >> k;
    ll k[20];
    int yes = 0, no = 0;
    for (int i = 0; i < 10; ++i)
    {
        k[i] = i;
    }
    for (int i = 0; i < 1; i++)
    {

        if (DecisionTree(k[i]))
        {
            yes++;
        }

        else
        {
            no++;
        }
    }
    int decisions[100], categories[100];
    for (int i = 0; i < 100; i++)
    {
        categories[i] = 0;
    }

    //final decision
    if (yes >= no)
    {
        cout << "YES, I will play tennis\n";
    }
    else
    {
        cout << "NO, I wont play tennnis\n";
    }
}