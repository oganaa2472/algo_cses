#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

const long long INF = 1e18; // A large value to represent infinity

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    // dist[i][0] = min cost to reach city i without using discount
    // dist[i][1] = min cost to reach city i using discount
    vector<vector<long long>> dist(n + 1, vector<long long>(2, INF));

    // Priority queue stores tuples of {cost, city, used_discount}
    // used_discount is 0 if not used, 1 if used
    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<tuple<long long, int, int>>> pq;

    dist[1][0] = 0;
    pq.push({0, 1, 0}); // Start at city 1, cost 0, discount not used

    while (!pq.empty()) {
        auto [d, u, used_discount] = pq.top();
        pq.pop();

        if (d > dist[u][used_discount]) {
            continue;
        }

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            // Case 1: Discount not used yet
            if (used_discount == 0) {
                // Option 1.1: Don't use discount on this edge
                if (dist[u][0] + w < dist[v][0]) {
                    dist[v][0] = dist[u][0] + w;
                    pq.push({dist[v][0], v, 0});
                }
                // Option 1.2: Use discount on this edge
                if (dist[u][0] + w / 2 < dist[v][1]) {
                    dist[v][1] = dist[u][0] + w / 2;
                    pq.push({dist[v][1], v, 1});
                }
            }
            // Case 2: Discount already used
            else { // used_discount == 1
                // Cannot use discount again, take the full price
                if (dist[u][1] + w < dist[v][1]) {
                    dist[v][1] = dist[u][1] + w;
                    pq.push({dist[v][1], v, 1});
                }
            }
        }
    }

    // The answer is the minimum of reaching city n with or without the discount applied somewhere
    cout << min(dist[n][0], dist[n][1]) << endl;

    return 0;
}