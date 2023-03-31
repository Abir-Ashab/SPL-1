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

double euclideanDistance(DataPoint a, DataPoint b);
void kMeans(vector<DataPoint> data, int k);

struct DataPoint
{
    double x, y;
};

double euclideanDistance(DataPoint a, DataPoint b)
{
    double ret;

    double first = pow(a.x - b.x, 2);

    double second = pow(a.y - b.y, 2);

    ret = sqrt(first + second);

    return ret;
}

void kMeans(vector<DataPoint> data, int k)
{

    vector<DataPoint> centroids(k);

    for (int i = 0; i < k; i++)
    {
        centroids[i] = data[rand() % data.size()];
    }

    vector<vector<DataPoint>> clusters(k);

    while (true)
    {
        for (DataPoint point : data)
        {
            double minDistance = DBL_MAX;
            int nearestCentroid = 0;
            for (int i = 0; i < k; i++)
            {

                double distance = euclideanDistance(point, centroids[i]);

                if (distance < minDistance)
                {
                    minDistance = distance;
                    nearestCentroid = i;
                }
            }
            clusters[nearestCentroid].push_back(point);
        }

        bool converged = true;\

        for (int i = 0; i < k; i++)
        {

            DataPoint newCentroid = {0, 0};\

            for (DataPoint point : clusters[i])
            {

                newCentroid.x += point.x;
                newCentroid.y += point.y;
            }

            newCentroid.x /= clusters[i].size();
            newCentroid.y /= clusters[i].size();

            if (euclideanDistance(newCentroid, centroids[i]) > 0.0001)
            {
                converged = false;
                centroids[i] = newCentroid;
            }
        }
        if (converged)
        {
            break;
        }

        return;
    }

    for (int i = 0; i < k; i++)
    {
        int j = 1;

        cout << "Cluster ";
        cout << i + 1 << ":" << endl;

        for (DataPoint point : clusters[i])
        {
            cout << "(" << point.x << ", " << point.y << ")" << endl;
            if (j == clusters[i].size() / 2)
            {
                break;
            }
            else
            {
                j++;
            }
        }
    }
}

int main()
{
    vector<DataPoint> data;

    cout << "Enter number of points : ";
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        double a, b;
        int s;
        cout << "\nEnter x" << i + 1 << " : ";
        cin >> a;

        cout << "\nEnter y" << i + 1 << " : ";
        cin >> b;

        data.push_back({a, b});
    }
    cout << '\n';

    int k = 3;
    kMeans(data, k);
    return 0;
}
