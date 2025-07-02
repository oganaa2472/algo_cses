#include <bits/stdc++.h>
using namespace std;

typedef long long item;

struct segtree {
    int size;
    vector<item> tree;

    void init(int n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size, 0);
    }

    void build() {
        for (int i = 0; i < size; ++i)
            tree[size + i] = 1;
        for (int i = size - 1; i >= 0; --i)
            tree[i] = tree[2 * i] + tree[2 * i + 1];
    }

    void set(int i, item v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = v;
            return;
        }
        int mid = (lx + rx) / 2;
        if (i < mid) {
            set(i, v, 2 * x + 1, lx, mid);
        } else {
            set(i, v, 2 * x + 2, mid, rx);
        }
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void set(int i, item v) {
        set(i, v, 0, 0, size);
    }

    int findKth(int k, int x, int lx, int rx) {
        if (rx - lx == 1) return lx;
        int mid = (lx + rx) / 2;
        if (tree[2 * x + 1] > k) {
            return findKth(k, 2 * x + 1, lx, mid);
        } else {
            return findKth(k - tree[2 * x + 1], 2 * x + 2, mid, rx);
        }
    }

    int findKth(int k) {
        return findKth(k, 0, 0, size);
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    segtree st;
    st.init(n);
    st.build();

    vector<int> result(n);
    for (int i = n - 1; i >= 0; --i) {
        int pos = st.findKth(a[i]);
        result[i] = pos + 1; // use 1-based values for permutation
        st.set(pos, 0); // mark as used
    }

    for (int i = 0; i < n; ++i)
        cout << result[i] << " ";
    cout << '\n';
    return 0;
}
