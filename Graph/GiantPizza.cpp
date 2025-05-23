#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <vector>

std::vector<std::vector<int>> adj; // Adjacency list for the implication graph
std::vector<std::vector<int>> rev_adj; // Adjacency list for the reversed graph
std::vector<bool> visited; // Visited array for DFS
std::vector<int> order; // Stores nodes in decreasing order of finish times (Pass 1)
std::vector<int> scc_id; // Stores the SCC ID for each node
int current_scc_id; // Counter for assigning SCC IDs

// DFS for the first pass of Kosaraju's algorithm (on original graph)
void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs1(v);
        }
    }
    order.push_back(u); // Add node to order after visiting all its neighbors
}

// DFS for the second pass of Kosaraju's algorithm (on reversed graph)
void dfs2(int u) {
    visited[u] = true;
    scc_id[u] = current_scc_id; // Assign the current SCC ID
    for (int v : rev_adj[u]) {
        if (!visited[v]) {
            dfs2(v);
        }
    }
}

// Helper function to get the node index for a literal
// "+ x" -> x-1
// "- x" -> (x-1) + m
int get_node(char sign, int topping_idx, int m) {
    if (sign == '+') {
        return topping_idx - 1; // Node for p_x
    } else {
        return (topping_idx - 1) + m; // Node for not p_x
    }
}

// Helper function to get the node index for the negation of a literal
// "+ x" -> node for "- x" -> (x-1) + m
// "- x" -> node for "+ x" -> x-1
int get_negation_node(char sign, int topping_idx, int m) {
    if (sign == '+') {
        return (topping_idx - 1) + m; // Node for not p_x
    } else {
        return topping_idx - 1; // Node for p_x
    }
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    std::cin >> n >> m; // n: family members, m: toppings

    // The implication graph has 2*m nodes: 0..m-1 for p_1..p_m, m..2m-1 for not p_1..not p_m
    adj.resize(2 * m);
    rev_adj.resize(2 * m);

    // Read wishes and build the implication graph
    for (int i = 0; i < n; ++i) {
        char sign1, sign2;
        int topping1, topping2;
        std::cin >> sign1 >> topping1 >> sign2 >> topping2;

        // Clause is (L1 or L2)
        // Equivalent to (not L1 => L2) and (not L2 => L1)

        // Literal 1:
        int u1 = get_node(sign1, topping1, m);
        int neg_u1 = get_negation_node(sign1, topping1, m);

        // Literal 2:
        int u2 = get_node(sign2, topping2, m);
        int neg_u2 = get_negation_node(sign2, topping2, m);

        // Add edges: (not L1 => L2) and (not L2 => L1)
        adj[neg_u1].push_back(u2);
        rev_adj[u2].push_back(neg_u1);

        adj[neg_u2].push_back(u1);
        rev_adj[u1].push_back(neg_u2);
    }

    // --- Kosaraju's Algorithm ---

    // Pass 1: DFS on original graph to compute finish times
    visited.assign(2 * m, false);
    order.clear();
    for (int i = 0; i < 2 * m; ++i) {
        if (!visited[i]) {
            dfs1(i);
        }
    }
    std::reverse(order.begin(), order.end()); // Reverse to get decreasing order of finish times

    // Pass 2: DFS on reversed graph to find SCCs
    visited.assign(2 * m, false);
    scc_id.assign(2 * m, -1);
    current_scc_id = 0;
    for (int u : order) {
        if (!visited[u]) {
            dfs2(u);
            current_scc_id++; // Increment SCC ID for the next component
        }
    }

    // --- Check for Impossibility and Construct Solution ---

    std::string result = "";
    bool possible = true;

    for (int i = 0; i < m; ++i) { // Iterate through each topping (0-indexed)
        int p_node = i; // Node for p_{i+1}
        int neg_p_node = i + m; // Node for not p_{i+1}

        if (scc_id[p_node] == scc_id[neg_p_node]) {
            // If a variable and its negation are in the same SCC, it's impossible
            possible = false;
            break;
        }

        // Construct the assignment based on SCC IDs
        // If SCC(p_x) has a lower ID, it's later in reverse topological order -> p_x must be true
        // If SCC(not p_x) has a lower ID, it's later in reverse topological order -> p_x must be false
        if (scc_id[p_node] < scc_id[neg_p_node]) {
            result += '+'; // Topping i+1 is included
        } else {
            result += '-'; // Topping i+1 is not included
        }
    }

    if (possible) {
        std::cout << result << std::endl;
    } else {
        std::cout << "IMPOSSIBLE" << std::endl;
    }

    return 0;
}
