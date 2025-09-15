#include <bits/stdc++.h>
using namespace std;

bool dfs(int node, int color, vector<vector<int>>& graph, vector<int>& vis) {
    vis[node] = color;
    for (auto ch : graph[node]) {
        if (vis[ch] == -1) {
            if (!dfs(ch, 1 - color, graph, vis)) return false;
        } else if (vis[ch] == color) {
            return false; // conflict → not bipartite
        }
    }
    return true;
}

void isBipartite(vector<vector<int>>& graph, int n) {
    vector<int> visited(n + 1, -1);

    for (int i = 1; i <= n; i++) {   // 1-based nodes
        if (visited[i] == -1) {
            if (!dfs(i, 0, graph, visited)) {
                cout << "IMPOSSIBLE\n";
                return;
            }
        }
    }


    for (int i = 1; i <= n; i++) {
        int answer = visited[i] ? 2:1;
    
        cout << answer <<" ";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1); // 1-based indexing

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected
    }
    
    isBipartite(adj, n);
}
