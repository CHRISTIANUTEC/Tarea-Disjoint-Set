#include <iostream>
#include <vector>
using namespace std;

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
class DisjointSetTree : public DisjointSet
{
private:
    vector<T> data;

public:
    DisjointSetTree(T *data, int n) : DisjointSet(n), data(data, data + n)
    {
    }

    virtual ~DisjointSetTree()
    {
    }
    void MakeSet_tree(int i, T value)
    {
        data[i] = value;
    }

    int FindTree(T x)
    {
        int index = &x - &data[0];
        return Find(index);
    }

    void UnionTree(T x, T y)
    {
        int indexX = &x - &data[0];
        int indexY = &y - &data[0];
        Union(indexX, indexY);
    }
};

template <typename T>
class DisjointSetArray : public DisjointSet
{
private:
    T *data;
    int n;

public:
    DisjointSetArray(T *data, int n) : DisjointSet(n), data(data), n(n)
    {
    }

    virtual ~DisjointSetArray()
    {
    }

    int FindArray(T x)
    {
        int index = &x - data;
        return Find(index);
    }

    void UnionArray(T x, T y)
    {
        int indexX = &x - data;
        int indexY = &y - data;
        Union(indexX, indexY);
    }
};
