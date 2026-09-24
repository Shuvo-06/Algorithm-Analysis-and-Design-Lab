#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    Edge() {}
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

class DSU {
    vector <int> parent, size;
    int n;
public :
    DSU(int n) : n(n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        return x == parent[x] ? x : parent[x] = find(parent[x]);
    }

    void union_set(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector <Edge> edges(m), taken;
    for (auto &x : edges) cin >> x.u >> x.v >> x.w;

    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.w < b.w;
    });

    DSU dsu(n);
    int mst_weight = 0;
    for (auto edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.union_set(edge.u, edge.v);
            mst_weight += edge.w;
            taken.push_back(edge);
        }
    }
    cout << mst_weight << "\n";
    for (auto [u, v, w] : taken) cout << u << " - " << v << " -> " << w << endl;
    return 0;
}

/*
6 9
1 2 4
1 3 3
1 4 7
2 3 2
2 5 6
3 4 5
3 5 8
4 6 1
5 6 9
Expected : 17
*/
