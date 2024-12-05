// GROUP:   NCS3
// ID:      20225052
// Assign:  08
// Assign:  ClosetsPair
// UVA:     10245
// Name:    Judy Waleed

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>     // please use the built-in sqrt() function
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)) {
    Type *temp = new Type[n];
    int mid = n / 2;
    int i = 0, j = mid, k = 0;
    while (i<mid && j < n) {
        if (IsBefore(a[i], a[j])) {
            temp[k] = a[i];
            i++;
        }else {
            temp[k] = a[j];
            j++;
        }
        k++;
    }

    while (i < mid) {
        temp[k] = a[i];
        i++;
        k++;
    }

    while (j < n) {
        temp[k] = a[j];
        j++;
        k++;
    }

    for (int i = 0; i < n; i++) {
        a[i] = temp[i];
    }

    delete[] temp;
};

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)) {
    if (n <= 1) {
        return;
    }
    int mid = n / 2;
    MergeSort(a, mid, IsBefore);
    MergeSort(a + mid, n - mid, IsBefore);
    Merge(a, n, IsBefore);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Point
{
    double x,y;
};

bool IsBeforeX(Point& a, Point& b) {
    return a.x < b.x;
};

bool IsBeforeY(Point& a, Point& b) {
    return a.y < b.y;
};

double dist(Point& a, Point& b) {
    double d = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    return d;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Sort the points p according to x before calling this function
double ClosestPair(Point* p, int n) {
    if (n == 1 ) {
        return INFINITY;
    }
    if (n ==2) {
        MergeSort(p, n, IsBeforeY);
        return dist(p[0], p[1]);
    }
    if (n==3) {
        double d1 = dist(p[0], p[1]);
        double d2 = dist(p[1], p[2]);
        double d3 = dist(p[0], p[2]);
        return min(d1, min(d2, d3));
    }

    int mid = n / 2;
    double d1 = ClosestPair(p, mid);
    double d2 = ClosestPair(p + mid, n - mid);
    double d = min(d1, d2);

    Point* strip = new Point[n];
    int j = 0;
    for(int i= 0; i < n; i++) {
        if(p[i].x >= p[mid].x - d && p[i].x <= p[mid].x + d) {
            strip[j] = p[i];
            j++;
        }
    }

    MergeSort(strip, j, IsBeforeY);

    for (int i = 0; i < j; i++) {
        for (int k = 1; k <= 7 && i + k < j; k++) {
            d = min(d, dist(strip[i], strip[i + k]));
        }
    }

    return d;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    while (true) {
        cout<<"Enter the number of points: ";
        int n;
        if (n == 0) {
            break;
        }
        cin>> n;
        Point* P = new Point[n];
        for (int i= 0; i<n; i++) {
            cout<<"Enter the x and y coordinates of point "<<i+1<<": ";
            cin>>P[i].x>>P[i].y;
        }

        MergeSort(P, n, IsBeforeX);
        if (ClosestPair(P,n)>10000) {
            cout<<"INFINITY"<<endl;
        }else {
            cout<<"The smallest distance between two points is: "<<ClosestPair(P, n)<<endl;
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
