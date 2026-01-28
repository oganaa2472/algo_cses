#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

const int MAXN = 100005;

vector<int> adj[MAXN];      // Үндсэн граф
vector<int> adj_rev[MAXN];  // Урвуу граф
bool visited[MAXN];
stack<int> s;               // Finish time хадгалах стек
int kingdom[MAXN];          // Аль вант улсад харьяалагдахыг хадгалах

// 1-р алхам: Stack-д хийх DFS
void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs1(v);
        }
    }
    // Бүх хөршүүдээ дууссаны дараа stack-д хийнэ
    s.push(u);
}

// 2-р алхам: Вант улс оноох DFS (Урвуу графаар)
void dfs2(int u, int k) {
    kingdom[u] = k;
    for (int v : adj_rev[u]) {
        if (kingdom[v] == 0) { // Хараахан вант улс оноогоогүй бол
            dfs2(v, k);
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
        adj_rev[v].push_back(u); // Урвуу ирмэг
    }

    // 1. Бүх цэгээр гүйж Stack-д хийнэ
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs1(i);
        }
    }

    // 2. Stack-аас гаргаж вант улсуудыг олно
    int kingdom_count = 0;
    while (!s.empty()) {
        int u = s.top();
        s.pop();

        if (kingdom[u] == 0) {
            kingdom_count++;
            dfs2(u, kingdom_count);
        }
    }

    // Хариу хэвлэх
    cout << kingdom_count << endl;
    for (int i = 1; i <= n; i++) {
        cout << kingdom[i] << " ";
    }
    cout << endl;

    return 0;
}