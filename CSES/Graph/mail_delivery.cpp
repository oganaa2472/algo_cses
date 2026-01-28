#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
const int MAXM = 200005;

// Graph: {neighbor, edge_index}
vector<pair<int, int>> adj[MAXN];
int degree[MAXN];
bool used_edge[MAXM]; // Ирмэг ашиглагдсан эсэх
int ptr[MAXN]; // Орой бүрийн adjacency list-ийг хаана хүртэл шалгаснаа санах заагч

int main() {
    // Input хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        // Ирмэг бүрт i гэсэн дугаар оноож байна
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        degree[u]++;
        degree[v]++;
    }

    // 1. Бүх оройн зэрэг тэгш эсэхийг шалгах
    for (int i = 1; i <= n; i++) {
        if (degree[i] % 2 != 0) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    // 2. Hierholzer's Algorithm
    stack<int> st;
    st.push(1); // 1-р оройгоос эхэлнэ
    vector<int> path;

    while (!st.empty()) {
        int u = st.top();

        // u оройгоос гарах ашиглагдаагүй ирмэг хайх
        // ptr[u] ашиглан өмнө нь шалгасан ирмэгүүдийг алгасна (O(1) amortized)
        bool found_edge = false;
        while (ptr[u] < adj[u].size()) {
            pair<int, int> edge = adj[u][ptr[u]];
            int v = edge.first;
            int id = edge.second;
            
            ptr[u]++; // Дараагийн удаа энэ ирмэгийг дахин шалгахгүй

            if (!used_edge[id]) {
                used_edge[id] = true;
                st.push(v);
                found_edge = true;
                break; // DFS шиг гүн рүү орно
            }
        }

        if (!found_edge) {
            // Явах замгүй болсон тул одоогийн замыг хариунд нэмээд буцна (Backtrack)
            path.push_back(u);
            st.pop();
        }
    }

    // 3. Бүх ирмэгээр явсан эсэхийг шалгах
    // Хариуны урт нь ирмэгийн тоо + 1 байх ёстой
    if (path.size() != m + 1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        // Зам хэвлэх
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}