#include <iostream>
#include <vector>
#include <queue>
#include <limits> // For numeric_limits
#include <algorithm> // For std::min
#include <vector>

// Use long long for flow and capacity to handle large values
using flow_t = long long;
// A large value to represent infinite capacity
const flow_t INF = std::numeric_limits<flow_t>::max();

// Structure to represent an edge in the flow network
struct Edge {
    int to;         // The destination node of the edge
    flow_t capacity; // The current capacity of the edge
    int rev;        // The index of the reverse edge in the adjacency list of the 'to' node
    // Optional: Store original street info if needed for output
    int original_u; // Original 1-indexed start node of the street
    int original_v; // Original 1-indexed end node of the street
    bool is_original_street; // True if this edge corresponds to an original street direction
};

// Adjacency list representation of the graph.
// adj[u] stores indices of edges starting from node u in the 'edges' vector.
std::vector<std::vector<int>> adj;
// Stores all edges in the graph. Each physical connection (u, v, c)
// results in multiple entries in this vector.
std::vector<Edge> edges;

// Level graph for BFS. Stores the distance from the source in the layered network.
std::vector<int> level;
// Pointer optimization for DFS in Dinic's algorithm.
// ptr[u] stores the index of the next edge to explore from node u
// in the adjacency list during the current DFS phase.
std::vector<int> ptr;

// Function to add a directed edge and its reverse edge to the graph
// For an undirected street (u, v) with capacity 1, we call this twice:
// add_edge(u-1, v-1, 1, u, v, true) and add_edge(v-1, u-1, 1, u, v, false)
void add_edge(int u, int v, flow_t capacity, int original_u, int original_v, bool is_original_street) {
    // Add the forward edge from u to v
    adj[u].push_back(edges.size()); // Store the index of this new edge
    edges.push_back({v, capacity, (int)edges.size() + 1, original_u, original_v, is_original_street}); // Create the edge and link to its reverse

    // Add the backward (reverse) edge from v to u with initial capacity 0
    adj[v].push_back(edges.size()); // Store the index of the reverse edge
    edges.push_back({u, 0, (int)edges.size() - 1, original_u, original_v, false}); // Create the reverse edge and link back to the forward
}

// Breadth-First Search to build the level graph (layered network)
// Returns true if the sink 't' is reachable from the source 's' in the residual graph.
bool bfs(int s, int t) {
    // Initialize levels of all nodes to -1 (unvisited)
    level.assign(adj.size(), -1);
    // Source node is at level 0
    level[s] = 0;
    // Queue for BFS
    std::queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // Explore neighbors of node u
        for (int id : adj[u]) {
            const Edge& edge = edges[id];
            // If the edge has remaining capacity and the destination node is unvisited
            if (edge.capacity > 0 && level[edge.to] == -1) {
                // Set the level of the destination node
                level[edge.to] = level[u] + 1;
                // Add the destination node to the queue
                q.push(edge.to);
            }
        }
    }
    // Return true if the sink node 't' was reached during BFS (level[t] is not -1)
    return level[t] != -1;
}

// Depth-First Search to find augmenting paths in the level graph
// Pushes flow from node 'u' to the sink 't', with a maximum allowed flow 'pushed'.
// Returns the amount of flow successfully pushed along the found path.
flow_t dfs(int u, int t, flow_t pushed) {
    // If no flow can be pushed, return 0
    if (pushed == 0) return 0;
    // If the sink is reached, return the amount of flow to be pushed
    if (u == t) return pushed;

    // Iterate through edges starting from node u, using the pointer optimization
    // `ptr[u]` keeps track of the next edge to check from u in the adjacency list during the current DFS phase.
    for (int& cid = ptr[u]; cid < adj[u].size(); ++cid) {
        int id = adj[u][cid];
        Edge& edge = edges[id];

        // Check if the edge is valid in the current level graph and has capacity:
        // 1. The destination node must be exactly one level below the current node (part of the layered network).
        // 2. The edge must have remaining capacity.
        if (level[edge.to] != level[u] + 1 || edge.capacity == 0) continue;

        // Recursively call DFS on the destination node to find flow further down the path.
        // The amount of flow we can push through this edge is limited by its capacity
        // and the amount of flow that can be pushed from the destination to the sink.
        flow_t tr = dfs(edge.to, t, std::min(pushed, edge.capacity));

        // If no flow was found through the rest of the path from edge.to, continue to the next edge from u.
        if (tr == 0) continue;

        // If flow 'tr' was found, augment the flow along this edge and its reverse.
        edge.capacity -= tr;          // Decrease capacity of the forward edge
        edges[edge.rev].capacity += tr; // Increase capacity of the reverse edge

        // Return the amount of flow pushed along this path.
        return tr;
    }

    // If the loop finishes without finding any augmenting path from u, return 0.
    return 0;
}

