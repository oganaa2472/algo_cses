#include <iostream>
#include <vector>

using namespace std;

void dfs(int parent, int child, const vector<vector<int>>& adj, vector<int>& result) {
    // result[child] defaults to 0 (no direct subordinates initially)
    for (int u : adj[child]) {
        if (u == parent) continue;

        // 1. First recurse deeper to calculate the child's subtree
        dfs(child, u, adj, result);

        // 2. Add each child's total subtree (subordinates + the child itself (+1))
        result[child] += result[u] + 1;
    }
}

int main() {
    // Fast I/O for 2 * 10^5 constraints
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<int>> adj(n + 1);
    vector<int> result(n + 1, 0);

    for (int i = 2; i <= n; i++) {
        int boss;
        cin >> boss;
        adj[boss].push_back(i);
        adj[i].push_back(boss);
    }

    dfs(0, 1, adj, result);

    for (int i = 1; i <= n; i++) {
        cout << result[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}