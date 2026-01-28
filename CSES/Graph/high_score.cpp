#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Хязгааргүйг илтгэх тоо (long long учир нь оноо маш их/бага байж болно)
const long long NINF = -1e18;

struct Edge {
    int u, v;
    long long w;
};

// N рүү хүрч чадах эсэхийг шалгах BFS-д зориулсан Reverse Graph
vector<int> adj_rev[2505];
bool can_reach_n[2505];

void dfs_reverse(int u) {
    can_reach_n[u] = true;
    for (int v : adj_rev[u]) {
        if (!can_reach_n[v]) {
            dfs_reverse(v);
        }
    }
}

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
        // Reverse graph: v-ээс u руу явна гэж хадгална
        adj_rev[v].push_back(u);
    }

    // N цэгээс буцаж явж үзээд, N-д хүрч чадах цэгүүдийг тэмдэглэх
    dfs_reverse(n);

    // Bellman-Ford initialization
    // Хамгийн их оноо олох тул хасах хязгааргүйгээр дүүргэнэ
    vector<long long> dist(n + 1, NINF);
    dist[1] = 0;

    // Relaxation steps: N-1 удаа
    for (int i = 1; i < n; i++) {
        for (const auto& e : edges) {
            if (dist[e.u] == NINF) continue; // Эхлэлээс хүрч чадахгүй бол алгасна
            
            if (dist[e.u] + e.w > dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
            }
        }
    }

    // N-th step: Check for positive cycles
    // Хэрэв N-дэх удаад оноо нэмэгдсээр байвал эерэг цикл байна
    for (const auto& e : edges) {
        if (dist[e.u] == NINF) continue;

        if (dist[e.u] + e.w > dist[e.v]) {
            // Энд цикл олдлоо. 
            // Гэхдээ энэ цикл 1-ээс эхлээд N-д хүрэх замд нөлөөлөх үү?
            // dist[e.u] != NINF гэдэг нь 1-ээс хүрч болно гэсэн үг.
            // can_reach_n[e.v] гэдэг нь N рүү хүрч чадна гэсэн үг.
            if (can_reach_n[e.v]) {
                cout << -1 << endl;
                return 0;
            }
        }
    }

    cout << dist[n] << endl;

    return 0;
}