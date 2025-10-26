#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    // adjacency list (possible glides)
    vector<vector<int>> adj(n);

    // stack for left glides
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && h[st.top()] < h[i]) {
            adj[i].push_back(st.top()); // i can glide to st.top()
            st.pop();
        }
        if (!st.empty() && h[st.top()] > h[i]) {
            adj[st.top()].push_back(i); // st.top() can glide to i
        }
        st.push(i);
    }

    // dp[i] = max mountains from i
    vector<int> dp(n, -1);
    function<int(int)> dfs = [&](int u) {
        if (dp[u] != -1) return dp[u];
        int best = 1; // at least current mountain
        for (int v : adj[u]) {
            best = max(best, 1 + dfs(v));
        }
        return dp[u] = best;
    };

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, dfs(i));
    }

    cout << ans << "\n";
}
