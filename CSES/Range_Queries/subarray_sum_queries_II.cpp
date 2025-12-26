#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct Node {
    ll sum, pref, suff, max_sub;
};

Node merge(Node l, Node r) {
    Node res;
    res.sum = l.sum + r.sum;
    res.pref = max(l.pref, l.sum + r.pref);
    res.suff = max(r.suff, r.sum + l.suff);
    res.max_sub = max({l.max_sub, r.max_sub, l.suff + r.pref});
    return res;
}

const int MAXN = 200005;
Node tree[4 * MAXN];
int x[MAXN];

void build(int node, int start, int end, int n) {
    if (start == end) {
        ll val = x[start];
        ll best = max(0LL, val); // Хоосон дэд массив зөвшөөрөгдөх тул
        tree[node] = {val, best, best, best};
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid, n);
    build(2 * node + 1, mid + 1, end, n);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

Node query(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) return tree[node];
    int mid = (start + end) / 2;
    if (r <= mid) return query(2 * node, start, mid, l, r);
    if (l > mid) return query(2 * node + 1, mid + 1, end, l, r);
    
    return merge(query(2 * node, start, mid, l, r), 
                 query(2 * node + 1, mid + 1, end, l, r));
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q;
    if (!(cin >> n >> q)) return 0;
    for (int i = 1; i <= n; i++) cin >> x[i];
    build(1, 1, n, n);
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << query(1, 1, n, a, b).max_sub << "\n";
    }
    return 0;
}