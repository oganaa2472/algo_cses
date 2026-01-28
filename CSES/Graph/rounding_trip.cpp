#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
vector<int> parent(MAXN);
bool visited[MAXN];

int cycle_start = -1;
int cycle_end = -1;

// DFS ашиглан цикл хайх
bool dfs(int u, int p) {
    visited[u] = true;
    parent[u] = p;

    for (int v : adj[u]) {
        // Хэрэв дөнгөж ирсэн замаараа буцах гэж байвал алгасна
        if (v == p) continue;

        if (visited[v]) {
            // ЦИКЛ ОЛДЛОО!
            // v нь аль хэдийн очсон цэг, мөн p (эцэг) биш байна.
            cycle_end = u;
            cycle_start = v;
            return true;
        }

        // Хэрэв очоогүй бол цааш гүн рүү хайна
        if (!visited[v]) {
            if (dfs(v, u)) return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Граф салангид байж болох тул бүх цэгээр гүйж шалгана
    for (int i = 1; i <= n; i++) {
        if (!visited[i] && cycle_start == -1) {
            dfs(i, -1);
        }
    }

    if (cycle_start == -1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        vector<int> cycle;
        cycle.push_back(cycle_start);
        
        // Parent массиваа ашиглан арагшаа мөшгих
        for (int v = cycle_end; v != cycle_start; v = parent[v]) {
            cycle.push_back(v);
        }
        cycle.push_back(cycle_start); // Битүү болгохын тулд эхлэлийг дахин нэмнэ

        cout << cycle.size() << endl;
        for (int node : cycle) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}