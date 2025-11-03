#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

int n;
vector<vector<int>> adj;
vector<array<int,2>> dp;
vector<int> parent;

void dfs(int v, int p){
    parent[v] = p;
    dp[v][0] = dp[v][1] = 0;
    vector<int> children;
    for(int u: adj[v]) if(u!=p){
        dfs(u, v);
        children.push_back(u);
    }
     // base = sum max(dp[u][0], dp[u][1])
    int base = 0;
    for(int u: children) base += max(dp[u][0], dp[u][1]);
    dp[v][1] = base; // v matched to parent -> cannot match children

    // dp[v][0] : either don't match v to any child (base)
    int best = base;
    // or match v with exactly one child u
    for(int u: children){
        // if match v-u: we gain 1 (edge) + dp[u][1] for u-subtree (u matched to parent)
        int candidate = base - max(dp[u][0], dp[u][1]) + 1 + dp[u][1];
        best = max(best, candidate);
    }
    dp[v][0] = best;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    adj.assign(n+1, {});
    for(int i=0;i<n-1;i++){
        int a,b; cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dp.assign(n+1, {0,0});
    parent.assign(n+1, -1);
    dfs(1, 0); // root at 1
    cout << dp[1][0] << "\n";
    return 0;
}