#include <iostream>
#include <vector>
#include <cmath>
#include <numeric> // for std::iota
#include <map> // To map cycle entry node to cycle ID and size
#include <algorithm> // for std::fill

// Maximum number of planets and queries
const int MAXN = 200005;
// Maximum power of 2 for binary lifting (ceil(log2(MAXN)))
const int LOGN = 18;

// t[i]: the planet reached from planet i by teleporter (0-indexed)
std::vector<int> t(MAXN);
// up[i][k]: the planet reached from planet i after 2^k teleportations
int up[MAXN][LOGN];
// dist_to_cycle[i]: the number of steps from planet i to the first node in its cycle
int dist_to_cycle[MAXN];
// cycle_node[i]: a representative node in the cycle that planet i reaches
int cycle_node[MAXN];
// cycle_id[i]: a unique identifier for the cycle that planet i belongs to or reaches
int cycle_id[MAXN];
// cycle_pos[i]: the position of planet i within its cycle (0-indexed within the cycle)
int cycle_pos[MAXN];
// visited[i]: state of planet i during DFS (0: unvisited, 1: visiting, 2: visited)
int visited[MAXN];
// path_stack: used during DFS to detect cycles in the current path
std::vector<int> path_stack;
// current_cycle_id: counter for assigning unique IDs to cycles
int current_cycle_id = 0;
// cycle_info: map from a cycle's representative node to its {cycle_id, cycle_size}
std::map<int, std::pair<int, int>> cycle_info;


// Function to move k steps forward from a start node using binary lifting
int move_k_steps(int start_node, int k) {
    int curr = start_node;
    // Iterate through powers of 2 from largest to smallest
    for (int i = LOGN - 1; i >= 0; --i) {
        // If the i-th bit of k is set, move 2^i steps
        if (k & (1 << i)) {
            curr = up[curr][i];
        }
    }
    return curr;
}

