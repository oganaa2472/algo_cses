#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * PROBLEM: Subarray Sum Queries (CSES)
 * Technique: Segment Tree with custom node merging
 * Time Complexity: O(N + M log N)
 */

typedef long long ll;

struct Node {
    ll sum, pref, suff, max_sub;
};

// Хоёр зангилааг нэгтгэх функц
Node merge(Node l, Node r) {
    Node res;
    res.sum = l.sum + r.sum;
    res.pref = max(l.pref, l.sum + r.pref);
    res.suff = max(r.suff, r.sum + l.suff);
    // Хамгийн их дэд массив нь 3 боломжийн нэг байна
    res.max_sub = max({l.max_sub, r.max_sub, l.suff + r.pref});
    return res;
}

const int MAXN = 200005;
Node tree[4 * MAXN];
int n;

void update(int node, int start, int end, int k, int u) {
    if (start == end) {
        // Хэрэв тоо сөрөг байвал хоосон дэд массив (0) нь илүү их байна
        ll val = u;
        ll best = max(0LL, val);
        tree[node] = {val, best, best, best};
        return;
    }
    int mid = (start + end) / 2;
    if (k <= mid) update(2 * node, start, mid, k, u);
    else update(2 * node + 1, mid + 1, end, k, u);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        update(1, 1, n, i, x);
    }

    while (m--) {
        int k, x;
        cin >> k >> x;
        update(1, 1, n, k, x);
        // Нийт массивын хамгийн их дэд массивын нийлбэр язгуур зангилаанд байна
        cout << tree[1].max_sub << "\n";
    }

    return 0;
}