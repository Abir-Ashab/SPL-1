#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include<bits/stdc++.h>
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
		for (j = i + 1; j < n ; j++) 
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
    for(int i = 0; i < n; ++i) 
	{
		//cout << arr[i].distance << '\n';
	}
	int freq1 = 0;	 
	int freq2 = 0;	

	for (int i = 0; i < k; i++)
	{
		if (arr[i].val == 0)
			freq1++;

		else if (arr[i].val == 1)
			freq2++;
	}

	if(freq1 > freq2)
	return 0;
	else return 1;
}

int main() {
	ios_base::sync_with_stdio(0);
    cin.tie(0);
	cout << "Enter number of points : ";
	int n;
	cin >> n; 
	Point arr[n];

	for(int i = 0; i < n; ++i) 
	{
        double a, b;
        int s;
		cout << "\nEnter x" << i + 1 << " : ";
        cin >> a;

		cout << "\nEnter y" << i + 1 << " : ";
		cin >> b;
		
		cout << "\nEnter type" << i + 1 << " : ";
		cin >> s;
		
        arr[i].x = a;
        arr[i].y = b;
        arr[i].val = s;
    }

	Point p;
	cout << "\nEnter point which you want to check : \n";
	cin >> p.x >> p.y;

	int k = 3;
	int m = KNN(arr, n, k, p);
	string s1;
	if(m == 1) s1 = "dog";
	else s1 = "cat";
    
	cout << "When k = " << k  << " The value classified to unknown point is "
	     << s1 << '\n';
    
	k = 5;
	m = KNN(arr, n, k, p);

	if(m == 1) s1 = "dog";
	else s1 = "cat";

    cout << "When k = " << k  << " The value classified to unknown point is "
	     << s1 << '\n';
	return 0;
}