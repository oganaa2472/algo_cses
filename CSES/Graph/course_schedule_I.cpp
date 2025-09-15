#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> graph(n + 1);
    vector<int> indegree(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;          // a must be before b
        graph[a].push_back(b);
        ++indegree[b];
    }

    priority_queue<int, vector<int>, greater<int>> pq;  // min-heap for lexicographically smallest order
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) pq.push(i);
    }

    vector<int> order;
    while (!pq.empty()) {
        int u = pq.top(); pq.pop();
        order.push_back(u);
        for (int v : graph[u]) {
            if (--indegree[v] == 0) pq.push(v);
        }
    }

    // A valid schedule is guaranteed; otherwise, would check if order.size() == n
    if (order.size() != n) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << order[i];
    }
    cout << '\n';
    return 0;
}