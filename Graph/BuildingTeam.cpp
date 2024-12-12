#include <bits/stdc++.h>
using namespace std;
bool isPossible=true;

bool dfs(int i,int curr,vector<vector<int>>& adj,vector<int>& colors){
    if(colors[i]!=0){
            return colors[i]!=curr;
    }
    colors[i]=curr==1?2:1;
    for(auto ch:adj[i]){
        if(!dfs(ch,colors[i],adj,colors)){
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
		isPossible = dfs(i,0,adj,colors);
	}
	if(!isPossible){
		cout<<"IMPOSSIBLE"<<endl;
		return 0;
	}
	for(int i = 1;i<=n;i++) cout<<colors[i]<<" ";
 

    
   
    return 0;
}