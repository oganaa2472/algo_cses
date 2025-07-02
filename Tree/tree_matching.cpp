#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> adj;
vector<bool> matched;
int matched_count;
void dfs(int u,int p){
    for(int v:adj[u]){
        if(v==p) continue;
        dfs(v,u);
        if(!matched[u]&&!matched[v]){
            matched[u] = true;
            matched[v] = true;
            matched_count++;
        }
    }
}
int main() {
    
	// your code goes here
	
	int n;
	cin>>n;
	
	adj.resize(n+1);
    
    matched.resize(n+1,false);
    matched_count = 0;
    if(n==1)
    {
        cout<<0<<endl;
        return 0;
    }
    for(int i = 0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    cout<<matched_count;
    
}
