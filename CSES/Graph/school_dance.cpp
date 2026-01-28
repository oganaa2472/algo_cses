#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_NODES = 1005; // N, M <= 500, so N+M+2 <= 1002
int capacity[MAX_NODES][MAX_NODES];
vector<int> adj[MAX_NODES];
int parent[MAX_NODES];

// Original input edges to reconstruct solution easily
vector<pair<int, int>> potential_pairs;

// BFS for finding augmenting path
bool bfs(int s, int t) {
    memset(parent, -1, sizeof(parent));
    queue<int> q;
    q.push(s);
    parent[s] = -2;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v] > 0) {
                parent[v] = u;
                if (v == t) return true;
                q.push(v);
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    int s = 0;           // Source
    int t = n + m + 1;   // Sink

    // 1. Граф байгуулах
    // Хөвгүүд: 1..n
    // Охид: n+1..n+m
    
    // S -> Boys
    for (int i = 1; i <= n; i++) {
        adj[s].push_back(i);
        adj[i].push_back(s);
        capacity[s][i] = 1;
    }

    // Girls -> T
    for (int i = 1; i <= m; i++) {
        int girlNode = n + i;
        adj[girlNode].push_back(t);
        adj[t].push_back(girlNode);
        capacity[girlNode][t] = 1;
    }

    // Potential Pairs (Boys -> Girls)
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        int boyNode = u;
        int girlNode = n + v;

        adj[boyNode].push_back(girlNode);
        adj[girlNode].push_back(boyNode);
        
        // Parallel edges (давхардсан хос) байж магадгүй тул 1 гэж тохируулна 
        // (эсвэл += 1 хийхгүй, учир нь 0/1 байх ёстой)
        capacity[boyNode][girlNode] = 1; 
        
        // Хариу хэвлэхэд ашиглахаар хадгалж авъя (заавал биш ч хялбар)
        potential_pairs.push_back({u, v});
    }

    // 2. Max Flow (Edmonds-Karp)
    int max_pairs = 0;
    while (bfs(s, t)) {
        // Энд бүх багтаамж 1 тул урсгал үргэлж 1 байна
        int flow = 1;
        max_pairs += flow;

        int curr = t;
        while (curr != s) {
            int prev = parent[curr];
            capacity[prev][curr] -= flow;
            capacity[curr][prev] += flow;
            curr = prev;
        }
    }

    // 3. Хариу хэвлэх
   // 3. Хариу хэвлэх
    cout << max_pairs << endl;
    
    for (int i = 1; i <= n; i++) { // Бүх хөвгүүдээр гүйнэ
        for (int v : adj[i]) {
            // v нь Охин байх ёстой
            if (v > n && v <= n + m && capacity[i][v] == 0 && capacity[v][i] == 1) {
                cout << i << " " << (v - n) << endl;
                break; // <--- ЭНЭ МӨРИЙГ НЭМЭХ: Хөвгүүн хосоо олсон тул цааш хайх хэрэггүй
            }
        }
    }

    return 0;
}