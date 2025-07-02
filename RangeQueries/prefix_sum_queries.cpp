#include <bits/stdc++.h>
using namespace std;

struct item {
    long long sum, pref;
};

struct segtree {
    int size;
    item NEUTRAL_ELEMENT = {0, 0};
    vector<item> sums;

    
    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        sums.resize(2 * size);
    }

    item merge(item a, item b) {
        return {
            a.sum + b.sum,
            max(a.pref, a.sum + b.pref)
        };
    }

    item single(long long v) {
        if (v > 0)
            return {v, v};
        else
            return {v, 0};
    }

    item sum(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) return NEUTRAL_ELEMENT;
        if (lx >= l && rx <= r) return sums[x];

        int mid = (lx + rx) / 2;
        item s1 = sum(l, r, 2 * x + 1, lx, mid);
        item s2 = sum(l, r, 2 * x + 2, mid, rx);
        return merge(s1, s2);
    }

    item sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }

    void build(vector<long long>& a) {
        build(a, 0, 0, size);
    }

    void build(vector<long long>& a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)a.size()) {
                sums[x] = single(a[lx]);
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        sums[x] = merge(sums[2 * x + 1], sums[2 * x + 2]);
    }

    void set(int i, long long v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            sums[x] = single(v);
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            set(i, v, 2 * x + 1, lx, mid);
        } else {
            set(i, v, 2 * x + 2, mid, rx);
        }
        sums[x] = merge(sums[2 * x + 1], sums[2 * x + 2]);
    }

    void set(int i, long long v) {
        set(i, v, 0, 0, size);
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    segtree st;
    vector<long long> a(n);
    st.init(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    st.build(a);

    while (m--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k;
            long long v;
            cin >> k >> v;
            st.set(k - 1, v);
        } else {
            int l, r;
            cin >> l >> r;
            l--;
            cout << st.sum(l, r).pref << endl;
        }
    }
    return 0;
}
