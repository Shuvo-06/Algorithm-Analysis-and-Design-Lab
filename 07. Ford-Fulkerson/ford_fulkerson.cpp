#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> residue(n, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        residue[u][v] += w;
    }

    int s, t;
    cin >> s >> t;
    vector <int> parent(n);
    function <int(int, int)> dfs = [&](int u, int flow) {
        if (u == t) return flow;
        for (int v = 0; v < n; v++) {
            if (parent[v] != -1 || residue[u][v] <= 0) continue;

            parent[v] = u;
            int new_flow = dfs(v, min(flow, residue[u][v]));
            if (new_flow > 0) return new_flow;
        }
        return 0;
    };

    int max_flow = 0;
    while (true) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        int new_flow = dfs(s, inf);
        if (new_flow == 0) break;

        int curr = t;
        while (curr != s) {
            int prev = parent[curr];
            residue[prev][curr] -= new_flow;
            residue[curr][prev] += new_flow;
            curr = prev;
        }
        max_flow += new_flow;
    }

    cout << max_flow << '\n';
    return 0;
}

/*
6 9
0 1 16
0 2 13
1 2 10
2 1 4
1 3 12
2 4 14
3 2 9
3 5 20
4 3 7
0 5
Expected : 19

4 5
0 1 100
0 2 100
1 2 1
1 3 100
2 3 100
0 3
Expected : 200
*/
