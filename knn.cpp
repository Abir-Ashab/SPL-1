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

struct Point
{
    int val;
    double x, y;
    double distance;
};

void Sort(Point arr[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (arr[j].distance < arr[i].distance)
            {
                Point temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int KNN(Point arr[], int n, int k, Point p)
{

    for (int i = 0; i < n; i++)
    {
        double q1 = (arr[i].x - p.x) * (arr[i].x - p.x);
        double q2 = (arr[i].y - p.y) * (arr[i].y - p.y);

        arr[i].distance = sqrt((q1 + q2));
    }

    Sort(arr, n);
    int freq1 = 0;
    int freq2 = 0;

    for (int i = 0; i < k; i++)
    {
        if (arr[i].val == 0)
            freq1++;

        else if (arr[i].val == 1)
            freq2++;
    }

    if (freq1 > freq2)
        return 0;
    else
        return 1;
}

void k_fold_cross_validation(Point arr[], int n, int k)
{
    int fold_size = n / k;
    double accuracy = 0.0;

    for (int i = 0; i < k; i++)
    {
        int test_start = i * fold_size;
        int test_end = test_start + fold_size;

        vector<Point> train, test;

        for (int j = 0; j < n; j++)
        {
            if (j >= test_start && j < test_end)
            {
                test.push_back(arr[j]);
            }
            else
            {
                train.push_back(arr[j]);
            }
        }

        int correct_predictions = 0;

        for (int j = 0; j < test.size(); j++)
        {
            int predicted_class = KNN(&train[0], train.size(), 3, test[j]);

            if (predicted_class == test[j].val)
            {
                correct_predictions++;
            }
        }

        double fold_accuracy = (double)correct_predictions / (double)test.size();
        cout << "Accuracy for fold " << i + 1 << " is " << fold_accuracy << endl;

        accuracy += fold_accuracy;
    }

    accuracy /= k;
    cout << "Average accuracy over " << k << " folds is " << accuracy << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout << "Enter number of points : ";
    // int n;
    // cin >> n;
    int n = 50;
    Point arr[n];
    ifstream file("knn.csv");
    string line;
    int i = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        getline(ss, token, ',');
        arr[i].x = stod(token);

        getline(ss, token, ',');
        arr[i].y = stod(token);

        getline(ss, token, ',');
        arr[i].val = stoi(token);
        i++;
    }

    int k = 3;
    int num_folds = 10;
    int fold_size = n / num_folds;

    // Shuffle the data
    shuffle(arr, arr + n, default_random_engine(0));

    double accuracy_sum = 0.0;
    for (int fold = 0; fold < num_folds; fold++)
    {
        int correct = 0;
        int start_index = fold * fold_size;
        int end_index = (fold + 1) * fold_size;
        for (int i = start_index; i < end_index; i++)
        {
            Point p = arr[i];
            Point temp_arr[n-1];
            int index = 0;
            for (int j = 0; j < n; j++)
            {
                if (j == i)
                    continue;

                temp_arr[index] = arr[j];
                double q1 = (temp_arr[index].x - p.x) * (temp_arr[index].x - p.x);
                double q2 = (temp_arr[index].y - p.y) * (temp_arr[index].y - p.y);
                temp_arr[index].distance = sqrt((q1 + q2));
                index++;
            }
            Sort(temp_arr, n - 1);
            int freq1 = 0;
            int freq2 = 0;

            for (int j = 0; j < k; j++)
            {
                if (temp_arr[j].val == 0)
                    freq1++;
                else if (temp_arr[j].val == 1)
                    freq2++;
            }

            int predicted_label;
            if (freq1 > freq2)
                predicted_label = 0;
            else
                predicted_label = 1;

            if (predicted_label == p.val)
                correct++;
        }

        double accuracy = (double) correct / fold_size;
        cout << "Accuracy for fold " << fold+1 << ": " << accuracy << endl;
        accuracy_sum += accuracy;
    }

    double overall_accuracy = accuracy_sum / num_folds;
    cout << "Overall accuracy: " << overall_accuracy << endl;

    return 0;
}
