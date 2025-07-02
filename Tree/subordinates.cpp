#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> adj;
vector<bool> visited;
vector<int> dp;
void dfs(int u,int p){
    dp[u] = 1;
    for(int v:adj[u]){
        if(v==p) continue;
        dfs(v,u);
        dp[u]+=dp[v];
    }

}
int main() {
    
	// your code goes here
	
	int n;
	cin>>n;
	adj.resize(n+1);
    dp.resize(n+1,0);

    
    for(int i = 2;i<=n;i++){
        int u;
        cin>>u;
        adj[u].push_back(i);
        adj[i].push_back(u);
    }
    dfs(1,0);
    for(int i = 1;i<dp.size();i++){
        cout<<dp[i]-1<<" ";
    }
    
    
}
