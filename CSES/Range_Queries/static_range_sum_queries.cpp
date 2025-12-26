#include <iostream>
#include <vector>

using namespace std;

// Using long long because the sum can exceed 2^31 - 1
typedef long long ll;

vector<ll> tree;
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
    // The sum of the parent is the sum of its two children
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Query the sum in range [l, r]: O(log n)
ll query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return 0; // Outside range: sum is 0
    if (l <= start && end <= r) return tree[node]; // Completely inside
    
    int mid = (start + end) / 2;
    return query(2 * node, start, mid, l, r) + 
           query(2 * node + 1, mid + 1, end, l, r);
}

int main() {
    // Fast I/O is critical for 200,000 queries
    ios::sync_with_stdio(0); cin.tie(0);
    
    int q;
    if (!(cin >> n >> q)) return 0;
    
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) cin >> arr[i];
    
    // Size the tree to 4 * n
    tree.assign(4 * n + 1, 0);
    build(arr, 1, 1, n);
    
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << query(1, 1, n, a, b) << "\n";
    }
    
    return 0;
}