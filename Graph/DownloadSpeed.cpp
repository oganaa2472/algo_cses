#include <iostream>
#include <vector>
#include <queue>
#include <limits> // For numeric_limits
#include <algorithm> // For std::min

// Use long long for flow and capacity to handle large values
using flow_t = long long;
// A large value to represent infinite capacity
const flow_t INF = std::numeric_limits<flow_t>::max();

// Structure to represent an edge in the flow network
struct Edge {
    int to;         // The destination node of the edge
    flow_t capacity; // The current capacity of the edge
    int rev;        // The index of the reverse edge in the adjacency list of the 'to' node
};

// Adjacency list representation of the graph.
// adj[u] stores indices of edges starting from node u in the 'edges' vector.
std::vector<std::vector<int>> adj;
// Stores all edges in the graph. Each physical connection (u, v, c)
// results in two entries: a forward edge (u, v) with capacity c
// and a backward edge (v, u) with initial capacity 0.
std::vector<Edge> edges;

// Level graph for BFS. Stores the distance from the source in the layered network.
std::vector<int> level;
// Pointer optimization for DFS in Dinic's algorithm.
// ptr[u] stores the index of the next edge to explore from node u
// in the adjacency list during the current DFS phase.
std::vector<int> ptr;

// Function to add a directed edge and its reverse edge to the graph
void add_edge(int u, int v, flow_t capacity) {
    // Add the forward edge from u to v
    adj[u].push_back(edges.size()); // Store the index of this new edge
    edges.push_back({v, capacity, (int)edges.size() + 1}); // Create the edge and link to its reverse

    // Add the backward (reverse) edge from v to u with initial capacity 0
    adj[v].push_back(edges.size()); // Store the index of the reverse edge
    edges.push_back({u, 0, (int)edges.size() - 1}); // Create the reverse edge and link back to the forward
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
    // `ptr[u]` keeps track of the next edge to check from u in this DFS phase.
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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    std::cin >> n >> m; // n: number of computers, m: number of connections

    // Adjust node indices to be 0-indexed (computers 1..n become 0..n-1)
    int source = 0;     // Server is computer 1 (0-indexed)
    int sink = n - 1;   // Kotivalo's computer is computer n (0-indexed)

    // Resize adjacency list to accommodate n nodes (0 to n-1)
    adj.resize(n);

    // Read connections and build the flow network graph
    for (int i = 0; i < m; ++i) {
        int u, v;
        flow_t c; // Capacity of the connection
        std::cin >> u >> v >> c;
        // Add a directed edge from u to v with capacity c.
        // Adjust input node indices (1-based) to 0-based.
        add_edge(u - 1, v - 1, c);
    }

    // Calculate the maximum flow from the source (computer 1) to the sink (computer n)
    flow_t max_speed = dinic(source, sink);

    // Print the maximum speed (maximum flow)
    std::cout << max_speed << std::endl;

    return 0;
}
