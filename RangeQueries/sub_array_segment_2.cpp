#include <bits/stdc++.h>
using namespace std;

struct item {
    long long sum, pref, suf, seg;
};

struct segtree {
    int size;
    item NEUTRAL = {0, 0, 0, 0};
    vector<item> tree;

    item merge(item a, item b) {
        return {
            a.sum + b.sum,
            max(a.pref, a.sum + b.pref),
            max(b.suf, b.sum + a.suf),
            max({a.seg, b.seg, a.suf + b.pref})
        };
    }

    item single(long long v) {
        return {
            v,
            max(v, 0LL),
            max(v, 0LL),
            max(v, 0LL)
        };
    }

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size, NEUTRAL);
    }

    void build(vector<long long> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)a.size()) {
                tree[x] = single(a[lx]);
            }
            return;
        }
        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);
        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(vector<long long> &a) {
        build(a, 0, 0, size);
    }

    void set(int i, long long v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = single(v);
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m)
            set(i, v, 2 * x + 1, lx, m);
        else
            set(i, v, 2 * x + 2, m, rx);
        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void set(int i, long long v) {
        set(i, v, 0, 0, size);
    }

    item calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) return NEUTRAL;
        if (lx >= l && rx <= r) return tree[x];
        int mid = (lx + rx) / 2;
        item left = calc(l, r, 2 * x + 1, lx, mid);
        item right = calc(l, r, 2 * x + 2, mid, rx);
        return merge(left, right);
    }

    item calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    segtree st;
    st.init(n);
    st.build(a);

    while (m--) {
        // int type;
        // cin >> type;
        // if (type == 1) {
        //     // Update: set(i, v)
        //     int i;
        //     long long v;
        //     cin >> i >> v;
        //     st.set(i, v);
        // } else {
            // Query: max subarray sum in [l, r)
            int l, r;
            cin >> l >> r;
            // l--;
            //  st.set(l, r);
            cout << st.calc(l-1,r).seg << "\n";
        // }
    }

    return 0;
}
