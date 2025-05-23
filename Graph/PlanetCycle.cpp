#include <iostream>
#include <vector>
#include <numeric> // for std::iota
#include <algorithm> // for std::fill

// Maximum number of planets
const int MAXN = 200005;

// t[i]: the planet reached from planet i by teleporter (0-indexed)
std::vector<int> t(MAXN);
// ans[i]: the number of teleportations starting from planet i until a previously visited planet is reached
std::vector<int> ans(MAXN);
// visited[i]: state of planet i during DFS (0: unvisited, 1: visiting, 2: finished)
std::vector<int> visited(MAXN, 0);
// step_in_path[i]: the step number of planet i within the current DFS path (used for cycle detection)
// Initialized to -1 to indicate not in the current path.
std::vector<int> step_in_path(MAXN, -1);
// path_nodes_vec: stores nodes in the current DFS path being explored
std::vector<int> path_nodes_vec;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    // Read teleporter destinations (adjusting to 0-indexed)
    for (int i = 0; i < n; ++i) {
        std::cin >> t[i];
        t[i]--; // Adjust to 0-indexed (planets 1 to n become 0 to n-1)
    }

    // Perform DFS from each unvisited node to find component structure and calculate answers
    // We iterate through all nodes to ensure all components of the functional graph are processed.
    for (int i = 0; i < n; ++i) {
        // If the planet 'i' has not been visited yet, start a new traversal from it.
        if (visited[i] == 0) {
            path_nodes_vec.clear(); // Clear path vector for each new component exploration
            
            int current_node = i;
            int steps = 0;

            // Traverse from 'i' until a visited node is encountered.
            while (visited[current_node] == 0) {
                visited[current_node] = 1; // Mark the current node as visiting (in the current path)
                path_nodes_vec.push_back(current_node); // Add the node to the current path stack
                step_in_path[current_node] = steps; // Record the step number to reach this node in the current path
                current_node = t[current_node]; // Move to the next planet
                steps++; // Increment step count
            }

            // Now `current_node` is either visited (state 1, meaning a cycle is detected in the current path)
            // or finished (state 2, meaning the path reached a node in a previously processed component).

            if (visited[current_node] == 1) { // Case 1: Cycle detected in the current path
                // `current_node` is the first repeated node, which is the entry point into the cycle.
                int cycle_entry_node = current_node;
                int cycle_entry_step = step_in_path[cycle_entry_node]; // Step number where the cycle entry was first visited in this path
                int cycle_length = steps - cycle_entry_step; // The length of the cycle

                // Calculate answers for all nodes in the current path (both transient and cycle parts)
                for (int node : path_nodes_vec) {
                    if (step_in_path[node] >= cycle_entry_step) {
                        // If the node's step number is greater than or equal to the cycle entry step,
                        // the node is part of the cycle.
                        // The number of steps from a node in the cycle until a previously visited node
                        // is reached is simply the length of the cycle.
                        ans[node] = cycle_length;
                    } else {
                        // If the node's step number is less than the cycle entry step,
                        // the node is in the transient part leading to the cycle.
                        // The number of steps from this node to reach a previously visited node
                        // is the distance from this node to the cycle entry node, plus the cycle length.
                        // Distance from 'node' to 'cycle_entry_node' = step_in_path[cycle_entry_node] - step_in_path[node].
                        // Total steps = (distance to cycle entry) + cycle length.
                        ans[node] = (cycle_entry_step - step_in_path[node]) + cycle_length;
                    }
                    visited[node] = 2; // Mark the node as fully finished processing
                    step_in_path[node] = -1; // Reset step_in_path for this node for future traversals (if any, though not needed with visited[2])
                }

            } else if (visited[current_node] == 2) { // Case 2: Reached a node that was already processed and its answer is known
                // The current path leads to a node `current_node` that belongs to a previously identified
                // and fully processed component (either another cycle or a path leading to a cycle).
                // The answer for `current_node` (steps from `current_node` to its first repeat) is already
                // stored in `ans[current_node]`.

                // Calculate answers for all nodes in the current path leading to `current_node`.
                for (int node : path_nodes_vec) {
                    // The number of steps from 'node' to reach a previously visited node is:
                    // the distance from 'node' to `current_node`, plus the number of steps from `current_node`
                    // until *its* first repeated node is reached (which is `ans[current_node]`).
                    // Distance from 'node' to `current_node` = total steps taken in this path to reach `current_node` - step number of 'node' in this path.
                    // Distance from 'node' to `current_node` = `steps` - `step_in_path[node]`.
                    // Total steps = (distance from 'node' to `current_node`) + `ans[current_node]`.
                    ans[node] = (steps - step_in_path[node]) + ans[current_node];
                    visited[node] = 2; // Mark the node as fully finished processing
                    step_in_path[node] = -1; // Reset step_in_path for this node
                }
            }
        }
    }

    // Print the results for each planet (adjusting back to 1-indexed output)
    for (int i = 0; i < n; ++i) {
        std::cout << ans[i] << (i == n - 1 ? "" : " "); // Print space after each number except the last one
    }
    std::cout << std::endl;

    return 0;
}
