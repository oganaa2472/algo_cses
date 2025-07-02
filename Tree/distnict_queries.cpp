#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int LOG = 20;

vector<int> tree[MAXN];
int up[MAXN][LOG]; // Binary lifting table
int level[MAXN];

// Preprocessing for Binary Lifting
void dfs(int node, int parent) {
    up[node][0] = parent;
    for (int i = 1; i < LOG; ++i) {
        if (up[node][i - 1] != -1)
            up[node][i] = up[up[node][i - 1]][i - 1];
        else
            up[node][i] = -1;
    }

    for (int child : tree[node]) {
        if (child != parent) {
            level[child] = level[node] + 1;
            dfs(child, node);
        }
    }
}

// LCA Query
int lca(int u, int v) {
    if (level[u] < level[v])
        swap(u, v);

    int diff = level[u] - level[v];
    for (int i = LOG - 1; i >= 0; --i) {
        if ((1 << i) & diff)
            u = up[u][i];
    }

    if (u == v) return u;

    for (int i = LOG - 1; i >= 0; --i) {
        if (up[u][i] != -1 && up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }

    return up[u][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    // Read tree edges
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    memset(up, -1, sizeof(up));

    // Start DFS from root node 1
    level[1] = 0;
    dfs(1, -1);

    // Answer queries
    while (q--) {
        int a, b;
        cin >> a >> b;
        int l = lca(a, b);
        int dist = level[a] + level[b] - 2 * level[l];
        cout << dist << '\n';
    }

    return 0;
}
