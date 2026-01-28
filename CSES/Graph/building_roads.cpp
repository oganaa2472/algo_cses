#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Graph хадгалах Adjacency List (Хэмжээг нь бодлогын хязгаараас арай их авна)
const int MAXN = 100005;
vector<int> adj[MAXN];
// Очсон эсэхийг шалгах массив
bool visited[MAXN];

// DFS функц: Тухайн хоттой холбоотой бүх хотыг 'visited' болгоно
void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

int main() {
    // Input/Output хурдасгах (CP-д заавал хэрэгтэй)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // Замуудыг уншиж Graph үүсгэх
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        // Undirected graph (хоёр урсгалтай) тул хоёр тал руу нь нэмнэ
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Салангид хэсэг бүрийн төлөөлөгч хотуудыг хадгалах
    vector<int> bridges;

    // Бүх хотоор гүйж шалгана
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            // Хэрэв энэ хотод өмнө нь очоогүй бол энэ нь ШИНЭ салангид хэсэг (New Component) юм
            bridges.push_back(i);
            dfs(i); // Энэ хэсэгт хамаарах бүх хотыг visited болгоно
        }
    }

    // Хариу хэвлэх
    // bridges.size() нь нийт салангид хэсгийн тоо (K)
    // Бидэнд K - 1 зам хэрэгтэй
    cout << bridges.size() - 1 << endl;

    // Төлөөлөгчдийг хооронд нь холбоно (0-ийг 1-тэй, 1-ийг 2-той гэх мэт)
    for (size_t i = 0; i < bridges.size() - 1; i++) {
        cout << bridges[i] << " " << bridges[i + 1] << endl;
    }

    return 0;
}