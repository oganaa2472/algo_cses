#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, long long>> edges;
    for (int i = 0; i < m; ++i) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        edges.emplace_back(a, b, c);
    }

    vector<long long> dist(n + 1, 0); // distances from a dummy source
    vector<int> parent(n + 1, -1);
    int x = -1;

    for (int i = 1; i <= n; ++i) {
        x = -1;
        for (auto [u, v, w] : edges) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                x = v; // last updated node
            }
        }
    }

    if (x == -1) {
        cout << "NO\n";
    } else {
        // To ensure we’re inside the cycle
        for (int i = 0; i < n; ++i)
            x = parent[x];

        vector<int> cycle;
        int cur = x;
        do {
            cycle.push_back(cur);
            cur = parent[cur];
        } while (cur != x || cycle.size() == 1);
        cycle.push_back(x);
        
        reverse(cycle.begin(), cycle.end());
        int sz = cycle.size();
        if(sz>2&&cycle[sz-1]==cycle[sz-2]) cycle.pop_back();
        cout << "YES\n";
        for (int node : cycle)
            cout << node << " ";
        cout << "\n";
    }

    return 0;
}
