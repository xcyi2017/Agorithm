//
// Created by xcy on 2020/10/8.
//

#ifndef DAY12_UNIONFIND6_H
#define DAY12_UNIONFIND6_H

#include <cassert>
#include <iostream>

// 路径压缩 在find操作中对路径进行压缩
namespace UF6 {
    class UnionFind {
    private:
        int *parent;
        int *rank; // rank[i]表示以i为根的集合中层数
        int count;
    public:
        explicit UnionFind(int n);

        ~UnionFind();

        int find(int p);

        bool isConnected(int p, int q);

        void unionElements(int p, int q);

    };

    UnionFind::UnionFind(int n) : parent(new int[n]), rank(new int[n]), count(n) {
        for (int i = 0; i < count; i++) {
            parent[i] = i; // 初始状态两两元素互不连接
            rank[i] = 1; // 初始状态每个元素自身组成一个集合
        }
    }

    UnionFind::~UnionFind() {
        delete[] parent;
        delete[] rank;
    }

    int UnionFind::find(int p) {
        assert(p >= 0 && p < count);
        if (p != parent[p])
            parent[p] = find(parent[p]); // 形成最优的层数，两层
        return parent[p];
    }

    bool UnionFind::isConnected(int p, int q) {
        return find(p) == find(q);
    }

    void UnionFind::unionElements(int p, int q) {
        int pRoot = find(p);
        int qRoot = find(q);

        if (pRoot == qRoot)
            return;
        if (rank[pRoot] < rank[qRoot]) {
            parent[pRoot] = qRoot;
        } else if (rank[pRoot] > rank[qRoot]) {
            parent[qRoot] = pRoot;
        } else {
            parent[pRoot] = qRoot;
            rank[qRoot] += 1;
        }
    }
}

#endif //DAY12_UNIONFIND6_H
