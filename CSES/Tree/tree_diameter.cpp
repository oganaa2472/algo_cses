#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adj;
vector<int> dist;
int farthestNode;
int maxDist;

void dfs(int node, int parent, int d) {
    dist[node] = d;
    if (d > maxDist) {
        maxDist = d;
        farthestNode = node;
    }
    for (int nei : adj[node]) {
        if (nei == parent) continue;
        dfs(nei, node, d + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // 1️⃣ First DFS from node 1
    dist.assign(n + 1, 0);
    maxDist = -1;
    dfs(1, -1, 0);
    int u = farthestNode;

    // 2️⃣ Second DFS from u
    dist.assign(n + 1, 0);
    maxDist = -1;
    dfs(u, -1, 0);
    int diameter = maxDist;

    cout << diameter << "\n";
    return 0;
}
