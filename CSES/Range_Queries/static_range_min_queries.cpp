#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Using a large value for infinity (larger than any xi)
const int INF = 1e9 + 7;

vector<int> tree;
int n;

// Build the Segment Tree: O(n)
void build(const vector<int>& arr, int node, int start, int end) {
    if (start == end) {
        // Leaf node stores the array element
        tree[node] = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    // Recursively build left and right children
    build(arr, 2 * node, start, mid);
    build(arr, 2 * node + 1, mid + 1, end);
    // Internal node stores the minimum of its children
    tree[node] = min(tree[2 * node], tree[2 * node + 1]);
}

// Query the minimum in range [l, r]: O(log n)
int query(int node, int start, int end, int l, int r) {
    // Case 1: Range is completely outside [l, r]
    if (r < start || end < l) {
        return INF; 
    }
    // Case 2: Range is completely inside [l, r]
    if (l <= start && end <= r) {
        return tree[node];
    }
    // Case 3: Range is partially inside
    int mid = (start + end) / 2;
    return min(query(2 * node, start, mid, l, r),
               query(2 * node + 1, mid + 1, end, l, r));
}

int main() {
    // Fast I/O is mandatory for large input
    ios::sync_with_stdio(0);
    cin.tie(0);

    int q;
    if (!(cin >> n >> q)) return 0;

    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    // Initialize tree with 4 * n space
    tree.assign(4 * n + 1, INF);
    build(arr, 1, 1, n);

    while (q--) {
        int a, b;
        cin >> a >> b;
        // Output the minimum in range [a, b]
        cout << query(1, 1, n, a, b) << "\n";
    }

    return 0;
}