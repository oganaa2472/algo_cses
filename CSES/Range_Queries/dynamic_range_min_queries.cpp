#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Large value for out-of-bounds queries
const int INF = 1e9 + 7;

vector<int> tree;
int n;

// Build the tree: O(n)
void build(const vector<int>& arr, int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    build(arr, 2 * node, start, mid);
    build(arr, 2 * node + 1, mid + 1, end);
    // Store the minimum of the two children
    tree[node] = min(tree[2 * node], tree[2 * node + 1]);
}

// Update value at position k to u: O(log n)
void update(int node, int start, int end, int k, int u) {
    if (start == end) {
        tree[node] = u;
        return;
    }
    int mid = (start + end) / 2;
    if (k <= mid) 
        update(2 * node, start, mid, k, u);
    else 
        update(2 * node + 1, mid + 1, end, k, u);
    
    // Recompute minimum after child update
    tree[node] = min(tree[2 * node], tree[2 * node + 1]);
}

// Query the minimum in range [l, r]: O(log n)
int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return INF; // Return INF so it doesn't affect min()
    if (l <= start && end <= r) return tree[node];
    
    int mid = (start + end) / 2;
    return min(query(2 * node, start, mid, l, r),
               query(2 * node + 1, mid + 1, end, l, r));
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int q;
    cin >> n >> q;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) cin >> arr[i];
    
    tree.assign(4 * n + 1, INF);
    build(arr, 1, 1, n);
    
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k, u;
            cin >> k >> u;
            update(1, 1, n, k, u);
        } else {
            int a, b;
            cin >> a >> b;
            cout << query(1, 1, n, a, b) << "\n";
        }
    }
    
    return 0;
}