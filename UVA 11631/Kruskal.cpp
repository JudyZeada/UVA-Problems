// GROUP:   NCS3
// ID:      20225052
// Assign:  05
// Assign:  Kruskal
// UVA:     11631
// Name:    Judy Waleed

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DisjointSets {
    int n;
    int *parent;
    int *num_nodes;

    void Initialize(int _n) {
        n = _n;
        parent = new int[n];
        num_nodes = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            num_nodes[i] = 1;
        }
    };

    void Destroy() {
        delete[] parent;
        delete[] num_nodes;
    };

    int Find(int i) {
        while (i != parent[i]) {
            i = parent[i];
        }
        return i;
    };

    bool Union(int i, int j) {
        int root_i = Find(i);
        int root_j = Find(j);
        if (root_i == root_j) {
            return false;
        }
        if (num_nodes[root_i] >= num_nodes[root_j]) {
            parent[root_j] = root_i;
            num_nodes[root_i] += num_nodes[root_j];
        } else {
            parent[root_i] = root_j;
            num_nodes[root_j] += num_nodes[root_i];
        }
        return true;
    };
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type *a, int n, bool (*IsBefore)(Type &a, Type &b)) {
    Type *temp = new Type[n];
    int mid = n / 2;
    int i = 0;
    int j = mid;
    int k = 0;
    while (i < mid && j < n) {
        if (IsBefore(a[i], a[j])) {
            temp[k] = a[i];
            i++;
        } else {
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
void MergeSort(Type *a, int n, bool (*IsBefore)(Type &a, Type &b)) {
    if (n <= 1) {
        return;
    }
    int mid = n / 2;
    MergeSort(a, mid, IsBefore);
    MergeSort(a + mid, n - mid, IsBefore);
    Merge(a, n, IsBefore);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge {
    int u, v;
    int w;

    void Initialize(int _u, int _v, int _w) {
        u = _u;
        v = _v;
        w = _w;
    };
};

bool IsBeforeEdge(Edge &a, Edge &b) {
    return a.w < b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int N= 1,M = 1;
    int TotalCost=0;
    while (N != 0 && M != 0) {
        DisjointSets D;
        cout<<"Enter number of junctions and number of roads: \n";
        cin>>N;
        cin>>M;
        if (N == 0 && M == 0) {
            break;
        }
        D.Initialize(N);
        Edge* Roads = new Edge[M];
        int x,y,z;
        for(int i= 0; i < M; i++) {
            cout<<"Enter the junctions and the length of the road: \n";
            cin>>x;
            cin>>y;
            cin>>z;
            Roads[i].Initialize(x,y,z);
            TotalCost+=z;
        }
        MergeSort(Roads, M, IsBeforeEdge);
        int SavedCost= 0, MinCost=0;
        for(int i = 0; i<M ; i++) {
            if (D.Union(Roads[i].u, Roads[i].v)) {
                MinCost+=Roads[i].w;
            }
        }
        SavedCost = TotalCost - MinCost;
        cout<<SavedCost<<endl;

        delete[] Roads;
        D.Destroy();
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
