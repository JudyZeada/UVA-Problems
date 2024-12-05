// GROUP:   NCS3
// ID:      20225052
// Assign:  02
// Assign:  DisjointSets
// UVA:     10608
// Name:    Judy Waleed

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DisjointSets
{
    int n;
    int* parent;
    int* num_nodes;

    void Initialize(int _n) {
        n=_n;
        parent = new int[n+1];
        for (int i =1; i<=n; i++) {
            parent[i] = i;
        }
        num_nodes= new int[n+1];
        for (int i =1; i<=n; i++) {
            num_nodes[i] = 1;
        }
    };
    void Destroy() {
        delete[] parent;
        delete[] num_nodes;
    };
    int Find(int i) {
        while(i != parent[i]) {
            i = parent[i];
        }
        return i;
    };
    bool Union(int i, int j) {
        int root_i= Find(i);
        int root_j= Find(j);
        if(root_i == root_j) {
            return false;
        }
        if (num_nodes[root_i] > num_nodes[root_j]) {
            parent[root_j] = root_i;
            num_nodes[root_i]+=num_nodes[root_j];
        } else if (num_nodes[root_i] < num_nodes[root_j]) {
            parent[root_i] = root_j;
            num_nodes[root_j]+=num_nodes[root_i];
        } else {
            parent[root_j] = root_i;
            num_nodes[root_i]+=num_nodes[root_j];
        }
        return true;

    };
    int FindNumSets() {
        int Max =0;
        for (int i =1; i<=n; i++) {
            if(num_nodes[i] > Max) {
                Max = num_nodes[i];
            }
        }
        return Max;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout<<"Enter number of test cases: \n";
    int t, N, M;
    cin>>t;
    DisjointSets D;
    for(int i=0; i<t; i++) {
        cout<<"Enter number of people and number of friendships: \n";
        cin>>N;
        cin>>M;
        D.Initialize(N);
        for (int j=0; j<M; j++) {
            cout << "Enter the two people: \n";
            int a, b;
            cin >> a;
            cin >> b;
            D.Union(a, b);
        }
        cout << "Max group of friends: " << D.FindNumSets() << endl;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
