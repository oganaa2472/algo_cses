#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct Node {
    ll sum;
    ll max_pref;
};

// Merge logic to combine two segments
Node merge(Node l, Node r) {
    return {l.sum + r.sum, max(l.max_pref, l.sum + r.max_pref)};
}

const int MAXN = 200005;
Node tree[4 * MAXN];
int n;

void build(const vector<int>& arr, int node, int start, int end) {
    if (start == end) {
        tree[node] = {arr[start], max(0LL, (ll)arr[start])};
        return;
    }
    int mid = (start + end) / 2;
    build(arr, 2 * node, start, mid);
    build(arr, 2 * node + 1, mid + 1, end);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

void update(int node, int start, int end, int k, int u) {
    if (start == end) {
        tree[node] = {u, max(0LL, (ll)u)};
        return;
    }
    int mid = (start + end) / 2;
    if (k <= mid) update(2 * node, start, mid, k, u);
    else update(2 * node + 1, mid + 1, end, k, u);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

Node query(int node, int start, int end, int l, int r) {
    // If the node range is exactly the query range
    if (l <= start && end <= r) return tree[node];
    
    int mid = (start + end) / 2;
    // If query is entirely in the left child
    if (r <= mid) return query(2 * node, start, mid, l, r);
    // If query is entirely in the right child
    if (l > mid) return query(2 * node + 1, mid + 1, end, l, r);
    
    // Otherwise, query both and merge results
    return merge(query(2 * node, start, mid, l, r),
                 query(2 * node + 1, mid + 1, end, l, r));
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int q;
    cin >> n >> q;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) cin >> arr[i];

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
            cout << query(1, 1, n, a, b).max_pref << "\n";
        }
    }
    return 0;
}