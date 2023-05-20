#include "decision_tree.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <string>
#include <iostream>
#include <random>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

random_device rd;
mt19937 gen(rd());

vector<ll> k1, k2;

void RandomGenerator(int N)
{
    k1.push_back(N);
    for (int i = 0; i < 4; i++)
    {
        k1.push_back(rand() % N);
    }
    // cout << "K1" << '\n';
    // for( auto val : k1 ) cout << val << ' ';
}

void RandomGenerator2(int N)
{
    k2.push_back(0);
    N /= 2;
    for (int i = 0; i < 4; i++)
    {
        k2.push_back(rand() % N);
    }
    // cout << "K2" << '\n';
    // for( auto val : k2 ) cout << val << ' ';
}
void k_folds_cross_validation(vvs DATA, int f)
{
    map<string, string> mq, mq2;
    int accuracy = 0, folds = f;
    f++;
    while (f > 0)
    {
        f--;
        // cout << f << ' ';
        string expected = DATA[f][4];
        // cout << expected << ' ';
        for (int j = 0; j < 4; j++)
        {
            mq[DATA[0][j]] = DATA[f][j];
        }
        string actual;
        for (int k = 0; k < 5; ++k)
        {
            vvs DATA2;
            for (int i = 0; i < k1[k]; i++)
            {
                for (int j = k2[k]; j < m; j++)
                {
                    DATA2.push_back(DATA[j]);
                    cout << DATA[i][j] << "       ";
                }
                cout << '\n';
            }
            // initial attr_vals;

            node *root = new node();
            func(root, DATA2);
            // int question;
            // cin >> question;

            // for (int i = 0; i < question; i++)
            // {
            // cout << "\n\nFor the following data : ";

            // cout << "\n\nMy decision is : ";

            if (decision_function(root, mq))
            {
                yes++;
            }
            else
            {
                no++;
            }
        }
        if (yes >= no)
        {
            actual = "Yes";
        }
        else
        {
            actual = "No";
        }
        if (actual == expected)
            accuracy++;
        cout << accuracy << ' ';
    }
    cout << "Accuracy is : " << (1.0 * accuracy / (folds * 1.0)) * 100 << "%" << '\n';
}
int random_forest()
{
    // cout << "Number of files: ";
    // int k, i, index = 0;
    // cin >> k;
    freopen("decision_random.txt", "r", stdin);
    ll n, m;
    cin >> n >> m;
    vvs DATA(n);

    RandomGenerator(n);
    RandomGenerator2(n / 2);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            string s;
            cin >> s;
            DATA[i].push_back(s);
        }
    }
    map<string, string> mq, mq2;
    // for (int j = 0; j < m - 1; j++)
    // {
    //     string s;
    //     cin >> s;
    //     mq[DATA[0][j]] = s;
    // }
    // kon class e unique attr koyta o ki..for example..outlook = {sunny,rain,overcast}
    for (int j = 0; j < m - 1; j++)
    {
        map<string, bool> mp;
        for (int i = 1; i < n; i++)
        {
            if (!mp[DATA[i][j]])
            {
                mp[DATA[i][j]] = 1;
                attr_vals[DATA[0][j]].push_back(DATA[i][j]);
                // cout << "DATA[0][j] = " << DATA[0][j] << "  DATA[i][j] = " << DATA[i][j] << '\n';
            }
        }
    }
    int f = 5;
    int accuracy = 0, folds = f;
    f++;
    while (f > 0)
    {
        f--;
        int yes = 0;
        int no = 0;
        for (int j = 0; j < 4; j++)
        {
            mq[DATA[0][j]] = DATA[f][j];
        }
        string expected = DATA[f][4];
        string actual;
        for (int k = 0; k < 5; ++k)
        {
            vvs DATA2;
            for (int i = 0; i < k1[k]; i++)
            {
                for (int j = k2[k]; j < m; j++)
                {
                    DATA2.push_back(DATA[j]);
                    cout << DATA[i][j] << "       ";
                }
                cout << '\n';
            }
            // initial attr_vals;

            node *root = new node();
            func(root, DATA2);
            // int question;
            // cin >> question;

            // for (int i = 0; i < question; i++)
            // {
            // cout << "\n\nFor the following data : ";

            for (int j = 0; j < m - 1; j++)
            {
                string s;
                s = mq[DATA2[0][j]];
                // cout << s << "  ";
                mq2[DATA2[0][j]] = s;
            }

            // cout << "\n\nMy decision is : ";

            if (decision_function(root, mq2))
            {
                yes++;
            }
            else
            {
                no++;
            }
        }
        cout << "YES = " << yes << "  NO = " << no << '\n';
        if (yes >= no)
        {
            actual = "Yes";
        }
        else
        {
            actual = "No";
        }
        if (actual == expected)
            accuracy++;
    }
    cout << "Accuracy is : " << (1.0 * accuracy / (folds * 1.0)) * 100 << "%" << '\n';
}