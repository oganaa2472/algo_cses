#include <iostream>
#include <vector>
#include <algorithm> // For std::min
#include <limits>    // For std::numeric_limits

// Define a large value to represent infinity for minimum queries
const long long INF = std::numeric_limits<long long>::max();

// Global variables for segment trees and prices
std::vector<long long> p; // Stores current pizza prices (1-indexed for convenience)
std::vector<long long> tree1; // Segment tree for (p_i + i)
std::vector<long long> tree2; // Segment tree for (p_i - i)
int N; // Number of buildings

// --- Segment Tree Helper Functions ---

// Builds a segment tree
// node: current node in the tree array
// start: start index of the segment this node represents
// end: end index of the segment this node represents
// val_arr: the underlying array (either p_i + i or p_i - i)
// tree_arr: the segment tree array to build (tree1 or tree2)
void build(int node, int start, int end, const std::vector<long long>& val_arr, std::vector<long long>& tree_arr) {
    if (start == end) {
        // Leaf node: store the value from the underlying array
        tree_arr[node] = val_arr[start];
    } else {
        int mid = (start + end) / 2;
        // Recursively build left and right children
        build(2 * node, start, mid, val_arr, tree_arr);
        build(2 * node + 1, mid + 1, end, val_arr, tree_arr);
        // Internal node: store the minimum of its children
        tree_arr[node] = std::min(tree_arr[2 * node], tree_arr[2 * node + 1]);
    }
}

// Updates a value in a segment tree
// node: current node
// start, end: segment range of current node
// idx: index in the original array to update
// new_val: the new value at idx
// tree_arr: the segment tree array to update
void update(int node, int start, int end, int idx, long long new_val, std::vector<long long>& tree_arr) {
    if (start == end) {
        // Leaf node: update its value
        tree_arr[node] = new_val;
    } else {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            // idx is in the left child's range
            update(2 * node, start, mid, idx, new_val, tree_arr);
        } else {
            // idx is in the right child's range
            update(2 * node + 1, mid + 1, end, idx, new_val, tree_arr);
        }
        // After children are updated, update the current node
        tree_arr[node] = std::min(tree_arr[2 * node], tree_arr[2 * node + 1]);
    }
}

// Queries the minimum value in a given range [L, R]
// node: current node
// start, end: segment range of current node
// L, R: query range
// tree_arr: the segment tree to query
long long query(int node, int start, int end, int L, int R, const std::vector<long long>& tree_arr) {
    // Case 1: Current segment is completely outside the query range
    if (R < start || end < L) {
        return INF; // Return infinity as it won't affect the minimum
    }
    // Case 2: Current segment is completely inside the query range
    if (L <= start && end <= R) {
        return tree_arr[node];
    }
    // Case 3: Partial overlap, recurse on children
    int mid = (start + end) / 2;
    long long p1 = query(2 * node, start, mid, L, R, tree_arr);
    long long p2 = query(2 * node + 1, mid + 1, end, L, R, tree_arr);
    return std::min(p1, p2);
}

// --- Main Logic ---

int main() {
    // Optimize C++ standard streams for faster input/output
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int Q; // Number of queries
    std::cin >> N >> Q;

    // Resize global vectors. We'll use 1-based indexing for buildings (1 to N).
    // Segment trees typically need 4*N size to avoid issues.
    p.resize(N + 1);
    tree1.resize(4 * N + 4);
    tree2.resize(4 * N + 4);

    // Temporary vectors to hold initial p_i+i and p_i-i values
    std::vector<long long> initial_val1(N + 1);
    std::vector<long long> initial_val2(N + 1);

    // Read initial pizza prices and populate initial_val1/val2
    for (int i = 1; i <= N; ++i) {
        std::cin >> p[i];
        initial_val1[i] = p[i] + i;
        initial_val2[i] = p[i] - i;
    }

    // Build both segment trees
    build(1, 1, N, initial_val1, tree1);
    build(1, 1, N, initial_val2, tree2);

    // Process queries
    for (int q = 0; q < Q; ++q) {
        int type;
        std::cin >> type;

        if (type == 1) {
            // Type 1 Query: 1 k x (Update price p_k to x)
            int k;
            long long x;
            std::cin >> k >> x;

            // Update the current price in our p array
            p[k] = x;

            // Update both segment trees
            // Segment Tree 1: p_k + k
            update(1, 1, N, k, p[k] + k, tree1);
            // Segment Tree 2: p_k - k
            update(1, 1, N, k, p[k] - k, tree2);

        } else {
            // Type 2 Query: 2 k (Find minimum price from building k)
            int k;
            std::cin >> k;

            long long min_cost = INF;

            // Calculate minimum cost for ordering from a >= k
            // Query segment tree 1 for range [k, N]
            long long min_val_right = query(1, 1, N, k, N, tree1);
            if (min_val_right != INF) { // Ensure a valid minimum was found
                min_cost = std::min(min_cost, min_val_right - k);
            }

            // Calculate minimum cost for ordering from a < k
            // Query segment tree 2 for range [1, k-1]
            // Handle edge case where k=1 (range [1,0] is empty)
            if (k > 1) {
                long long min_val_left = query(1, 1, N, 1, k - 1, tree2);
                if (min_val_left != INF) { // Ensure a valid minimum was found
                    min_cost = std::min(min_cost, min_val_left + k);
                }
            }
            
            std::cout << min_cost << "\n";
        }
    }

    return 0;
}