#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

const int MAXN = 100005;
long long k[MAXN]; // Зоосны тоо
vector<int> adj[MAXN];

// Tarjan хувьсагчид
vector<int> disc(MAXN), low(MAXN);
vector<bool> onStack(MAXN);
stack<int> st;
int timer = 0, sccCount = 0;
int sccID[MAXN]; // Node бүрийн харьяалагдах SCC-ийн дугаар

// Condensation Graph хувьсагчид
long long sccCoins[MAXN]; // SCC бүрийн нийт зоос
vector<int> adjSCC[MAXN]; // SCC хоорондын ирмэг
long long dp[MAXN]; // DP хариу

// Tarjan's Algorithm
void dfsSCC(int u) {
    disc[u] = low[u] = ++timer;
    st.push(u);
    onStack[u] = true;

    for (int v : adj[u]) {
        if (disc[v] == 0) {
            dfsSCC(v);
            low[u] = min(low[u], low[v]);
        } else if (onStack[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }

    if (low[u] == disc[u]) {
        sccCount++;
        while (true) {
            int v = st.top();
            st.pop();
            onStack[v] = false;
            sccID[v] = sccCount;
            sccCoins[sccCount] += k[v]; // SCC доторх зооснуудыг нэмэх
            if (u == v) break;
        }
    }
}

// DP with Memoization
long long solveDP(int u) {
    if (dp[u] != -1) return dp[u];

    long long max_next = 0;
    for (int v : adjSCC[u]) {
        max_next = max(max_next, solveDP(v));
    }

    return dp[u] = sccCoins[u] + max_next;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) cin >> k[i];

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    // 1. Find SCCs
    for (int i = 1; i <= n; i++) {
        if (disc[i] == 0) dfsSCC(i);
    }

    // 2. Build Condensation Graph
    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            // Хэрэв хоёр өрөө өөр өөр SCC-д байвал, тэр хоёр SCC-ийн хооронд зам үүсгэнэ
            if (sccID[u] != sccID[v]) {
                adjSCC[sccID[u]].push_back(sccID[v]);
            }
        }
    }

    // 3. DP on DAG
    // DP массивыг -1-ээр дүүргэх
    fill(dp, dp + sccCount + 1, -1);

    long long ans = 0;
    // Бүх SCC-ээс эхэлж үзээд хамгийн ихийг нь авна
    for (int i = 1; i <= sccCount; i++) {
        ans = max(ans, solveDP(i));
    }

    cout << ans << endl;

    return 0;
}