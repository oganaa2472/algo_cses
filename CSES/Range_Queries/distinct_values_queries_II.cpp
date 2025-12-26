#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int MAXN = 400005; // N + Q утгууд багтахаар
int n, q;
int tree[2 * MAXN];
int x[MAXN], pre[MAXN];
set<int> pos[MAXN]; 

// Хурдан итератив Segment Tree
void update_tree(int i, int val) {
    for (tree[i += n] = val; i > 1; i >>= 1)
        tree[i >> 1] = max(tree[i], tree[i ^ 1]);
}

int query_tree(int l, int r) {
    int res = 0;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = max(res, tree[l++]);
        if (r & 1) res = max(res, tree[--r]);
    }
    return res;
}

// Байршил шинэчлэх функц
void fix_pre(int i) {
    if (i < 1 || i > n) return;
    auto it = pos[x[i]].find(i);
    int p = (it == pos[x[i]].begin() ? 0 : *prev(it));
    update_tree(i, p);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;

    vector<int> a(n + 1);
    vector<pair<int, int>> queries(q);
    vector<int> q_val(q, 0);
    vector<int> coords;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        coords.push_back(a[i]);
    }

    vector<pair<int, pair<int, int>>> qs(q);
    for (int i = 0; i < q; i++) {
        cin >> qs[i].first >> qs[i].second.first >> qs[i].second.second;
        if (qs[i].first == 1) coords.push_back(qs[i].second.second);
    }

    // Coordinate Compression (WA-аас сэргийлнэ)
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    auto get_c = [&](int v) { return lower_bound(coords.begin(), coords.end(), v) - coords.begin(); };

    for (int i = 1; i <= n; i++) {
        x[i] = get_c(a[i]);
        pos[x[i]].insert(i);
    }

    for (int i = 1; i <= n; i++) fix_pre(i);

    for (int i = 0; i < q; i++) {
        int t = qs[i].first;
        if (t == 1) {
            int k = qs[i].second.first;
            int u = get_c(qs[i].second.second);

            // 1. Хуучин утгын дараагийн байршлыг засах
            auto it = pos[x[k]].upper_bound(k);
            int next_old = (it == pos[x[k]].end() ? -1 : *it);
            pos[x[k]].erase(k);
            if (next_old != -1) fix_pre(next_old);

            // 2. Шинэ утга тавих
            x[k] = u;
            pos[x[k]].insert(k);
            fix_pre(k);

            // 3. Шинэ утгын дараагийн байршлыг засах
            it = pos[x[k]].upper_bound(k);
            if (it != pos[x[k]].end()) fix_pre(*it);
        } else {
            int l = qs[i].second.first;
            int r = qs[i].second.second;
            if (query_tree(l, r) < l) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return 0;
}