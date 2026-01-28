#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Хязгааргүйг илтгэх том тоо (10^18)
const long long INF = 1e18;

// N <= 500 тул 2D array хангалттай
long long dist[505][505];

int main() {
    // Input/Output хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    cin >> n >> m >> q;

    // 1. Матрицаа бэлдэх (Initialization)
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) dist[i][j] = 0; // Өөрөөсөө өөр рүүгээ 0
            else dist[i][j] = INF;      // Бусад нь одоогоор мэдэгдэхгүй
        }
    }

    // 2. Замуудыг оруулах
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        // Undirected graph (хоёр урсгалтай)
        // Анхаар: Хоёр хотын хооронд олон зам байж болно, хамгийн багыг нь авна.
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }

    // 3. Floyd-Warshall Algorithm (O(N^3))
    // k = завсрын цэг
    for (int k = 1; k <= n; k++) {
        // i = эхлэх цэг
        for (int i = 1; i <= n; i++) {
            // j = очих цэг
            for (int j = 1; j <= n; j++) {
                // Хэрэв i -> k болон k -> j замууд байгаа бол
                // i -> j замыг шинэчлэх (Relaxation)
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // 4. Query хариулах (O(1))
    while (q--) {
        int u, v;
        cin >> u >> v;
        if (dist[u][v] == INF) {
            cout << -1 << "\n";
        } else {
            cout << dist[u][v] << "\n";
        }
    }

    return 0;
}