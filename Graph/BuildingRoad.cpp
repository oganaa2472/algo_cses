#include <bits/stdc++.h>
using namespace std;
bool isPossible=true;

bool dfs(int u, int color, vector<int> &colors,
                           vector<vector<int>> &adj) {

    // Assign color to the current u
 
    colors[u] = color;

    // Iterate through all adjacent vertices
    for(auto &v : adj[u]) {
        if(colors[v] == 0) {

            
            if(!dfs(v, color==1?2:1, colors, adj))
                return false;
        }
        else if(colors[v] == color) {
            return false;
        }
    }
    return true;
}
int main() {
    int n, m;
    cin >> n >> m;
    
    
    vector<vector<int>> adj(n+1);
    int a,b;
    for(int i = 0;i<m;i++){
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    
    
    vector<int> colors(n+1,0);
	for(int i =1;i<n+1&&isPossible;i++){
	    if(colors[i] == 0) { 
                
            isPossible = dfs(i, 1, colors, adj);
        }
		
	}
	if(!isPossible){
		cout<<"IMPOSSIBLE"<<endl;
		return 0;
	}
	for(int i = 1;i<=n;i++) cout<<colors[i]<<" ";
 

    
   
    return 0;
}