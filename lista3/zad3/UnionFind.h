//
// Created by konra on 27.04.2019.
//

#ifndef ZAD1M_UNIONFIND_H
#define ZAD1M_UNIONFIND_H


class UnionFind {
    int *id, number, *setSize;
public:
// Create an empty union find data structure with N isolated sets.
    explicit UnionFind(int N) {
        number = N; id = new int[N]; setSize = new int[N];
        for (int i = 0; i<N; i++)
            id[i] = i, setSize[i] = 1; }


    ~UnionFind() { delete[] id; delete[] setSize; }

// Return the id of component corresponding to object p.
    int find(int p) {
        int root = p;
        while (root != id[root])
            root = id[root];
        while (p != root) {
            int newp = id[p];
            id[p] = root; p = newp;
        }
        return root;
    }
// Replace sets containing x and y with their union.
    void merge(int x, int y) {
        int i = find(x);
        int j = find(y);
        if (i == j)
            return;
        // make smaller root point to larger one
        if (setSize[i] < setSize[j]) {
            id[i] = j;
            setSize[j] += setSize[i];
        }
        else {
            id[j] = i;
            setSize[i] += setSize[j];
        }
        number--;
    }
// Are objects x and y in the same set?
    bool connected(int x, int y) { return find(x) == find(y); }
// Return the number of disjoint sets.
    int getNumber() { return number; }
};


#endif //ZAD1M_UNIONFIND_H
