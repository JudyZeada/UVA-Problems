// GROUP:   NCS3
// ID:      20225052
// Assign:  06
// Assign:  Prim
// UVA:     534
// Name:    Judy Waleed

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits.h>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
    int  n, sz;
    Value* arr;

    void Initialize() {
        sz=12;
        n=0;
        arr=new Value[sz];
    };

    void Destroy() {
        delete[] arr;
    };

    void AddLast(Value v) {
        if(n==sz) {
            sz*=2;
            Value* newarr=new Value[sz];
            for(int i=0; i<n; i++) {
                newarr[i]=arr[i];
            }
            delete[] arr;
            arr=newarr;
        }
        arr[n]=v;
        n++;
    };

    void RemoveLast() {
        n--;
        if(n<=sz/4) {
            sz/=2;
            Value* newarr =new Value[sz];
            for(int i =0; i<n;i++) {
                newarr[i]=arr[i];
            }
            delete[] arr;
            arr=newarr;
        }
    };

    Value& operator[](int i) {
        return arr[i];
    };
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Find the square root of "v" in "n" iterations
double Sqrt(double v, int n=100) {
    double a =0, b=v;
    for(int i=0; i<n; i++) {
        double c=(a+b)/2;
        if(c*c>v) {
            b=c;
        } else {
            a=c;
        }
    }
    return a;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Edge
{
    int		v;  // id of the adjacent node
    double	w; // edge weight = distance between the two nodes

};

struct Node
{
    int x,y; // x and y coordinates of the node
    Array<Edge> adj;

    void Initialize(int _x, int _y) {
        x=_x;
        y=_y;
        adj.Initialize();
    };

    void Destroy() {
        adj.Destroy();
    };

};

struct Graph
{
    int n;
    Node* nodes;

    void Initialize(int _n) {
        n = _n;
        nodes = new Node[n];
    };

    void Destroy() {
        delete[] nodes;
    };

    double Distance(int i, int j) {
        return Sqrt((nodes[i].x-nodes[j].x)*(nodes[i].x-nodes[j].x)+(nodes[i].y-nodes[j].y)*(nodes[i].y-nodes[j].y));
    };

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
double Prim(Graph& g) {
    double Max = INT_MIN;
    Array<int> P;
    Array<double> D;
    bool* S = new bool[g.n];
    D.Initialize();
    P.Initialize();
    for(int i=0; i<g.n; i++) {
        S[i]=false;
        D.AddLast(INT_MAX);
        P.AddLast(-1);
    }
    S[0]=true;
    D[0]=0;
    P[0]=0;
    for (int i=0; i<g.n-1; i++) {
        Edge MinEdge;
        for(int j=0; j< g.nodes[i].adj.n; j++) {
            if(g.nodes[i].adj[j].w<D[g.nodes[i].adj[j].v] && !S[g.nodes[i].adj[j].v]) {
                D[g.nodes[i].adj[j].v]=g.nodes[i].adj[j].w;
                P[g.nodes[i].adj[j].v]=i;
            }
        }
        double Min=INT_MAX;
        for(int j=0; j<g.n; j++) {
            if(!S[j] && D[j]<Min) {
                Min=D[j];
                MinEdge.v=j;
                MinEdge.w=D[j];
            }
        }
        S[MinEdge.v]=true;
    }

    int current = g.n-1;
    while (current != 0) {
        if(D[current]>Max) {
            Max=D[current];
        }
        current=P[current];
    }

    return Max;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    int count =1;
    while (true) {
        cout<<"Enter the number of stones: \n";
        int n;
        cin>>n;
        if(n==0) {
            break;
        }
        Graph g;
        g.Initialize(n);
        cout<<"Enter the coordinates of the stones: \n";
        for(int i=0; i<n;i++) {
            int x,y;
            cin>>x;
            cin>>y;
            g.nodes[i].Initialize(x,y);
        }
        for (int i=0; i<n; i++) {
            for (int j=i+1; j<n; j++) {
                Edge e;
                e.v=j;
                e.w=g.Distance(i,j);
                g.nodes[i].adj.AddLast(e);
                e.v=i;
                g.nodes[j].adj.AddLast(e);
            }
        }


        cout<<"Scenario #"<<count<<endl;
        cout<<"Frog Distance = "<< Prim(g) <<endl;
        count++;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
