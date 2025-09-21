// kosojaru
#include <bits/stdc++.h>
using namespace std;

void dfs1(int node, vector<vector<int>> &adj, vector<bool> &vis, stack<int> &st) {
    vis[node] = true;
    for (int neigh : adj[node]) {
        if (!vis[neigh]) {
            dfs1(neigh, adj, vis, st);
        }
    }
    st.push(node); // store finish order
}

void dfs2(int node, vector<vector<int>> &revAdj, vector<bool> &vis, vector<int> &component) {
    vis[node] = true;
    component.push_back(node);
    for (int neigh : revAdj[node]) {
        if (!vis[neigh]) {
            dfs2(neigh, revAdj, vis, component);
        }
    }
}

vector<vector<int>> stronglyConnectedComponents(int V, vector<vector<int>> &edges) {
    // Build adjacency list
    vector<vector<int>> adj(V);
    for (auto &e : edges) {
        int u = e[0], v = e[1];
        adj[u].push_back(v);
    }

    // Step 1: Order vertices by finish time in stack
    stack<int> st;
    vector<bool> vis(V, false);
    for (int i = 0; i < V; i++) {
        if (!vis[i]) dfs1(i, adj, vis, st);
    }

    // Step 2: Reverse the graph
    vector<vector<int>> revAdj(V);
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            revAdj[v].push_back(u);
        }
    }

    // Step 3: Process vertices in stack order on reversed graph
    fill(vis.begin(), vis.end(), false);
    vector<vector<int>> sccs;

    while (!st.empty()) {
        int node = st.top();
        st.pop();

        if (!vis[node]) {
            vector<int> component;
            dfs2(node, revAdj, vis, component);
            sccs.push_back(component);
        }
    }

    return sccs;
}
