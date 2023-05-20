#include <bits/stdc++.h>
#include "random_forest.h"
#include "kmeans_algo.h"
#include "knn_algo.h"
#include "logistic_Regression.h"

using namespace std;
typedef long long ll;

void k_folds_for_decision_tree(vvs info, int k);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    if (s == "knn")
    {
        knn_algo();
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
    }
    else if (s == "decision")
    {
        freopen("decision_random.txt", "r", stdin);
        long long n, m;
        cin >> n >> m;
        vvs info(n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                string s;
                cin >> s;
                info[i].push_back(s);
            }
        }
        map<string, string> mq, mq2;

        for (int j = 0; j < m - 1; j++)
        {
            map<string, bool> mp;
            for (int i = 1; i < n; i++)
            {
                if (!mp[info[i][j]])
                {
                    mp[info[i][j]] = 1;
                    attr_vals[info[0][j]].push_back(info[i][j]);
                }
            }
        }
        int k = 5;
        k_folds_for_decision_tree(info, k);
    }
    return 0;
}

void k_folds_for_decision_tree(vvs info, int k)
{
    int folds = k;
    int accuracy = 0;
    k++;
    while (k > 0)
    {
        k--;
        node *root = new node();
        vvs info2;

        func(root, info);
        map<string, string> mq;
        string expected = info[k][4];
        for (int j = 0; j < 4; j++)
        {
            // string s;
            // cin >> s;
            // cout << s << "  ";
            mq[info[0][j]] = info[k][j];
        }
        string actual;
        if (decision_function(root, mq))
        {
            actual = "Yes";
        }
        else
        {
            actual = "No";
            folds--;
        }
        if (actual == expected)
            accuracy++;
    }
    cout << "Average Accuracy is : " << (accuracy * 1.0 / folds) * 100 << "%" << '\n';
}