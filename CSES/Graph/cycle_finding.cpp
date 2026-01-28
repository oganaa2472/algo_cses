#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    long long w;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    // dist массивыг 0-ээр дүүргэнэ (Дурын циклийг олохын тулд)
    vector<long long> dist(n + 1, 0);
    // parent массив замаа хадгалахад хэрэгтэй
    vector<int> parent(n + 1, -1);

    int x = -1; // Сүүлд шинэчлэгдсэн цэг

    // Bellman-Ford Algorithm: N удаа давтана
    for (int i = 0; i < n; i++) {
        x = -1;
        for (const auto& e : edges) {
            if (dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                parent[e.v] = e.u;
                x = e.v; // Өөрчлөлт орсон цэгийг хадгална
            }
        }
    }

    if (x == -1) {
        // Хэрэв N-дэх удаад ямар ч өөрчлөлт ороогүй бол сөрөг цикл байхгүй
        cout << "NO" << endl;
    } else {
        // Сөрөг цикл олдлоо
        cout << "YES" << endl;

        // x нь циклийн гадна байж магадгүй тул N удаа ухарч найдвартай цикл дотор орно
        for (int i = 0; i < n; i++) {
            x = parent[x];
        }

        // Одоо x нь цикл дотор байгаа. Замаа цуглуулъя.
        vector<int> cycle;
        for (int v = x; ; v = parent[v]) {
            cycle.push_back(v);
            // Хэрэв буцаад x дээр ирвэл цикл битүүрлээ
            if (v == x && cycle.size() > 1) break;
        }

        // parent-аар хөөсөн тул зам урвуу байгаа. Эргүүлнэ.
        reverse(cycle.begin(), cycle.end());

        // Хэвлэх
        for (int node : cycle) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}