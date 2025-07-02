#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    int size;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size, 0);
    }

    void build(const vector<int>& a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)a.size()) tree[x] = a[lx];
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(const vector<int>& a) {
        build(a, 0, 0, size);
    }

    int max_query(int l, int r, int x, int lx, int rx) {
        if (lx >= r || rx <= l) return INT_MIN;
        if (lx >= l && rx <= r) return tree[x];
        int m = (lx + rx) / 2;
        int left = max_query(l, r, 2 * x + 1, lx, m);
        int right = max_query(l, r, 2 * x + 2, m, rx);
        return max(left, right);
    }

    int max_query(int l, int r) {
        return max_query(l, r, 0, 0, size);
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    SegmentTree st;
    st.init(n);
    st.build(h);

    while (q--) {
        int a, b;
        cin >> a >> b;
        a--, b--; // 0-based

        int visible = 0, maxSeen = INT_MIN;
        for (int i = a; i <= b; i++) {
            int height = h[i];
            if (height > maxSeen) {
                visible++;
                maxSeen = height;
            }
        }
        cout << visible << "\n";
    }
}
