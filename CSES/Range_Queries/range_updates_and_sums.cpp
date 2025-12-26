#include <iostream>
#include <vector>

using namespace std;

/**
 * PROBLEM: Range Updates and Sums (CSES)
 * Technique: Segment Tree with dual Lazy Propagation (Add & Set)
 */

typedef long long ll;

const int MAXN = 200005;
ll tree[4 * MAXN];
ll lazy_add[4 * MAXN];
ll lazy_set[4 * MAXN];
bool has_set[4 * MAXN];

// Хүлээгдэж буй үйлдлүүдийг хүүхдүүд рүү дамжуулах
void push(int node, int start, int end) {
    int mid = (start + end) / 2;
    if (has_set[node]) {
        // Set үйлдэл дамжуулах
        has_set[2 * node] = has_set[2 * node + 1] = true;
        lazy_set[2 * node] = lazy_set[2 * node + 1] = lazy_set[node];
        lazy_add[2 * node] = lazy_add[2 * node + 1] = 0;
        
        tree[2 * node] = (ll)(mid - start + 1) * lazy_set[node];
        tree[2 * node + 1] = (ll)(end - mid) * lazy_set[node];
        
        has_set[node] = false;
        lazy_set[node] = 0;
    }
    if (lazy_add[node] != 0) {
        // Add үйлдэл дамжуулах
        if (has_set[2 * node]) lazy_set[2 * node] += lazy_add[node];
        else lazy_add[2 * node] += lazy_add[node];
        
        if (has_set[2 * node + 1]) lazy_set[2 * node + 1] += lazy_add[node];
        else lazy_add[2 * node + 1] += lazy_add[node];

        tree[2 * node] += (ll)(mid - start + 1) * lazy_add[node];
        tree[2 * node + 1] += (ll)(end - mid) * lazy_add[node];
        
        lazy_add[node] = 0;
    }
}

void build(const vector<int>& a, int node, int start, int end) {
    if (start == end) {
        tree[node] = a[start];
        return;
    }
    int mid = (start + end) / 2;
    build(a, 2 * node, start, mid);
    build(a, 2 * node + 1, mid + 1, end);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Range Add (Type 1)
void update_add(int node, int start, int end, int l, int r, int x) {
    if (start > end || start > r || end < l) return;
    if (start >= l && end <= r) {
        if (has_set[node]) lazy_set[node] += x;
        else lazy_add[node] += x;
        tree[node] += (ll)(end - start + 1) * x;
        return;
    }
    push(node, start, end);
    int mid = (start + end) / 2;
    update_add(2 * node, start, mid, l, r, x);
    update_add(2 * node + 1, mid + 1, end, l, r, x);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Range Set (Type 2)
void update_set(int node, int start, int end, int l, int r, int x) {
    if (start > end || start > r || end < l) return;
    if (start >= l && end <= r) {
        has_set[node] = true;
        lazy_set[node] = x;
        lazy_add[node] = 0;
        tree[node] = (ll)(end - start + 1) * x;
        return;
    }
    push(node, start, end);
    int mid = (start + end) / 2;
    update_set(2 * node, start, mid, l, r, x);
    update_set(2 * node + 1, mid + 1, end, l, r, x);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Range Sum Query (Type 3)
ll query(int node, int start, int end, int l, int r) {
    if (start > end || start > r || end < l) return 0;
    if (start >= l && end <= r) return tree[node];
    push(node, start, end);
    int mid = (start + end) / 2;
    return query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(a, 1, 1, n);
    while (q--) {
        int t, l, r, x;
        cin >> t >> l >> r;
        if (t == 1) {
            cin >> x;
            update_add(1, 1, n, l, r, x);
        } else if (t == 2) {
            cin >> x;
            update_set(1, 1, n, l, r, x);
        } else {
            cout << query(1, 1, n, l, r) << "\n";
        }
    }
    return 0;
}