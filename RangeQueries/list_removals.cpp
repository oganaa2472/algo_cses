#include <bits/stdc++.h>
using namespace std;

typedef long long item;

struct segtree {
    int size;
    item NEUTRAL_ELEMENT = 0;
    vector<item> sums;

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        sums.resize(2 * size);
    }

    item merge(item a, item b) {
        return a + b;
    }

    item single(item v) {
        return v;
    }

    void build(vector<item>& a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)a.size()) {
                sums[x] = 1;  // Each position initially counts as present
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        sums[x] = merge(sums[2 * x + 1], sums[2 * x + 2]);
    }

    void build(vector<item>& a) {
        build(a, 0, 0, size);
    }

    void set(int i, item v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            sums[x] = single(v);
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m)
            set(i, v, 2 * x + 1, lx, m);
        else
            set(i, v, 2 * x + 2, m, rx);
        sums[x] = merge(sums[2 * x + 1], sums[2 * x + 2]);
    }

    void set(int i, item v) {
        set(i, v, 0, 0, size);
    }

    int find_kth_and_remove(int k, int x, int lx, int rx) {
        if (rx - lx == 1) return lx;
        int m = (lx + rx) / 2;
        int sl = sums[2 * x + 1];
        if (k <= sl)
            return find_kth_and_remove(k, 2 * x + 1, lx, m);
        else
            return find_kth_and_remove(k - sl, 2 * x + 2, m, rx);
    }

    int find_kth_and_remove(int k) {
        return find_kth_and_remove(k, 0, 0, size);
    }
};

int main() {
    int n;
    cin >> n;
    segtree st;
    st.init(n);
    vector<item> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    st.build(a);

    for (int i = 0; i < n; i++) {
        int pos;
        cin >> pos;
        int idx = st.find_kth_and_remove(pos);
        cout << a[idx] << " ";
        st.set(idx, 0);
    }
    cout << "\n";
    return 0;
}
