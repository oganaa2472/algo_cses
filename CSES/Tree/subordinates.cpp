#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> subordinates;

int dfs(int u) {
    int count = 0; // number of subordinates
    for (int v : adj[u]) {
        count += 1 + dfs(v);
    }
    subordinates[u] = count;
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    adj.resize(n + 1);
    subordinates.resize(n + 1);

    for (int i = 2; i <= n; ++i) {
        int boss;
        cin >> boss;
        adj[boss].push_back(i);
    }

    dfs(1);

    for (int i = 1; i <= n; ++i)
        cout << subordinates[i] << " ";
    cout << "\n";

    return 0;
}
