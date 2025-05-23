#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
    int n,m;
    cin>>n>>m;
    vector<vector<int>> adj(n+1);
    for(int i = 0;i<m;i++){
        int a,b;
        cin>>a>>b;
        
        adj[a].push_back(b);
    }
    vector<int> indegree(n+1,0);
    for(int i = 1;i<=n;i++){
        for(auto it:adj[i]){
            indegree[it]++;
        }
    }
    queue<int> q;
    for(int i = 1;i<=n;i++){
        if(indegree[i]==0) q.push(i);
    }    
    vector<int> topo;
    while(!q.empty()){
        int f = q.front();
        topo.push_back(f);
        q.pop();
        for(auto it:adj[f]){
            indegree[it]--;
            if(indegree[it]==0) q.push(it);
        }
    }
    if(topo.size()==n){
        for(int i = 0;i<topo.size();i++) cout<<topo[i]<<" ";
    }else{
        cout<<"IMPOSSIBLE";
    }
}
