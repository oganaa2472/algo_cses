#include <bits/stdc++.h>
using namespace std;

void printResult(int node, vector<int>& path) {
    int count = 1;
    string result = "";
    result += to_string(node) + " ";
    for (int i = path.size() - 1; i >= 0; i--) {
        result += to_string(path[i]);
        count++;
        if (path[i] == node) break;
        else result += " ";
    }
    cout << count << endl;
    cout << result << endl;
}

bool dfs(int parent, int u, vector<bool>& visited, vector<vector<int>>& adj, vector<int>& answer) {
    if (visited[u]) {
        if (answer.size() > 2) {
            printResult(u, answer);
            return true; // Cycle found
        }
        return false; // No cycle
    }

    visited[u] = true;
    answer.push_back(u);

    for (auto& v : adj[u]) {
        if (v == parent) continue;
        if (dfs(u, v, visited, adj, answer)) return true; // Propagate the cycle detection
    }

    answer.pop_back();
    return false; // No cycle in this path
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<bool> visited(n + 1, false);
    vector<int> answer;

    bool foundCycle = false;
    for (int i = 1; i <= n; i++) {
        if (!visited[i] && dfs(-1, i, visited, adj, answer)) {
            foundCycle = true;
            break; // Stop after finding the first cycle
        }
    }

    if (!foundCycle)
        cout << "IMPOSSIBLE" << endl;

    return 0;
}
