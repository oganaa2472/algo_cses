#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];

vector<int> bfs(int start, int n) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    return dist;
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Step 1: Find farthest from node 1
    vector<int> dist1 = bfs(1, n);
    int u = max_element(dist1.begin(), dist1.end()) - dist1.begin();

    // Step 2: Find farthest from u
    vector<int> distU = bfs(u, n);
    int v = max_element(distU.begin(), distU.end()) - distU.begin();

    // Step 3: BFS from v
    vector<int> distV = bfs(v, n);

    // Step 4: For each node, max distance from u or v
    for (int i = 1; i <= n; ++i) {
        cout << max(distU[i], distV[i]) << " ";
    }
    cout << endl;

    return 0;
}
