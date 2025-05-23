#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <limits>

const long long INF = std::numeric_limits<long long>::max();

struct Edge {
    int to;
    int weight;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m, k; // n: cities, m: flights, k: k shortest
    std::cin >> n >> m >> k;

    std::vector<std::vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    // dist[i] stores the k shortest distances found so far to reach city i
    // Using vector of size k, initialized with INF
    std::vector<std::vector<long long>> dist(n + 1, std::vector<long long>(k, INF));

    // Priority queue stores {distance, city}
    // Use min-priority queue
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> pq;

    // Start at city 1 with distance 0
    dist[1][0] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // If the current distance d is already greater than the k-th
        // shortest distance recorded for u, we can skip this path.
        // This check is important for efficiency.
        if (d > dist[u][k-1]) {
             continue;
        }

        for (const auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;
            long long new_d = d + w;

            // If the new distance is smaller than the k-th largest distance
            // recorded for v (or if we don't have k distances yet)
            if (new_d < dist[v][k-1]) {
                 dist[v][k-1] = new_d;
                 // Keep the k distances for v sorted
                 std::sort(dist[v].begin(), dist[v].end());
                 // Push the new distance to the priority queue
                 pq.push({new_d, v});
            }
        }
    }

    // The k shortest distances to city n are now in dist[n]
    // Print the k distances in increasing order
    for (int i = 0; i < k; ++i) {
        std::cout << dist[n][i] << (i == k - 1 ? "" : " ");
    }
    std::cout << std::endl;

    return 0;
}