#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const long long INF = 1e18;
const int MOD = 1e9 + 7;

int main() {
    // Input/Output хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // Adjacency list: {neighbor, weight}
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    // 4 төрлийн мэдээлэл хадгалах массивууд
    vector<long long> dist(n + 1, INF);
    vector<long long> count(n + 1, 0);
    vector<int> min_flights(n + 1, 0);
    vector<int> max_flights(n + 1, 0);

    // Dijkstra Priority Queue: {cost, u}
    // Min-Heap (Хамгийн бага зардалтайг эхэлж гаргана)
    priority_queue<pair<long long, int>, 
                   vector<pair<long long, int>>, 
                   greater<pair<long long, int>>> pq;

    // Эхлэл (Syrjälä)
    dist[1] = 0;
    count[1] = 1;
    min_flights[1] = 0;
    max_flights[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Хуучирсан мэдээлэл бол алгасна
        if (d > dist[u]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            long long new_cost = dist[u] + w;

            // 1. Илүү хямд зам олдвол -> Бүгдийг шинэчлэх (Reset)
            if (new_cost < dist[v]) {
                dist[v] = new_cost;
                count[v] = count[u];
                min_flights[v] = min_flights[u] + 1;
                max_flights[v] = max_flights[u] + 1;
                pq.push({new_cost, v});
            }
            // 2. Ижил үнэтэй зам олдвол -> Нэмэх/Сайжруулах (Append/Update)
            else if (new_cost == dist[v]) {
                count[v] = (count[v] + count[u]) % MOD;
                min_flights[v] = min(min_flights[v], min_flights[u] + 1);
                max_flights[v] = max(max_flights[v], max_flights[u] + 1);
                // Зардал өөрчлөгдөөгүй тул pq руу хийх шаардлагагүй
            }
        }
    }

    // Хариу хэвлэх
    cout << dist[n] << " " << count[n] << " " << min_flights[n] << " " << max_flights[n] << endl;

    return 0;
}