// DFS function to detect cycles and compute path-to-cycle information
void dfs(int u) {
    visited[u] = 1; // Mark node u as visiting (currently in the recursion stack)
    path_stack.push_back(u); // Add u to the current path stack

    int v = t[u]; // The next planet from u

    if (visited[v] == 1) { // If the next planet v is currently visiting, a cycle is detected
        current_cycle_id++; // Increment cycle ID for the new cycle
        int cycle_start_index = -1;
        // Find the index of node v in the current path stack (where the cycle starts)
        for (int i = 0; i < path_stack.size(); ++i) {
            if (path_stack[i] == v) {
                cycle_start_index = i;
                break;
            }
        }

        int cycle_size = path_stack.size() - cycle_start_index; // Calculate the size of the cycle
        cycle_info[v] = {current_cycle_id, cycle_size}; // Store cycle information with v as a representative

        // Process nodes within the detected cycle
        for (int i = cycle_start_index; i < path_stack.size(); ++i) {
            int node = path_stack[i];
            cycle_id[node] = current_cycle_id; // Assign the cycle ID
            cycle_node[node] = v; // Set the cycle representative node
            cycle_pos[node] = i - cycle_start_index; // Set the position within the cycle
            dist_to_cycle[node] = 0; // Nodes in the cycle are 0 steps away from the cycle
            visited[node] = 2; // Mark nodes in the cycle as fully visited
        }

        // Process transient nodes leading to this cycle
        for (int i = cycle_start_index - 1; i >= 0; --i) {
            int node = path_stack[i];
            cycle_id[node] = current_cycle_id; // Assign the same cycle ID
            cycle_node[node] = v; // Set the same cycle representative node
            dist_to_cycle[node] = cycle_start_index - i; // Distance to the cycle
            visited[node] = 2; // Mark as fully visited
        }

    } else if (visited[v] == 0) { // If the next planet v is unvisited, continue DFS
        dfs(v); // Recurse on v

        // After returning from the recursive call, if u is still marked as visiting (meaning it's
        // not part of a cycle found deeper in the recursion)
        if (visited[u] == 1) {
             // u is a transient node leading to a component/cycle that was fully processed by the recursive call
             cycle_id[u] = cycle_id[v]; // Inherit cycle info from v
             cycle_node[u] = cycle_node[v];
             dist_to_cycle[u] = dist_to_cycle[v] + 1; // u is one step further from the cycle than v
             visited[u] = 2; // Mark u as fully visited
        }

    } else { // visited[v] == 2, the next planet v is already fully processed and belongs to a cycle
        // The current path from u leads to an already identified component/cycle
        cycle_id[u] = cycle_id[v]; // Inherit cycle info from v
        cycle_node[u] = cycle_node[v];
        dist_to_cycle[u] = dist_to_cycle[v] + 1; // u is one step further from the cycle than v
        visited[u] = 2; // Mark u as fully visited
    }

    // Remove u from the path stack after processing it (either cycle found or path determined)
    if (!path_stack.empty() && path_stack.back() == u) {
        path_stack.pop_back();
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    std::cin >> n >> q;

    // Read teleporter destinations (adjusting to 0-indexed)
    for (int i = 0; i < n; ++i) {
        std::cin >> t[i];
        t[i]--; // Adjust to 0-indexed (planets 1 to n become 0 to n-1)
    }

    // Initialize binary lifting table for 2^0 steps (direct teleporter)
    for (int i = 0; i < n; ++i) {
        up[i][0] = t[i];
    }

    // Compute binary lifting table for 2^k steps
    for (int k = 1; k < LOGN; ++k) {
        for (int i = 0; i < n; ++i) {
            up[i][k] = up[up[i][k-1]][k-1];
        }
    }

    // Initialize visited array to 0 (unvisited)
    std::fill(visited, visited + n, 0);

    // Perform DFS from each unvisited node to find components and cycles
    for (int i = 0; i < n; ++i) {
        if (visited[i] == 0) {
            path_stack.clear(); // Clear path stack for each new component exploration
            dfs(i);
        }
    }

    // Process queries
    for (int i = 0; i < q; ++i) {
        int a, b;
        std::cin >> a >> b;
        a--; // Adjust to 0-indexed
        b--; // Adjust to 0-indexed

        // Check if starting planet 'a' and destination planet 'b' are in the same component
        // (i.e., they reach the same cycle)
        if (cycle_id[a] != cycle_id[b]) {
            std::cout << -1 << std::endl; // Not reachable if in different components
            continue;
        }

        // Case 1: a and b are in the same component
        // Check if b is in the transient part reachable from a before a enters its cycle
        if (dist_to_cycle[a] >= dist_to_cycle[b]) {
            // If a is further from or at the same distance to the cycle as b,
            // b could be in the transient path from a to the cycle.
            int steps_needed = dist_to_cycle[a] - dist_to_cycle[b];
            // Move 'a' forward by the calculated number of steps
            if (move_k_steps(a, steps_needed) == b) {
                std::cout << steps_needed << std::endl; // If it reaches b, this is the minimum distance
            } else {
                // If moving that many steps doesn't reach b, it means b is not in the transient
                // path from a before a enters the cycle. This can only happen if b is in the cycle.
                // Fall through to the cycle handling case.
                 goto handle_cycle_case; // Use goto to jump to cycle handling logic
            }
        } else { // dist_to_cycle[a] < dist_to_cycle[b]
             // If a is closer to the cycle than b, b cannot be in the transient part
             // reachable from a before a enters the cycle. b must be in the cycle.
             handle_cycle_case:; // Label for the cycle handling case

             // Move 'a' forward to the node where it enters its cycle
             int a_cycle_entry = move_k_steps(a, dist_to_cycle[a]);

             // If b is in the cycle (a node in the cycle has dist_to_cycle == 0)
             if (dist_to_cycle[b] == 0) {
                 // Find the representative node of the cycle (can be any node in the cycle)
                 int cycle_entry_node_of_a = cycle_node[a];
                 // Get the size of the cycle from the stored info
                 int cycle_size = cycle_info[cycle_entry_node_of_a].second;

                 // Get the positions of a's cycle entry and b within the cycle
                 int pos_a_cycle = cycle_pos[a_cycle_entry];
                 int pos_b_cycle = cycle_pos[b];

                 // Calculate the number of steps needed to get from a's cycle entry to b within the cycle
                 int steps_within_cycle;
                 if (pos_b_cycle >= pos_a_cycle) {
                     steps_within_cycle = pos_b_cycle - pos_a_cycle;
                 } else {
                     // Wrap around the cycle
                     steps_within_cycle = (cycle_size - pos_a_cycle) + pos_b_cycle;
                 }
                 // Total distance is steps to reach cycle + steps within cycle
                 std::cout << dist_to_cycle[a] + steps_within_cycle << std::endl;

             } else {
                 // If dist_to_cycle[a] < dist_to_cycle[b] and b is *not* in the cycle,
                 // and they are in the same component, it means b is further from the cycle than a.
                 // a will reach the cycle first. b cannot be reached from a's transient path.
                 // b is unreachable from a in this scenario.
                 std::cout << -1 << std::endl;
             }
        }
    }

    return 0;
}
