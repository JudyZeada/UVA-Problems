// GROUP:   NCS3
// ID:      20225052
// Assign:  03
// Assign:  Graphs
// UVA:     924
// Name:    Judy Waleed

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
    int  n, sz;
    Value* arr;

    void Initialize() {
        n= 0;
        sz= 1;
        arr= new Value[sz];
    };
    void Destroy () {
        delete[] arr;
    };
    void AddLast(Value v) {
        if(n == sz) {
            sz*= 2;
            Value* new_arr= new Value[sz];
            for(int i= 0; i< n; i++) {
                new_arr[i]= arr[i];
            }
            delete[] arr;
            arr= new_arr;
        }
        arr[n]= v;
        n++;

    };
    void RemoveLast() {
        n--;
        if(n<=sz/4) {
            sz /= 2;
            Value* NewArr = new Value[sz];
            for (int i = 0; i<n; i++) {
                NewArr[i] = arr[i];
            }
            delete[] arr;
            arr= NewArr;
        }
    };
    Value& operator[](int i) {
        return arr[i];
    };
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Value>
struct Node
{   Value name;
    Array<int> adj;
    void Initialize(Value _name) {
        name= _name;
        adj.Initialize();
    };
    void Destroy() {
        adj.Destroy();
    };
};

struct Graph
{
    int n;
    Node<int>* nodes;

    void Initialize(int _n) {
        n= _n;
        nodes= new Node<int>[n];
        for (int i=0; i<n;i++) {
            nodes[i].Initialize(i);
        }
    };
    void Destroy() {
        for (int i = 0; i < n; ++i) {
            nodes[i].Destroy();
        }
        delete[] nodes;
    };
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Type>
struct Queue {
    int f, n, sz;
    Type* elems;

    void Initialize(int size) {
        f = 0;
        n = 0;
        sz = size;
        elems = new Type[sz];
    }

    void Destroy() {
        delete[] elems;
    }

    void Add(Type t) {
        if (n == sz) {
            sz *= 2;
            Type* new_elems = new Type[sz];
            for (int i = 0; i < n; i++) {
                new_elems[i] = elems[(f + i) % sz];
            }
            delete[] elems;
            elems = new_elems;
            f = 0;
        }
        elems[(f + n) % sz] = t;
        n++;
    }

    Type Pop() {
        Type tmp = elems[f];
        f = (f + 1) % sz;
        n--;
        return tmp;
    }

    int Num() {
        return n;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BOOM(Graph& G, int source) {
    if (G.nodes[source].adj.n == 0) {
        cout << "0\n";
        return;
    }

    bool *visited = new bool[G.n];
    for (int i = 0; i < G.n; i++) {
        visited[i] = false;
    }

    visited[source] = true;
    Queue<int> Qcurrent, Qnext;
    Qcurrent.Initialize(G.n);
    Qnext.Initialize(G.n);
    Qcurrent.Add(source);
    int day = 1;
    int maxBoom = 0;
    int maxDay = 0;

    while (true) {
        int Boom = 0;
        while (Qcurrent.Num() > 0) {
            int u = Qcurrent.Pop();
            for (int i = 0; i < G.nodes[u].adj.n; i++) {
                int v = G.nodes[u].adj[i];
                if (!visited[v]) {
                    visited[v] = true;
                    Qnext.Add(v);
                    Boom++;
                }
            }
        }
        if (Boom > maxBoom) {
            maxBoom = Boom;
            maxDay = day;
        }
        if (Qnext.Num() > 0) {
            day++;
            swap(Qcurrent, Qnext);
            Qnext.Initialize(G.n);
        } else {
            break;
        }
    }
    cout << maxBoom << " " << maxDay << endl;
    delete[] visited;
    Qcurrent.Destroy();
    Qnext.Destroy();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    cout <<"Enter the number of employees: \n";
    int num;
    cin >> num;
    Graph G;
    G.Initialize(num);
    for (int i=0; i<num; i++) {
        cout << "Enter the number of friends that employee " << i << " haves: \n";
        int num_friends;
        cin >> num_friends;
        for (int j=0; j<num_friends; j++) {
            int friend_num;
            cin >> friend_num;
            G.nodes[i].adj.AddLast(friend_num);
        }
    }
    cout <<"Enter number of test cases; \n";
    int test_cases;
    cin >> test_cases;
    for (int i=0; i<test_cases; i++) {
        int source;
        cin >> source;
        BOOM(G, source);
    }

    G.Destroy();

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
