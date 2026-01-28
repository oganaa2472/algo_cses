#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int in_degree[MAXN], out_degree[MAXN];
vector<int> path;

// Hierholzer's Algorithm using DFS
void dfs(int u) {
    // adj[u] дотроос ирмэгүүдийг дуустал нь авна
    // pop_back() ашиглах нь vector-оос элемент устгахад O(1) тул хурдан
    while (!adj[u].empty()) {
        int v = adj[u].back();
        adj[u].pop_back();
        dfs(v);
    }
    // Мухардалд орсон үедээ замд нэмнэ
    path.push_back(u);
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
        out_degree[u]++;
        in_degree[v]++;
    }

    // 1. Degree Check (Зайлшгүй нөхцөлүүдийг шалгах)
    // Start node (1): out - in = 1
    if (out_degree[1] - in_degree[1] != 1) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    // End node (n): in - out = 1
    if (in_degree[n] - out_degree[n] != 1) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    // Other nodes: in == out
    for (int i = 2; i < n; i++) {
        if (in_degree[i] != out_degree[i]) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    // 2. DFS эхлүүлэх
    dfs(1);

    // 3. Замын урт болон холбоост байдлыг шалгах
    // Зам нь M ирмэг буюу M+1 оройтой байх ёстой
    if (path.size() != m + 1) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    // 4. Хариу хэвлэх (Path урвуу дарааллаар хадгалагдсан тул эргүүлнэ)
    reverse(path.begin(), path.end());
    
    // Анхаарах: Эхлэл 1, төгсгөл N байх ёстой.
    // Хэрэв logic зөв бол автоматаар 1-ээс эхэлж N-д дуусна.
    // Гэхдээ зарим edge case дээр (салангид граф) path.size() шалгалт шүүнэ.
    
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << (i == path.size() - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}