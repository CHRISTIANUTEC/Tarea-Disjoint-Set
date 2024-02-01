#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
Integrantes:
-Christian Frisancho
-Isaac Simeón
*/

class DisjointSet
{
private:
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSet(int n) : parent(n), rank(n, 0) {}
    virtual ~DisjointSet() {}

    void MakeSet(int x)
    {
        parent[x] = x;
    }

    int Find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = Find(parent[x]);
        }
        return parent[x];
    }

    void Union(int x, int y)
    {
        int xRoot = Find(x);
        int yRoot = Find(y);
        if (xRoot == yRoot)
        {
            return;
        }
        if (rank[xRoot] < rank[yRoot])
            parent[xRoot] = yRoot;
        else if (rank[xRoot] > rank[yRoot])
            parent[yRoot] = xRoot;
        else
        {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }
    }

    bool isConnected(int x, int y)
    {
        return Find(x) == Find(y);
    }
};

template <typename T>
class DisjoinSetTree: public DisjointSet
{
private:
    T* data;
    int n;
    unordered_map<T, int> map;
public:
    DisjoinSetTree(){
        this->data = nullptr;
        this->n = 0;
    }

    DisjoinSetTree(int n1, T *data, int n) : DisjointSet(n1) {
        this->data = data;
        this->n = n;
    }
    virtual ~DisjoinSetTree(){}
    void MakeSet(T x) {
        if (map.find(x) == map.end()) {
            map[x] = x;
        }
    }
    int FindTree(T x){
        if(map[x] != x){
            map[x] = FindTree(map[x]);
        }
        return map[x];
    }
    void UnionTree(T x, T y){
        int xRoot = FindTree(x);
        int yRoot = FindTree(y);
        if(xRoot == yRoot){
            return;
        }
        map[yRoot] = xRoot;
    }
    bool isConnected(T x, T y){
        return FindTree(x) == FindTree(y);
    }
};

template <typename T>
class DisjointSetArray: public DisjointSet
{
private:
    T* data;
    int n;
    unordered_map<T, int> map;
public:
    DisjointSetArray(){
        this->data = nullptr;
        this->n = 0;
    }
    DisjointSetArray(T* data, int n): DisjointSet(n){
        this->data = data;
        this->n = n;
    }
    virtual ~DisjointSetArray(){}
    void MakeSet(T x){
        if(map.find(x) == map.end()){
            map[x] = x;
        }
    }
    int FindArray(T x){
        if(map[x] != x){
            map[x] = FindArray(map[x]);
        }
        return map[x];
    }
    void UnionArray(T x, T y){
        int xRoot = FindArray(x);
        int yRoot = FindArray(y);
        if(xRoot == yRoot){
            return;
        }
        map[yRoot] = xRoot;
    }
    bool isConnected(T x, T y){
        return FindArray(x) == FindArray(y);
    }
};
int main()
{
    cout << "Estructura de dato: DisjoinSet" << endl;
    DisjointSet ds(5);
    ds.MakeSet(0);
    ds.MakeSet(1);
    ds.MakeSet(2);
    ds.MakeSet(3);
    ds.MakeSet(4);
    ds.Union(0, 1);
    ds.Union(1, 2);
    ds.Union(3, 4);
    //Verificando si estan conectados
    cout << ds.isConnected(0, 2) << endl; //1
    cout << ds.isConnected(3, 4) << endl; //1
    cout << ds.isConnected(0, 4) << endl; //0

    cout<<"Nueva estructura de dato: DisjoinSetArray"<<endl;

    int data[5] = {0, 1, 2, 3, 4};
    int *ptr = data;
    DisjoinSetTree<int> dst(0, ptr, 5);
    dst.MakeSet(0);
    dst.MakeSet(1);
    dst.MakeSet(2);
    dst.MakeSet(3);
    dst.MakeSet(4);
    dst.UnionTree(0, 2);
    dst.UnionTree(1, 3);
    dst.UnionTree(0, 4);

    cout << dst.isConnected(0, 2) << endl; //1
    cout << dst.isConnected(3, 4) << endl; //0
    cout << dst.isConnected(0, 4) << endl; //1

    cout<<"Nueva estructura de dato: DisjoinSetArray"<<endl;
    int data2[5] = {10,11,12,13,14};
    int *ptr2 = data2;
    DisjointSetArray<int> dsa(ptr2, 5);

    dsa.MakeSet(10);
    dsa.MakeSet(11);
    dsa.MakeSet(12);
    dsa.MakeSet(13);
    dsa.MakeSet(14);
    dsa.UnionArray(10, 11);
    dsa.UnionArray(11, 12);
    dsa.UnionArray(13, 14);

    cout << dsa.isConnected(10, 13) << endl; //0
    cout << dsa.isConnected(13, 14) << endl; //1
    cout << dsa.isConnected(11, 14) << endl; //0
    return 0;
}
