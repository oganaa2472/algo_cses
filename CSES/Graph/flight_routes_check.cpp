#include <iostream>
#include <vector>
#include <cstring> // memset

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];      // Үндсэн граф
vector<int> adj_rev[MAXN];  // Урвуу граф
bool visited[MAXN];

// DFS функц
void dfs(int u, vector<int> graph[]) {
    visited[u] = true;
    for (int v : graph[u]) {
        if (!visited[v]) {
            dfs(v, graph);
        }
    }
}

int main() {
    // Input/Output хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj_rev[v].push_back(u); // Урвуу ирмэг хадгалах
    }

    // 1. Forward Check (1-ээс бусад руу)
    memset(visited, false, sizeof(visited));
    dfs(1, adj);

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            // 1-ээс i рүү очиж чадахгүй байна
            cout << "NO" << endl;
            cout << 1 << " " << i << endl;
            return 0;
        }
    }

    // 2. Backward Check (Бусдаас 1 рүү) -> Reverse DFS
    memset(visited, false, sizeof(visited));
    dfs(1, adj_rev);

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            // i-ээс 1 рүү ирж чадахгүй байна (Reverse дээр 1->i байхгүй бол)
            cout << "NO" << endl;
            cout << i << " " << 1 << endl;
            return 0;
        }
    }

    // Хоёулаа амжилттай бол
    cout << "YES" << endl;

    return 0;
}