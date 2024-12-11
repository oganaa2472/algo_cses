#include <bits/stdc++.h>
using namespace std;
 
 
void dfs(int parent,int child,vector<vector<int>>&adj,vector<bool>& visited){
    if(visited[child]==true) return;
    visited[child] = true;
    for(auto c:adj[child]){
        if(parent!=c){
            dfs(child,c,adj,visited);
        }
    }
    
}
int main() {
    int n, m;
    cin >> n >> m;
    vector<bool> visited(n+1,false);
    
    vector<vector<int>> adj(n+1);
    int a,b;
    for(int i = 0;i<m;i++){
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    int count = 0;
    vector<int>answer;
    for(int i =1;i<=n;i++){
        if(visited[i]==false){
            answer.push_back(i);
            count++;
            dfs(0,i,adj,visited);
        }
    }
    cout<<count-1<<endl;
    for(int i = 0;i<answer.size()-1;i++){
        cout<<answer[i]<<" "<<answer[i+1]<<endl;
    }
   
    return 0;
}