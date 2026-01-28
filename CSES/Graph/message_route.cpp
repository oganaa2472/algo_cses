#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Graph хадгалах Adjacency List
const int MAXN = 100005;
vector<int> adj[MAXN];

// parent[i] нь i компьютер лүү хаанаас ирснийг хадгална
int parent[MAXN];
// Очсон эсэхийг шалгах массив
bool visited[MAXN];

int main() {
    // Input/Output хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // Граф унших
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // BFS эхлүүлэх
    queue<int> q;
    q.push(1);
    visited[1] = true;
    parent[1] = 0; // Эхлэлийн цэгт эцэг байхгүй

    bool found = false;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // Хэрэв Maija-гийн компьютер (n) дээр ирвэл зогсоно
        if (u == n) {
            found = true;
            break;
        }

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u; // v лүү u-ээс ирсэн гэж тэмдэглэнэ
                q.push(v);
            }
        }
    }

    // Хариу хэвлэх
    if (!found) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        // Замаа мөшгих (Backtracking)
        vector<int> path;
        int curr = n;
        
        while (curr != 0) {
            path.push_back(curr);
            curr = parent[curr];
        }

        // Зам урвуу байгаа тул эргүүлэх
        reverse(path.begin(), path.end());

        // Замын урт (компьютерын тоо)
        cout << path.size() << endl;
        
        // Замаа хэвлэх
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}