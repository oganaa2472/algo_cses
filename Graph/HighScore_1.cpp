#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;

int main() {
    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, ll>> edges;
    
    for (int i = 0; i < m; i++) {
        int a, b;
        ll x;
        cin >> a >> b >> x;
        edges.emplace_back(a, b, x);
    }

    vector<ll> dist(n + 1, -INF);
    dist[1] = 0;

    for (int i = 1; i < n; i++) {
        for (auto [a, b, x] : edges) {
            if (dist[a] != -INF && dist[b] < dist[a] + x) {
                dist[b] = dist[a] + x;
            }
        }
    }

    // Cycle шалгах
    vector<bool> in_cycle(n + 1, false);
    for (int i = 1; i <= n; i++) {
        for (auto [a, b, x] : edges) {
            if (dist[a] != -INF && dist[b] < dist[a] + x) {
                dist[b] = dist[a] + x;
                in_cycle[b] = true;
            }
            if (in_cycle[a]) in_cycle[b] = true;
        }
    }

    if (in_cycle[n]) cout << -1 << endl;
    else cout << dist[n] << endl;
}
