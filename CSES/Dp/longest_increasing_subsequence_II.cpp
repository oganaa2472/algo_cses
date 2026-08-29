#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;

struct SegmentTree {
    int n;
    vector<long long> tree;

    SegmentTree(int n) : n(n), tree(4 * n, 0) {}

    // [l, r] интервалын нийлбэрийг олох
    long long query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0; // Завсарт багтахгүй бол
        if (l <= start && end <= r) return tree[node]; // Бүрэн багтвал

        int mid = (start + end) / 2;
        long long left_sum = query(2 * node, start, mid, l, r);
        long long right_sum = query(2 * node + 1, mid + 1, end, l, r);

        return (left_sum + right_sum) % MOD;
    }

    // idx байрлал дээр val утгыг нэмэх
    void update(int node, int start, int end, int idx, long long val) {
        if (start == end) {
            tree[node] = (tree[node] + val) % MOD;
            return;
        }

        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }

        tree[node] = (tree[2 * node] + tree[2 * node + 1]) % MOD;
    }
};

int main() {
    // Оролт ба гарагтыг хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> x(n);
    vector<int> vals(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        vals[i] = x[i];
    }
    
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    SegmentTree segTree(vals.size());

    for (int i = 0; i < n; i++) {
        int pos = lower_bound(vals.begin(), vals.end(), x[i]) - vals.begin();
        long long count = segTree.query(1, 1, vals.size(), 1, pos);
        segTree.update(1, 1, vals.size(), pos + 1, count + 1);
    }

    cout << segTree.query(1, 1, vals.size(), 1, vals.size()) << "\n";

    return 0;
}