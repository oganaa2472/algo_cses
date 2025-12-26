#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200005;
int tree[4 * MAXN];
int n;

// Build the tree: initially, every position has 1 element (it's "alive")
void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = 1;
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Walk the tree to find the p-th "alive" element and set it to 0
int find_and_remove(int node, int start, int end, int p) {
    if (start == end) {
        tree[node] = 0; // Mark as removed
        return start;   // Return the original index
    }
    
    int mid = (start + end) / 2;
    int res;
    
    // If the left child has at least p alive elements, go left
    if (tree[2 * node] >= p) {
        res = find_and_remove(2 * node, start, mid, p);
    } else {
        // Otherwise, go right, but subtract the count of left-side elements
        res = find_and_remove(2 * node + 1, mid + 1, end, p - tree[2 * node]);
    }
    
    // Update the parent's count of alive elements
    tree[node] = tree[2 * node] + tree[2 * node + 1];
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    vector<int> x(n + 1);
    for (int i = 1; i <= n; i++) cin >> x[i];

    build(1, 1, n);

    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        // Find the original index of the current p-th element
        int original_idx = find_and_remove(1, 1, n, p);
        cout << x[original_idx] << (i == n - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}