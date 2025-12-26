#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 2e9; // Large enough for pizza prices

struct SegmentTree {
    int n;
    vector<int> tree;
    SegmentTree(int _n) : n(_n), tree(4 * _n + 1) {}

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) update(2 * node, start, mid, idx, val);
        else update(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return INF;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return min(query(2 * node, start, mid, l, r),
                   query(2 * node + 1, mid + 1, end, l, r));
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<int> p(n + 1);
    
    SegmentTree leftTree(n), rightTree(n);

    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        leftTree.update(1, 1, n, i, p[i] - i);
        rightTree.update(1, 1, n, i, p[i] + i);
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k, x;
            cin >> k >> x;
            leftTree.update(1, 1, n, k, x - k);
            rightTree.update(1, 1, n, k, x + k);
        } else {
            int k;
            cin >> k;
            int ansLeft = leftTree.query(1, 1, n, 1, k) + k;
            int ansRight = rightTree.query(1, 1, n, k, n) - k;
            cout << min(ansLeft, ansRight) << "\n";
        }
    }

    return 0;
}