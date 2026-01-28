#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Хязгааргүйг илтгэх том тоо (long long хязгаар)
const long long INF = 1e18;

int main() {
    // Input/Output хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // Adjacency List: adj[u] -> {v, weight}
    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // Directed graph тул зөвхөн нэг тал руу нь нэмнэ
        adj[u].push_back({v, w});
    }

    // Distance array: Бүгдийг INF болгоно
    vector<long long> dist(n + 1, INF);
    
    // Priority Queue: {distance, node}
    // greater<...> ашиглан Min-Heap болгоно (хамгийн бага нь орой дээрээ байна)
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    // Эхлэлийн цэгээ тохируулах
    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        // Орой дээрх хамгийн бага зайтай элементийг авах
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Хэрэв бидний авсан зай (d) нь одоо мэдэгдэж байгаа хамгийн бага зайнаас (dist[u])
        // их байвал энэ нь хуучирсан мэдээлэл тул алгасна.
        if (d > dist[u]) continue;

        // Хөршүүдийг шалгах
        for (auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            // Relaxation: Илүү богино зам олдвол шинэчилнэ
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Бүх хот руу очих хамгийн богино зайг хэвлэх
    for (int i = 1; i <= n; i++) {
        cout << dist[i] << " ";
    }
    cout << endl;

    return 0;
}