#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
const int LOG = 20;

int t[MAXN];                // Teleporter destination
int up[MAXN][LOG];          // Binary lifting table
vector<int> adj_rev[MAXN];  // Reverse graph for BFS
bool visited[MAXN];         // Visited array for cycle detection
bool in_cycle[MAXN];        // Is node in cycle?

// Cycle info
int cycle_id[MAXN];         // ID of the cycle the node belongs to (or leads to)
int cycle_pos[MAXN];        // Position index in the cycle
int cycle_len[MAXN];        // Length of the cycle
int dist_to_cycle[MAXN];    // Distance to the cycle
int root[MAXN];             // The entry point node to the cycle

// Jump k steps using binary lifting
int jump(int x, int k) {
    for (int i = 0; i < LOG; i++) {
        if ((k >> i) & 1) {
            x = up[x][i];
        }
    }
    return x;
}

void bfs_tree_depth(int n) {
    queue<int> q;
    // Initialize BFS with all cycle nodes
    for (int i = 1; i <= n; i++) {
        if (in_cycle[i]) {
            dist_to_cycle[i] = 0;
            root[i] = i; // Root of a cycle node is itself
            q.push(i);
        } else {
            dist_to_cycle[i] = -1; // Mark as unvisited
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj_rev[u]) {
            if (dist_to_cycle[v] == -1) { // If not visited
                dist_to_cycle[v] = dist_to_cycle[u] + 1;
                root[v] = root[u];      // Propagate the cycle entry point
                cycle_id[v] = cycle_id[root[v]]; // Propagate cycle ID
                q.push(v);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    // 1. Input & Binary Lifting Setup
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        up[i][0] = t[i];
        adj_rev[t[i]].push_back(i); // Build reverse graph
    }

    // Build full binary lifting table
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }

    // 2. Cycle Detection
    int current_cycle_id = 0;
    vector<int> path_vis(n + 1, 0); // 0: unvisited, 1: visiting, 2: visited in previous DFS
    
    // We use an iterative approach to find cycles to avoid stack overflow
    for (int i = 1; i <= n; i++) {
        if (visited[i]) continue;
        
        int curr = i;
        vector<int> path;
        
        while (!visited[curr]) {
            visited[curr] = true;
            path.push_back(curr);
            curr = t[curr];
        }

        // Check if we hit a node in the current path (Cycle detected)
        bool cycle_found = false;
        int cycle_start_index = -1;
        
        // Is 'curr' in 'path'?
        // Note: In a functional graph, if we hit a visited node, either it's part of the current path (cycle)
        // or it's part of a previously processed component.
        // We need to check if 'curr' is actually part of the newly discovered cycle.
        // A simple way is to check if 'curr' is processed or if it's new.
        // But since we use 'visited' globally, we need to be careful.
        // Let's re-verify: 'curr' is the first node we encountered that was ALREADY visited.
        
        // We can check if 'curr' is part of the current path component.
        // The simplest way for functional graphs:
        // Walk again from 'curr' to see if we return to 'curr'. If yes, it's a cycle.
        // But we need to label the path correctly.
        
        // Optimization: Let's use the 'path' vector.
        for(size_t k=0; k<path.size(); ++k) {
            if (path[k] == curr) {
                cycle_found = true;
                cycle_start_index = k;
                break;
            }
        }

        if (cycle_found) {
            current_cycle_id++;
            int len = path.size() - cycle_start_index;
            for (size_t k = cycle_start_index; k < path.size(); k++) {
                int node = path[k];
                in_cycle[node] = true;
                cycle_id[node] = current_cycle_id;
                cycle_pos[node] = k - cycle_start_index;
                cycle_len[node] = len;
            }
        }
    }

    // 3. BFS to calculate distances to cycle for tree nodes
    bfs_tree_depth(n);

    // 4. Process Queries
    while (q--) {
        int a, b;
        cin >> a >> b;

        // If 'a' and 'b' lead to different cycles, impossible.
        // Note: cycle_id is propagated to tree nodes in BFS.
        // If roots are in different cycles, impossible.
        if (cycle_id[root[a]] != cycle_id[root[b]]) {
            cout << -1 << "\n";
            continue;
        }

        if (in_cycle[b]) {
            // Case: Target is in cycle
            // 'a' must be able to reach this cycle (checked above via cycle_id).
            int dist = dist_to_cycle[a];
            int entry = root[a];
            // Add distance on cycle
            int diff = (cycle_pos[b] - cycle_pos[entry] + cycle_len[entry]) % cycle_len[entry];
            cout << dist + diff << "\n";
        } else {
            // Case: Target is in tree (not in cycle)
            // 'a' must be in the same tree branch and 'above' 'b'.
            // condition: root[a] == root[b] AND dist_to_cycle[a] >= dist_to_cycle[b]
            if (root[a] != root[b] || dist_to_cycle[a] < dist_to_cycle[b]) {
                cout << -1 << "\n";
            } else {
                int dist = dist_to_cycle[a] - dist_to_cycle[b];
                // Check if jumping 'dist' steps from 'a' lands us on 'b'
                if (jump(a, dist) == b) {
                    cout << dist << "\n";
                } else {
                    cout << -1 << "\n";
                }
            }
        }
    }

    return 0;
}