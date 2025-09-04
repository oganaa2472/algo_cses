#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <map> // Using a map to simulate Segment Tree for simplicity
               // A full Segment Tree implementation would be more efficient
               // but the logic is the same.
               // We will implement a full Segment Tree below.

// --- Segment Tree Implementation ---
using namespace std;
class SegmentTree {
private:
    std::vector<int> tree;
    int n;

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = 0; // Initialize with no visible buildings
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 0;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int p1 = query(2 * node, start, mid, l, r);
        int p2 = query(2 * node + 1, mid + 1, end, l, r);
        return p1 + p2;
    }

public:
    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n, 0);
        build(1, 1, n);
    }

    void update(int idx, int val) {
        update(1, 1, n, idx, val);
    }

    int query(int l, int r) {
        if (l > r) return 0;
        return query(1, 1, n, l, r);
    }
};

struct Query {
    int a, b, index;
};



int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> h(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> h[i];
    }

    // Store queries grouped by their right endpoint 'b'
    std::vector<std::vector<std::pair<int, int>>> queries_by_b(n + 1);
    for (int i = 0; i < q; ++i) {
        int a, b;
        std::cin >> a >> b;
        queries_by_b[b].push_back({a, i});
    }

    // Main offline processing logic
    SegmentTree st(n);
    std::vector<int> ans(q);
    std::stack<int> s;

    for (int i = 1; i <= n; ++i) {
        // While the stack is not empty and the current building is taller than or equal to the top
        // Pop the buildings from the stack.
        // These buildings are now hidden by the current building 'i'.
        // Mark them as not visible (0) in the Segment Tree.
        while (!s.empty() && h[s.top()] <= h[i]) {
            st.update(s.top(), 0);
            s.pop();
        }

        // The current building 'i' is now visible relative to anything left on the stack.
        // Mark it as visible (1) in the Segment Tree.
        st.update(i, 1);
        s.push(i);

        // Process all queries with right endpoint 'b' equal to 'i'
        for (const auto& query_pair : queries_by_b[i]) {
            int a = query_pair.first;
            int query_index = query_pair.second;

            // The answer is the sum of visible buildings in the range [a, i].
            // The Segment Tree gives us this sum.
            ans[query_index] = st.query(a, i);
        }
    }

    // Print results
    for (int i = 0; i < q; ++i) {
        std::cout << ans[i] << "\n";
    }

    return 0;
}