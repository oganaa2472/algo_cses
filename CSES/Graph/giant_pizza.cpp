#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

const int MAXM = 200005; // 2 * m nodes
vector<int> adj[MAXM];
vector<int> visited(MAXM), on_stack(MAXM);
vector<int> low(MAXM), disc(MAXM);
vector<int> scc(MAXM); // Аль SCC-д харьяалагдахыг хадгалах
stack<int> st;
int timer, scc_count;

// Tarjan's Algorithm for SCC
void tarjan(int u) {
    disc[u] = low[u] = ++timer;
    st.push(u);
    on_stack[u] = true;

    for (int v : adj[u]) {
        if (disc[v] == 0) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (on_stack[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }

    if (low[u] == disc[u]) {
        scc_count++;
        while (true) {
            int v = st.top();
            st.pop();
            on_stack[v] = false;
            scc[v] = scc_count;
            if (u == v) break;
        }
    }
}

int main() {
    // Input/Output хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < n; i++) {
        char s1, s2;
        int u, v;
        cin >> s1 >> u >> s2 >> v;
        --u; --v; // 0-based index болгох

        // Node mapping:
        // u (Good/+) -> 2*u
        // ~u (Bad/-) -> 2*u + 1
        int node1 = (s1 == '+') ? 2 * u : 2 * u + 1;
        int node2 = (s2 == '+') ? 2 * v : 2 * v + 1;

        // Clause: (node1 OR node2)
        // Implication 1: ~node1 -> node2
        // Implication 2: ~node2 -> node1
        // XOR 1 (u^1) нь node-ийн эсрэг төлөвийг олдог (0->1, 1->0)
        adj[node1 ^ 1].push_back(node2);
        adj[node2 ^ 1].push_back(node1);
    }

    // Бүх цэгээр гүйж SCC олох
    for (int i = 0; i < 2 * m; i++) {
        if (disc[i] == 0) {
            tarjan(i);
        }
    }

    vector<char> result(m);
    for (int i = 0; i < m; i++) {
        // Хэрэв X болон ~X хоёулаа нэг SCC дотор байвал зөрчилтэй
        if (scc[2 * i] == scc[2 * i + 1]) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }

        // Tarjan нь SCC-г урвуу топологи эрэмбээр дугаарладаг.
        // Хэрэв scc[True] < scc[False] байвал True төлөв нь "sink" буюу
        // логикийн урсгалын төгсгөл рүү ойр байна гэсэн үг.
        // Implication graph дээр A -> B байвал бид A=True, B=False гэж сонгож болохгүй.
        // Тиймээс урсгал дагууд нь True утга онооно.
        if (scc[2 * i] < scc[2 * i + 1]) {
            result[i] = '+';
        } else {
            result[i] = '-';
        }
    }

    // Хариу хэвлэх
    for (int i = 0; i < m; i++) {
        cout << result[i] << (i == m - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}