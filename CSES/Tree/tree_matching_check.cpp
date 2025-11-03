#include<bits/stdc++.h>
using namespace std;
using vi = vector<int>;
int n;
const int MX = 2e5+5;
vector<int> adj[MX];
int dp[MX][2];
void solve(int u, int p){
    dp[u][0] = dp[u][1] = 0;
    int total = 0;
    for(int v: adj[u]) if(v!=p){
        solve(v, u);
        total += max(dp[v][0], dp[v][1]);
    }
    // base = sum max(dp[u][0], dp[u][1])
    dp[u][0] = total; // v not matched
    int best = 0;
    
    // dp[v][0] : either don't match v to any child (base)
    // or match v with exactly one child u
    for(int v: adj[u]) if(v!=p){
        // if match v-u: we gain 1 (edge) + dp[v][1] for v-subtree (v matched to parent)
        int candidate = 1 + dp[v][0] + (total - max(dp[v][0], dp[v][1]));
        best = max(best, candidate);
    }
    dp[u][1] = best;
}
int main(){
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    solve(1, -1);
    // The root can either be matched or not
    cout << max(dp[1][0], dp[1][1]) << "\n";
    return 0;
}