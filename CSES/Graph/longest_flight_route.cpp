#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
const int NINF = -1e9; // Хүрч чадахгүйг илтгэх тоо

vector<int> adj[MAXN];
int in_degree[MAXN];
int dist[MAXN];
int parent[MAXN];

int main() {
    // Input хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_degree[v]++; // Орсон ирмэгийн тоог нэмэх
    }

    // Topological Sort хийх Queue
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    // DP Initialization
    for (int i = 1; i <= n; i++) dist[i] = NINF;
    dist[1] = 1; // Эхлэх цэг (Syrjälä)

    // Process nodes in Topological Order
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            // Relaxation:
            // Хэрэв u-ээс v рүү очих нь илүү урт зам үүсгэж байвал,
            // мөн u нь өөрөө 1-р хотоос хүрч болохуйц (NINF биш) байвал шинэчилнэ.
            if (dist[u] != NINF && dist[u] + 1 > dist[v]) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
            }

            // Kahn's Algorithm steps
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    // Хариу шалгах
    if (dist[n] == NINF) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << dist[n] << endl;
        
        // Замаа сэргээх (Backtracking)
        vector<int> path;
        int curr = n;
        while (curr != 0) { // parent[1] нь анх 0 байгаа
            path.push_back(curr);
            curr = parent[curr];
            // 1 дээр ирэхэд parent[1] нь 0 тул loop зогсоно
            if (curr == 1) {
                path.push_back(1);
                break;
            }
        }
        
        // Зам урвуу байгаа тул эргүүлэх
        reverse(path.begin(), path.end());

        for (int city : path) {
            cout << city << " ";
        }
        cout << endl;
    }

    return 0;
}