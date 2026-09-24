#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    Edge() : u(-1), v(-1), w(-1) {}
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

class DSU {
    vector <int> parent, size;
    int n;
public :
    int cnt;
    DSU(int n) : n(n) {
        cnt = 0;
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
        cnt++;
    }
};


int ans = INT_MAX, n;
void recur(int idx, vector <Edge> &edges, DSU dsu1, DSU dsu2, int w1, int w2) {
    if (dsu1.cnt == n - 1 && dsu2.cnt == n - 1) {
        ans = min(ans, abs(w1 - w2));
        return;
    }

    bool can1 = dsu1.find(edges[idx].u) != dsu1.find(edges[idx].v);
    bool can2 = dsu2.find(edges[idx].u) != dsu2.find(edges[idx].v);
    if (!can1 && !can2) return;

    if (can1) {
        DSU new_dsu1 = dsu1;
        new_dsu1.union_set(edges[idx].u, edges[idx].v);
        recur(idx + 1, edges, new_dsu1, dsu2, w1 + edges[idx].w, w2);
    }

    if (can2) {
        DSU new_dsu2 = dsu2;
        new_dsu2.union_set(edges[idx].u, edges[idx].v);
        recur(idx + 1, edges, dsu1, new_dsu2, w1, w2 + edges[idx].w);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int m;
    cin >> n >> m;
    vector <Edge> edges(m);
    for (auto &x : edges) cin >> x.u >> x.v >> x.w;

    if (m != 2 * n - 2) {
        cout << "Cannot build double spanning tree\n";
        return 0;
    }
    else {
        DSU dsu1(n), dsu2(n);
        recur(0, edges, dsu1, dsu2, 0, 0);
        cout << (ans == INT_MAX ? -1 : ans) << "\n";
    }
    return 0;
}

/*
Test-cases :
6 10
1 2 1
2 3 2
3 4 4
4 5 8
5 6 16
1 3 32
2 4 64
3 5 128
4 6 256
1 6 512
Expected : 31

7 12
1 2 3
2 3 7
3 4 12
4 5 20
5 6 31
6 7 45
1 3 58
2 4 73
3 5 91
4 6 113
5 7 139
1 7 167
Expected : 7

5 8
1 2 5
2 3 5
3 4 5
4 5 5
1 3 4
2 4 4
3 5 4
1 5 3
Expected : 1

5 8
1 2 8
2 3 7
3 4 6
4 5 5
1 3 4
2 4 4
3 5 4
1 5 2
Expected : 0
*/

