#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> adj;
vector<bool> visited;
vector<int> dp;
int ans = 0;
int maxDist = 0;
int farthestNode = 0;
void dfs(int u,int dist){
    visited[u] = true;
    if(dist>maxDist){
        maxDist = dist;
        farthestNode = u;
    }
    for(int v:adj[u]){
        if(!visited[v]){
            dfs(v,dist+1);
        }
      
    }
    
  
    
}
int main() {
    
	// your code goes here
	
	int n;
	cin>>n;
	adj.resize(n+1);
    dp.resize(n+1,0);
    visited.resize(n+1,false);
    
    for(int i = 1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
     maxDist = 0;
    fill(visited.begin(), visited.end(), false);
    dfs(farthestNode, 0);
    cout<<maxDist<<endl;
    
   
    
    
}
