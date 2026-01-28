#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

// Хязгааргүйг илтгэх том тоо
const long long INF = 1e18;

int main() {
    // Input хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // Adjacency List: {neighbor, weight}
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    // dist[city][state]
    // state 0: coupon not used
    // state 1: coupon used
    vector<vector<long long>> dist(n + 1, vector<long long>(2, INF));

    // Priority Queue: {cost, city, state}
    // Min-Heap ашиглана
    priority_queue<tuple<long long, int, int>, 
                   vector<tuple<long long, int, int>>, 
                   greater<tuple<long long, int, int>>> pq;

    // Эхлэх цэг
    dist[1][0] = 0;
    pq.push({0, 1, 0});

    while (!pq.empty()) {
        auto [d, u, state] = pq.top();
        pq.pop();

        // Хэрэв хуучирсан мэдээлэл байвал алгасна
        if (d > dist[u][state]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            // Сонголт 1: Купон ашиглахгүйгээр энгийнээр явах
            // Хэрэв state=0 байсан бол 0 хэвээрээ, 1 байсан бол 1 хэвээрээ очно
            if (dist[u][state] + w < dist[v][state]) {
                dist[v][state] = dist[u][state] + w;
                pq.push({dist[v][state], v, state});
            }

            // Сонголт 2: Купон ашиглах (Зөвхөн одоо state=0 байгаа үед л боломжтой)
            if (state == 0) {
                long long discountPrice = w / 2;
                if (dist[u][0] + discountPrice < dist[v][1]) {
                    dist[v][1] = dist[u][0] + discountPrice;
                    pq.push({dist[v][1], v, 1}); // Төлөв 1 болж шилжинэ
                }
            }
        }
    }

    // Metsälä (n) хотод купон ашигласан байдлаар очсон хамгийн бага зардал
    cout << dist[n][1] << endl;

    return 0;
}