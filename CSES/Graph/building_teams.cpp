#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int team[MAXN]; // 0: Хуваарилагдаагүй, 1: Team 1, 2: Team 2
bool possible = true;

// BFS ашиглан багт хуваах функц
void bfs(int start) {
    queue<int> q;
    q.push(start);
    team[start] = 1; // Эхний хүнийг Баг 1-д оруулна

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (team[v] == 0) {
                // Хэрэв багт ороогүй бол эсрэг багт оруулна
                // u нь 1 бол v нь 2, u нь 2 бол v нь 1 болно
                team[v] = (team[u] == 1) ? 2 : 1;
                q.push(v);
            } else {
                // Хэрэв аль хэдийн багт орсон бөгөөд
                // найзтайгаа ижил багт байвал энэ нь IMPOSSIBLE
                if (team[v] == team[u]) {
                    possible = false;
                    return;
                }
            }
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
        adj[v].push_back(u);
    }

    // Бүх сурагчдыг шалгана (Салангид граф байж болно)
    for (int i = 1; i <= n; i++) {
        if (team[i] == 0) {
            bfs(i);
            // Хэрэв аль нэг хэсэгт зөрчил гарвал шууд зогсоно
            if (!possible) break;
        }
    }

    if (!possible) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        for (int i = 1; i <= n; i++) {
            cout << team[i] << " ";
        }
        cout << endl;
    }

    return 0;
}