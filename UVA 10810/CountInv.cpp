// GROUP:   NCS3
// ID:      20225052
// Assign:  04
// Assign:  CountInv
// UVA:     10810
// Name:    Judy Waleed

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

long long CountInvMerge(long long* a, int n) {
    long long swaps = 0;
    int mid = n/2; //mid=2
    long long* temp = new long long[n];
    int i = 0, j = mid, k = 0;
    while (i<mid && j<n) {
        if(a[i]<a[j]) {
            temp[k]=a[i];
            i++;
        }else {
            temp[k]=a[j];
            swaps+=mid -i;
            j++;

        }
        k++;
    }
    while (i<mid) {
        temp[k]=a[i];
        i++;
        k++;
    }
    while (j<n) {
        temp[k]=a[j];
        j++;
        k++;
    }
    for(int i=0; i<n; i++) {
        a[i]=temp[i];
    }
    delete[] temp;
    return swaps;
};
long long CountInv(long long* a, int n) {
    long long TotalSwaps = 0;
    if(n<=1) {
        return 0;
    }
    int mid = n/2;
    TotalSwaps+= CountInv(a, mid);
    TotalSwaps+= CountInv(a+mid, n-mid);
    TotalSwaps+= CountInvMerge(a, n);
    return TotalSwaps;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    while (true) {
        cout<<"Enter the number of elements: \n";
        int n;
        cin>>n;
        if(n==0) {
            break;
        }
        long long* a = new long long[n];
        cout<<"Enter the elements: \n";
        for(int i=0; i<n; i++) {
            cin>>a[i];
        }
        cout<<"The number of inversions: \n"<<CountInv(a, n)<<endl;
        delete[] a;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
