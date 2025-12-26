#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
int tree[4 * MAXN];
int n;

// Build the tree: Each node stores the MAX of its range
void build(const vector<int>& arr, int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    build(arr, 2 * node, start, mid);
    build(arr, 2 * node + 1, mid + 1, end);
    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
}

// Walk down the tree to find the first hotel with >= rooms
int find_and_update(int node, int start, int end, int rooms) {
    // If root max is less than required, return 0
    if (tree[node] < rooms) return 0;

    // Base case: Leaf node found
    if (start == end) {
        tree[node] -= rooms; // Assign the rooms
        return start;        // Return hotel index
    }

    int mid = (start + end) / 2;
    int res;
    
    // Priority: Try the left child first (to find the FIRST hotel)
    if (tree[2 * node] >= rooms) {
        res = find_and_update(2 * node, start, mid, rooms);
    } else {
        res = find_and_update(2 * node + 1, mid + 1, end, rooms);
    }

    // After updating a leaf, update the current node's maximum
    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int m;
    cin >> n >> m;
    vector<int> h(n + 1);
    for (int i = 1; i <= n; i++) cin >> h[i];

    build(h, 1, 1, n);

    for (int i = 0; i < m; i++) {
        int rooms;
        cin >> rooms;
        // Find, update, and print result in O(log n)
        cout << find_and_update(1, 1, n, rooms) << (i == m - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}