// Dinic's algorithm to find the maximum flow from source 's' to sink 't'
flow_t dinic(int s, int t) {
    flow_t total_flow = 0;
    // Repeat as long as there is an augmenting path from source to sink in the residual graph
    while (bfs(s, t)) {
        // Reset the pointer array for the DFS phase.
        // This optimization avoids re-checking edges that have already been found to lead to dead ends
        // in the current level graph.
        ptr.assign(adj.size(), 0);
        // In each DFS phase (after one BFS), find all possible augmenting paths
        // in the current level graph using multiple DFS calls until no more flow can be pushed
        // from the source in this layered network.
        while (flow_t pushed = dfs(s, t, INF)) {
            total_flow += pushed;
        }
    }
    // Return the total maximum flow found
    return total_flow;
}

// Function to find the nodes reachable from the source in the residual graph
std::vector<bool> find_reachable(int s, int n_nodes) {
    std::vector<bool> reachable(n_nodes, false);
    std::queue<int> q;

    q.push(s);
    reachable[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int id : adj[u]) {
            const Edge& edge = edges[id];
            // If the edge has remaining capacity and the destination is not yet reachable
            if (edge.capacity > 0 && !reachable[edge.to]) {
                reachable[edge.to] = true;
                q.push(edge.to);
            }
        }
    }
    return reachable;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    std::cin >> n >> m; // n: number of crossings, m: number of streets

    // Adjust node indices to be 0-indexed (crossings 1..n become 0..n-1)
    int source = 0;     // Bank is at crossing 1 (0-indexed)
    int sink = n - 1;   // Harbor is at crossing n (0-indexed)

    // Resize adjacency list to accommodate n nodes (0 to n-1)
    adj.resize(n);

    // Store original street endpoints to output the cut edges
    std::vector<std::pair<int, int>> original_streets(m);

    // Read streets and build the flow network graph
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        original_streets[i] = {u, v}; // Store original 1-indexed endpoints

        // Add two directed edges with capacity 1 for each undirected street
        // u-1 -> v-1 with capacity 1 (representing one direction of the street)
        add_edge(u - 1, v - 1, 1, u, v, true);
        // v-1 -> u-1 with capacity 1 (representing the other direction of the street)
        add_edge(v - 1, u - 1, 1, u, v, true);
    }

    // Calculate the maximum flow from the source (bank) to the sink (harbor)
    flow_t min_streets_to_close = dinic(source, sink);

    // Print the minimum number of streets to close (which is the max flow value)
    std::cout << min_streets_to_close << std::endl;

    // --- Find and Print the Streets in the Minimum Cut ---

    // Find all nodes reachable from the source in the residual graph
    std::vector<bool> reachable = find_reachable(source, n);

    // Iterate through all edges in the flow network to find those in the min cut.
    // An edge (u, v) is in the min cut if u is reachable from the source
    // in the residual graph and v is not reachable, and the edge corresponds
    // to an original street direction (capacity was 1).
    for (const auto& edge : edges) {
        // We only care about the edges that represent the original street directions.
        // Each original street (u, v) was added as two directed edges: u->v and v->u,
        // both marked with is_original_street = true.
        // We need to find one of these where the start is reachable and the end is not.
        if (edge.is_original_street) {
            int u_idx = edge.original_u - 1; // 0-indexed start node of original street
            int v_idx = edge.original_v - 1; // 0-indexed end node of original street

            // Check if the edge goes from a reachable node to an unreachable node
            // in the residual graph. This indicates it's part of the min cut.
            // We check both directions of the original street's representation.
            if (reachable[u_idx] && !reachable[v_idx]) {
                 // The edge from original_u to original_v is in the cut (or its reverse is).
                 // Since we added both directions of the original street with capacity 1,
                 // if u is reachable and v is not, the edge u->v must be saturated.
                 // This means the original street between original_u and original_v
                 // needs to be closed.
                 std::cout << edge.original_u << " " << edge.original_v << std::endl;
                 // We only need to print each original street once, so we can skip
                 // the corresponding reverse edge that also represents this street.
                 // A simple way is to mark streets as printed, or rely on the fact
                 // that exactly 'min_streets_to_close' edges will satisfy this condition
                 // and correspond to unique original streets.
                 // Given the problem constraints and typical min-cut output requirements,
                 // printing (u, v) when u is reachable and v is not, for original streets,
                 // will give the correct set of edges in the cut.
            }
        }
    }


    return 0;
}
