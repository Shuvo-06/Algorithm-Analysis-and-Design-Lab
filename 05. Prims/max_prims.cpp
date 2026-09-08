#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w, id;
    static int counter;

    Edge(int u = -1, int v = -1, int w = -1): u(u), v(v), w(w), id(counter++) {}

    bool operator>(const Edge& other) const {
        return w > other.w;
    }

    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

int Edge::counter = 0;

int main() {
    freopen("input.txt", "r", stdin);

    int n, m, src = 0;
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n);
    vector<Edge> edges;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
        graph[u].push_back({v, edges.size() - 1});
        graph[v].push_back({u, edges.size() - 1});
    }
    cin >> src;

    vector<int> vis(n, 0), tree;
    priority_queue<Edge> pq;

    vis[src] = true;
    for (auto [v, idx] : graph[src]) pq.push(edges[idx]);

    long long int ans = 0;
    while (!pq.empty()) {
        Edge e = pq.top();
        pq.pop();

        if (vis[e.u] && vis[e.v]) continue;
        int next = vis[e.u] ? e.v : e.u;
        tree.push_back(e.id);
        ans += e.w;
        vis[next] = true;
        for (auto [v, idx] : graph[next]) {
            if (!vis[v]) pq.push(edges[idx]);
        }
    }

    if (tree.size() != n - 1) {
        cout << "Graph is disconnected. MST does not exist.\n";
        return 0;
    }

    cout << ans << '\n';
    for (int id : tree) cout << edges[id].u << " " << edges[id].v << " -> " << edges[id].w << endl;
    cout << '\n';
    return 0;
}
