#include <iostream>
#include <vector>

using namespace std;

/**
 * PROBLEM: Range Update Queries (CSES)
 * Technique: Segment Tree with Lazy Propagation
 * Time Complexity: O(n + q log n)
 * Space Complexity: O(4n)
 */

typedef long long ll;

const int MAXN = 200005;
ll tree[4 * MAXN];
ll lazy[4 * MAXN];

// Function to propagate the lazy values to children
void push(int node, int start, int end) {
    if (lazy[node] != 0) {
        // Apply the lazy value to the current node
        // Since this is a range add, the sum would increase by (range_size * value)
        // However, for point queries, we just need to ensure the value reaches the leaf.
        tree[node] += (ll)(end - start + 1) * lazy[node];
        
        // If not a leaf node, pass the lazy tag to children
        if (start != end) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        
        // Reset the lazy tag for the current node
        lazy[node] = 0;
    }
}

// Build the initial tree: O(n)
void build(const vector<int>& arr, int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    build(arr, 2 * node, start, mid);
    build(arr, 2 * node + 1, mid + 1, end);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Update a range [l, r] by adding val: O(log n)
void update(int node, int start, int end, int l, int r, int val) {
    push(node, start, end); // Always push before processing
    if (start > end || start > r || end < l) return;

    if (start >= l && end <= r) {
        lazy[node] += val;
        push(node, start, end);
        return;
    }

    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r, val);
    update(2 * node + 1, mid + 1, end, l, r, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Query the value at a specific point (treated as a range [k, k]): O(log n)
ll query(int node, int start, int end, int k) {
    push(node, start, end); // Always push before processing
    if (start == end) {
        return tree[node];
    }

    int mid = (start + end) / 2;
    if (k <= mid)
        return query(2 * node, start, mid, k);
    else
        return query(2 * node + 1, mid + 1, end, k);
}

int main() {
    // Optimize I/O operations
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) cin >> arr[i];

    build(arr, 1, 1, n);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int a, b, u;
            cin >> a >> b >> u;
            update(1, 1, n, a, b, u);
        } else {
            int k;
            cin >> k;
            cout << query(1, 1, n, k) << "\n";
        }
    }

    return 0;
}