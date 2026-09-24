#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// yeah, this doesn't work, but can you explain why? 

struct Edge {
    int u, v, w, id;
    static int counter;

    Edge(int u = -1, int v = -1, int w = -1): u(u), v(v), w(w), id(counter++) {}

    bool operator<(const Edge& other) const {
        if (w != other.w) return w < other.w;
        return id < other.id;
    }

    bool operator>(const Edge& other) const {
        if (w != other.w) return w > other.w;
        return id > other.id;
    }
};
int Edge::counter = 0;


template <class T>
class indexed_set {
private:
    using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
    ordered_set s;

public:
    const T& operator[](int k) const { return *s.find_by_order(k); }
    int size() const { return (int)s.size(); }
    bool empty() const { return s.empty(); }
    void push(const T& x) { s.insert(x); }
    void erase(const T& x) { s.erase(x); }
    void erase_by_index(int k) {
        auto it = s.find_by_order(k);
        if (it != s.end()) s.erase(it);
    }
    int get_index(const T& x) const { return (int)s.order_of_key(x); }
    auto it(int k) const { return s.find_by_order(k); }
};


int main() {
    freopen("input.txt", "r", stdin);

    int n, m, src;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n);
    vector<Edge> edges;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
        graph[u].push_back({v, (int)edges.size() - 1});
        graph[v].push_back({u, (int)edges.size() - 1});
    }
    cin >> src;

    indexed_set<Edge> pq;
    vector<int> vis(n, 0), tree;

    vis[src] = true;
    for (auto [v, idx] : graph[src]) pq.push(edges[idx]);
    int ans = 0;

    while (!pq.empty()) {
        Edge e = pq[pq.size() / 2];
        pq.erase_by_index(pq.size() / 2);
        if (vis[e.u] && vis[e.v]) continue;

        int next = vis[e.u] ? e.v : e.u;
        tree.push_back(e.id);
        ans += e.w;
        vis[next] = true;

        for (auto [v, idx] : graph[next]) {
            if (!vis[v]) pq.push(edges[idx]);
        }
    }

    if ((int)tree.size() != n - 1) {
        cout << "Graph is disconnected. MST does not exist.\n";
        return 0;
    }

    cout << "MST weight: " << ans << '\n';
    cout << "Edges:\n";
    for (int id : tree) cout << edges[id].u << " " << edges[id].v << " -> " << edges[id].w << '\n';

    return 0;
}
