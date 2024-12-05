// GROUP:   5
// ID:      20225052
// Assign:  01
// Assign:  ArrayHeap
// UVA:     10954
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
		sz= 12;
		arr = new Value[sz];
	};
	void Destroy() {
		delete[] arr;
	};
	void AddLast(Value v)
	{
		if(n == sz) {
			sz *= 2;
			Value* NewArr = new Value[sz];
			for (int i = 0; i<n; i++) {
				NewArr[i] = arr[i];
			}
			delete[] arr;
			arr= NewArr;
			arr[n] = v;
			n++;
		} else {
			arr[n] = v;
			n++;
		}
	}
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
	}
	Value& operator[](int i) {
		return arr[i];
	};
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Elem>
struct Heap
{
	Array<Elem> a;
	bool (*IsBefore)(Elem&, Elem&);

	void Initialize(bool (*_IsBefore)(Elem&, Elem&)) {
		a.Initialize();
		IsBefore = _IsBefore;
	};
	void Destroy() {
		a.Destroy();
	};
	int LChild(int iP) {
			return (2*iP)+1;
	};
	int RChild(int iP) {
			return (2*iP)+2;
	};
	int Parent(int iC) {
		return (iC-1)/2;
	};
	void MoveUp(int indC) {
		while(indC>0 && IsBefore(a[indC], a[(indC-1)/2])) {
			int indP = Parent(indC);
			Elem temp = a[indC];
			a[indC] = a[indP];
			a[indP] = temp;
			indC = indP;
		}
	};
	void MoveDown(int indP) {
		while (true) {
			int indCL = LChild(indP);
			int indCR = RChild(indP);
			int indC = indP;

			if (indCL < a.n && IsBefore(a[indCL], a[indC])) {
				indC = indCL;
			}
			if (indCR < a.n && IsBefore(a[indCR], a[indC])) {
				indC = indCR;
			}
			if (indC == indP) break;

			swap(a[indP], a[indC]);
			indP = indC;
		}
	};
	void Add(Elem e){
		a.AddLast(e);
		MoveUp(a.n-1);
	};
	Elem GetFirst() {
		return a[0];
	};
	Elem RetrieveFirst() {
		Elem First = a[0];
		a[0] = a[a.n - 1];
		a.RemoveLast();
		MoveDown(0);
		return First;
	};
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBeforeInt(int& a, int& b)
{
	return a<b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	int N=1;
	Array<Heap<int>> Hs;
	Hs.Initialize();
	 do {
		cout<<"Enter the number of integers: \n";
		cin>>N;
	 	if(N==0) break;
		Heap<int> H;
		H.Initialize(IsBeforeInt);
		for(int i=0; i<N; i++) {
			cout<<"Enter the integers: \n";
			int x;
			cin>>x;
			H.Add(x);
		}
		Hs.AddLast(H);
	}while(N>0);

	for(int i=0; i<Hs.n; i++) {
		Heap<int> heap = Hs[i];
		int x = heap.RetrieveFirst(); // 1
		int y = heap.RetrieveFirst(); // 2
		int cost = x+y;
		int sum = x+y;
		while(heap.a.n>0) {
			sum+= heap.RetrieveFirst(); // 3
			cost += sum;
		}
		cout<<"The total cost is: "<<cost<<endl;
		//cout<<cost<<endl;
	}
	return 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
