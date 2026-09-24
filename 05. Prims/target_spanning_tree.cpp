#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

const int target = 54;

struct DSU {
    vector<int> parent, sz;

    DSU(int n) {
        parent.resize(n);
        sz.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

int n, m;
vector<Edge> edges;
vector<Edge> answer;
vector<Edge> current;

bool dfs(int idx, int edgeCount, int weight, DSU dsu) {
    if (edgeCount == n - 1) {
        if (weight == target) {
            answer = current;
            return true;
        }
        return false;
    }

    if (idx == m) return false;
    if (edgeCount + (m - idx) < n - 1) return false;
    if (weight > target) return false;


    Edge e = edges[idx];

    if (dsu.find(e.u) != dsu.find(e.v)) {
        DSU newDsu = dsu;
        newDsu.unite(e.u, e.v);
        current.push_back(e);
        if (dfs(idx + 1, edgeCount + 1, weight + e.w, newDsu)) return true;
        current.pop_back();
    }

    if (dfs(idx + 1, edgeCount, weight, dsu)) return true;
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);

    cin >> n >> m;
    edges.resize(m);

    for (int i = 0; i < m; i++) cin >> edges[i].u >> edges[i].v >> edges[i].w;

    DSU dsu(n);

    if (dfs(0, 0, 0, dsu)) {
        cout << "Weight = " << target << "\n\n";
        for (auto e : answer) cout << e.u << " - " << e.v << " : " << e.w << '\n';

    }
    else cout << "No spanning tree with weight " << target << " found.\n";

    return 0;
}
