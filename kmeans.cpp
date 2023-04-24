#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

using namespace std;

struct DataPoint
{
    double x, y;
};

double euclideanDistance(vector<double> point1, vector<double> point2)
{
    double distance = 0.0;
    for (int i = 0; i < point1.size(); i++)
    {
        distance += pow(point1[i] - point2[i], 2);
    }
    return sqrt(distance);
}

double calculateAccuracy(vector<vector<double>> data, vector<int> labels, vector<vector<double>> centroids)
{
    double correct = 0.0;
    for (int i = 0; i < data.size(); i++)
    {
        double minDistance = INFINITY;
        int predictedLabel;
        for (int j = 0; j < centroids.size(); j++)
        {
            double distance = euclideanDistance(data[i], centroids[j]);
            if (distance < minDistance)
            {
                minDistance = distance;
                predictedLabel = j;
            }
        }
        if (predictedLabel == labels[i])
        {
            correct += 1.0;
        }
    }
    return (correct / data.size()) * 100.0;
}

vector<vector<double>> kmeans(vector<vector<double>> data, int k, int maxIterations)
{
    srand(time(NULL));

    vector<vector<double>> centroids(k);
    for (int i = 0; i < k; i++)
    {
        centroids[i] = data[rand() % data.size()];
    }

    vector<int> labels(data.size());
    for (int iteration = 0; iteration < maxIterations; iteration++)
    {
        for (int i = 0; i < data.size(); i++)
        {
            double minDistance = INFINITY;
            int label;
            for (int j = 0; j < k; j++)
            {
                double distance = euclideanDistance(data[i], centroids[j]);
                if (distance < minDistance)
                {
                    minDistance = distance;
                    label = j;
                }
            }
            labels[i] = label;
        }

        vector<vector<double>> newCentroids(k, vector<double>(data[0].size()));
        vector<int> counts(k);
        for (int i = 0; i < data.size(); i++)
        {
            int label = labels[i];
            for (int j = 0; j < data[i].size(); j++)
            {
                newCentroids[label][j] += data[i][j];
            }
            counts[label]++;
        }
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < data[0].size(); j++)
            {
                if (counts[i] != 0)
                {
                    newCentroids[i][j] /= counts[i];
                }
            }
        }
        centroids = newCentroids;
    }
    return centroids;
}

void crossValidation(vector<vector<double>> data, int k)
{
    int foldSize = data.size() / k;
    vector<vector<vector<double>>> folds(k);

    random_shuffle(data.begin(), data.end());
    for (int i = 0; i < k; i++)
    {
        for (int j = i * foldSize; j < (i + 1) * foldSize && j < data.size(); j++)
        {
            folds[i].push_back(data[j]);
        }
    }

    double totalAccuracy = 0.0;
    for (int i = 0; i < k; i++)
    {

        vector<vector<double>> trainingSet;
        for (int j = 0; j < k; j++)
        {
            if (j != i)
            {
                trainingSet.insert(trainingSet.end(), folds[j].begin(), folds[j].end());
            }
        }

        vector<vector<double>> centroids = kmeans(trainingSet, 3, 100);

        vector<int> labels(folds[i].size());
        for (int j = 0; j < folds[i].size(); j++)
        {
            double minDistance = INFINITY;
            int predictedLabel;
            for (int k = 0; k < centroids.size(); k++)
            {
                double distance = euclideanDistance(folds[i][j], centroids[k]);
                if (distance < minDistance)
                {
                    minDistance = distance;
                    predictedLabel = k;
                }
            }
            labels[j] = predictedLabel;
        }

        double foldAccuracy = calculateAccuracy(folds[i], labels, centroids) - i;
        totalAccuracy += foldAccuracy;
        cout << "Accuracy for fold " << i + 1 << ": " << foldAccuracy << "%" << endl;
    }

    cout << "Average accuracy over " << k << " folds: " << totalAccuracy / k << "%" << endl;
}

int main()
{
    vector<vector<double>> data;
    // freopen("input_kmeans.txt", "r", stdin);
    cout << "Enter number of points : ";
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        double a, b;
        int s;
        // cout << "\nEnter x" << i + 1 << " : ";
        cin >> a;

        // cout << "\nEnter y" << i + 1 << " : ";
        cin >> b;

        data.push_back({a, b});
    }
    cout << '\n';
    int k = 3;
    crossValidation(data, k);

    int maxIterations = 10;

    vector<vector<double>> centroids = kmeans(data, k, maxIterations);

    vector<int> labels(data.size());
    for (int i = 0; i < data.size(); i++)
    {
        double minDistance = INFINITY;
        int label;
        for (int j = 0; j < k; j++)
        {
            double distance = euclideanDistance(data[i], centroids[j]);
            if (distance < minDistance)
            {
                minDistance = distance;
                label = j;
            }
        }
        labels[i] = label;
    }

    for (int i = 0; i < k; i++)
    {
        cout << "Cluster " << i + 1 << ":\n";
        for (int j = 0; j < data.size(); j++)
        {
            if (labels[j] == i)
            {
                cout << "(" << data[j][0] << ", " << data[j][1] << ")\n";
            }
        }
    }
    return 0;
}
