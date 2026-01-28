#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int visited[MAXN]; // 0: Unvisited, 1: Visiting, 2: Visited
int parent[MAXN];
int cycle_start = -1, cycle_end = -1;

bool dfs(int u) {
    visited[u] = 1; // Одоо судалж байна (Саарал)
    
    for (int v : adj[u]) {
        if (visited[v] == 1) {
            // ЦИКЛ ОЛДЛОО!
            // v нь одоогийн recursion stack дотор байна гэдэг нь
            // v-ээс u хүртэл зам байгаа, дээр нь u->v ирмэг нэмэгдээд цикл боллоо.
            cycle_start = v;
            cycle_end = u;
            return true;
        }
        if (visited[v] == 0) {
            parent[v] = u;
            if (dfs(v)) return true; // Хэрэв гүнээс цикл олдвол шууд true буцаана
        }
    }

    visited[u] = 2; // Судалж дууссан (Хар)
    return false;
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
    }

    // Салангид граф байж болох тул бүх цэгээр гүйж шалгана
    for (int i = 1; i <= n; i++) {
        if (visited[i] == 0 && dfs(i)) {
            break; // Цикл олдвол давталтыг зогсооно
        }
    }

    if (cycle_start == -1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        vector<int> cycle;
        cycle.push_back(cycle_start);
        
        // cycle_end-ээс эхлээд cycle_start хүртэл ухарч мөшгөнө
        for (int v = cycle_end; v != cycle_start; v = parent[v]) {
            cycle.push_back(v);
        }
        cycle.push_back(cycle_start); // Битүүлэхийн тулд эхлэлийг дахин нэмнэ

        // parent-аар хөөсөн тул зам урвуу байгаа (Start <- ... <- End). Эргүүлнэ.
        reverse(cycle.begin(), cycle.end());

        cout << cycle.size() << endl;
        for (int node : cycle) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}