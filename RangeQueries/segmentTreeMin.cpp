#include <bits/stdc++.h>
using namespace std;

struct segtree {
    int size;
    vector<long long> sums;

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        sums.assign(2 * size, 0LL);
    }

    long long sum(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) return INT_MAX;
        if (lx >= l && rx <= r) return sums[x];
        
        int mid = (lx + rx) / 2;
        long long s1 = sum(l, r, 2 * x + 1, lx, mid);
        long long s2 = sum(l, r, 2 * x + 2, mid, rx);
        return min(s1,s2);
    }

    long long sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            sums[x] = v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            set(i, v, 2 * x + 1, lx, mid);
        } else {
            set(i, v, 2 * x + 2, mid, rx);
        }
        sums[x] = min(sums[2 * x + 1], sums[2 * x + 2]);
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    segtree st;
    st.init(n);

    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        st.set(i, v);
    }

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int i, v;
            cin >> i >> v;
            st.set(i, v);
        } else {
            int l, r;
            cin >> l >> r;
            cout << st.sum(l, r) << endl;
        }
    }
    return 0;
}
