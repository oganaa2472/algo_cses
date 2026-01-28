#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 505;
const int INF = 1e9;

// Adjacency Matrix for Capacity (N is small enough)
// capacity[u][v] stores residual capacity
int capacity[MAXN][MAXN];
// To store original input edges for outputting the cut
vector<pair<int, int>> edges;
// Adjacency list for graph traversal (BFS)
vector<int> adj[MAXN];
// Parent array to store the path found by BFS
int parent[MAXN];
// Visited array for finding the cut
bool visited[MAXN];

// BFS to find an augmenting path in the residual graph
bool bfs(int s, int t, int n) {
    memset(parent, -1, sizeof(parent));
    queue<int> q;
    q.push(s);
    parent[s] = -2;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v] > 0) {
                parent[v] = u;
                if (v == t) return true;
                q.push(v);
            }
        }
    }
    return false;
}

// DFS/BFS to mark all reachable nodes from source in the residual graph
void dfs_reach(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v] && capacity[u][v] > 0) {
            dfs_reach(v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
        
        // Add directed edges for max flow (cap 1 each way)
        adj[u].push_back(v);
        adj[v].push_back(u);
        
        // Usually, for undirected graphs in Max Flow, we add capacity both ways.
        // If we use edge u->v, we use its capacity.
        capacity[u][v]++;
        capacity[v][u]++;
    }

    int max_flow = 0;
    int s = 1;
    int t = n;

    // 1. Edmonds-Karp Algorithm
    while (bfs(s, t, n)) {
        int flow = INF;
        int curr = t;
        
        // Find bottleneck capacity along the path
        while (curr != s) {
            int prev = parent[curr];
            flow = min(flow, capacity[prev][curr]);
            curr = prev;
        }

        // Update residual capacities
        curr = t;
        while (curr != s) {
            int prev = parent[curr];
            capacity[prev][curr] -= flow;
            capacity[curr][prev] += flow;
            curr = prev;
        }
        max_flow += flow;
    }

    // 2. Find Min-Cut
    // Run a traversal from Source to find all currently reachable nodes
    memset(visited, false, sizeof(visited));
    dfs_reach(s);

    // 3. Output
    cout << max_flow << endl;
    
    // Iterate over original edges.
    // If an edge connects a Visited node to an Unvisited node, it's part of the cut.
    for (auto& e : edges) {
        int u = e.first;
        int v = e.second;
        
        // Check if u is in S (reachable) and v is in T (unreachable) OR vice-versa
        if ((visited[u] && !visited[v]) || (visited[v] && !visited[u])) {
            cout << u << " " << v << endl;
        }
    }

    return 0;
}