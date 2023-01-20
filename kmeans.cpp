#include<bits/stdc++.h>
using namespace std;

struct DataPoint {
    double x, y;
};

double euclideanDistance(DataPoint a, DataPoint b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void kMeans(vector<DataPoint> data, int k) {

    vector<DataPoint> centroids(k);

    for (int i = 0; i < k; i++) {
        centroids[i] = data[rand() % data.size()];
    }
    
    vector<vector<DataPoint>> clusters(k);
    
    while (true) {
        for (DataPoint point : data) {
            double minDistance = DBL_MAX;
            int nearestCentroid = 0;
            for (int i = 0; i < k; i++) {

                double distance = euclideanDistance(point, centroids[i]);

                if (distance < minDistance) {
                    minDistance = distance;
                    nearestCentroid = i;
                }
            }
            clusters[nearestCentroid].push_back(point);
        }

        bool converged = true;
        for (int i = 0; i < k; i++) {
            DataPoint newCentroid = {0, 0};
            for (DataPoint point : clusters[i]) {

                newCentroid.x += point.x;
                newCentroid.y += point.y;
            }

            newCentroid.x /= clusters[i].size();
            newCentroid.y /= clusters[i].size();

            if (euclideanDistance(newCentroid, centroids[i]) > 0.0001) {
                converged = false;
                centroids[i] = newCentroid;
            }
        }
        if (converged) {
            break;
        }
    }

    for (int i = 0; i < k; i++) {
        cout << "Cluster " << i << ":" << endl;
        for (DataPoint point : clusters[i]) {
            cout << "(" << point.x << ", " << point.y << ")" << endl;
        }
    }
}

int main() {
    vector<DataPoint> data;
    
    cout << "Enter number of points : ";
    int n; cin >> n;
    
    for(int i = 0; i < n; ++i) {
        double a, b;
        int s;
		cout << "\nEnter x" << i + 1 << " : ";
        cin >> a;

		cout << "\nEnter y" << i + 1 << " : ";
		cin >> b;
		
        data.push_back({a,b});
    }
    int k = 3;
    kMeans(data, k);
    return 0;
}
