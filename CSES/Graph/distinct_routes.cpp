#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 505;

// adj: Max Flow олоход ашиглах граф (Forward & Backward edges)
vector<int> adj[MAXN];
// adj_original: Зөвхөн анхны чиглэлтэй ирмэгүүд (Зам сэргээхэд ашиглана)
vector<int> adj_original[MAXN];

// Capacity matrix: Үлдэгдэл багтаамж
int capacity[MAXN][MAXN];
int parent[MAXN];
int n, m;

// BFS for Edmonds-Karp (Augmenting path хайх)
bool bfs() {
    memset(parent, -1, sizeof(parent));
    queue<int> q;
    q.push(1);
    parent[1] = -2;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v] > 0) {
                parent[v] = u;
                if (v == n) return true;
                q.push(v);
            }
        }
    }
    return false;
}

int main() {
    // Input/Output хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        
        // Max Flow граф
        adj[u].push_back(v);
        adj[v].push_back(u); // Residual edge-д зориулж буцах холбоос нэмнэ
        capacity[u][v] = 1;  // Нэг ирмэгийг нэг л удаа ашиглана
        
        // Зам сэргээхэд ашиглах граф (зөвхөн урагшаа)
        adj_original[u].push_back(v);
    }

    int max_flow = 0;

    // 1. Edmonds-Karp Algorithm ашиглан Max Flow олох
    while (bfs()) {
        int flow = 1e9;
        int curr = n;
        
        // Зам дагуух хамгийн бага багтаамжийг олох (энэ бодлогод үргэлж 1 байна)
        while (curr != 1) {
            int prev = parent[curr];
            flow = min(flow, capacity[prev][curr]);
            curr = prev;
        }

        // Урсгалыг нэмж, багтаамжуудыг шинэчлэх
        max_flow += flow;
        curr = n;
        while (curr != 1) {
            int prev = parent[curr];
            capacity[prev][curr] -= flow; // Урагшаа урсгал хасна
            capacity[curr][prev] += flow; // Буцах урсгал нэмнэ
            curr = prev;
        }
    }

    // Хариу: Хамгийн их өдрийн тоо
    cout << max_flow << endl;

    // 2. Замуудыг ялгаж хэвлэх (Path Decomposition)
    // Бид max_flow ширхэг зам олох ёстой
    for (int i = 0; i < max_flow; i++) {
        vector<int> path;
        int curr = 1;
        path.push_back(1);

        while (curr != n) {
            // Одоогийн цэгээс урсгал гүйсэн ирмэгийг хайна
            for (int v : adj_original[curr]) {
                // capacity[curr][v] == 0 гэдэг нь энэ ирмэг дүүрсэн (ашиглагдсан) гэсэн үг
                if (capacity[curr][v] == 0) {
                    // Энэ ирмэгийг сонгож замд нэмнэ
                    path.push_back(v);
                    
                    // Энэ ирмэгийг "чөлөөлнө" (багтаамжийг 1 болгож тэмдэглэнэ)
                    // Ингэснээр дараагийн удаа энэ ирмэгийг дахин ашиглахгүй (loop-д орохгүй)
                    capacity[curr][v] = 1; 
                    
                    curr = v;
                    break; // Нэг алхам хийсэн тул дараагийн алхам руу шилжинэ
                }
            }
        }

        // Олдсон замыг хэвлэх
        cout << path.size() << endl;
        for (size_t j = 0; j < path.size(); j++) {
            cout << path[j] << (j == path.size() - 1 ? "" : " ");
        }
        cout << endl;
    }

    return 0;
}