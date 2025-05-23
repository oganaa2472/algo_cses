#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;
const int MOD = 1e9 + 7;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1); // adj[u] = {v, cost}
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    vector<long long> dist(n + 1, INF);    // dist[i] = min cost to reach i
    vector<int> count(n + 1, 0);           // count[i] = number of min-cost paths to i
    vector<int> minFlights(n + 1, INT_MAX); // minFlights[i] = min number of flights to i
    vector<int> maxFlights(n + 1, INT_MIN); // maxFlights[i] = max number of flights to i

    dist[1] = 0;
    count[1] = 1;
    minFlights[1] = 0;
    maxFlights[1] = 0;

    // Min heap: {cost, node}
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                count[v] = count[u];
                minFlights[v] = minFlights[u] + 1;
                maxFlights[v] = maxFlights[u] + 1;
                pq.push({dist[v], v});
            }
            else if (dist[v] == dist[u] + w) {
                count[v] = (count[v] + count[u]) % MOD;
                minFlights[v] = min(minFlights[v], minFlights[u] + 1);
                maxFlights[v] = max(maxFlights[v], maxFlights[u] + 1);
            }
        }
    }

    cout << dist[n] << " " << count[n] << " " << minFlights[n] << " " << maxFlights[n] << "\n";
    return 0;
}
