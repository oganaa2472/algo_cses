#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);  // adjacency list
    vector<int> indegree(n + 1, 0);  // indegree count

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        indegree[b]++;
    }

    // Min-heap for lexicographically smallest order
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) pq.push(i);
    }

    vector<int> order;
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        order.push_back(u);

        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                pq.push(v);
            }
        }
    }

    // Print result
    for (int i = 0; i < n; i++) {
        cout << order[i] << (i + 1 == n ? '\n' : ' ');
    }
}
