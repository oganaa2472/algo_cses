#include <bits/stdc++.h>
using namespace std;

void dfs(int s, int e,vector<vector<int>>&adj,vector<int>& count) {
    count[s] = 1;
    for (auto u : adj[s]) {
        if (u == e) continue;
        dfs(u, s,adj,count);
        count[s] += count[u];
    }
}
int main() {
	// your code goes here
    int n;
    cin>>n;
    vector<vector<int>> adj(n+1);
    vector<int> answer(n,0);
    for(int i = 1;i<n;i++){
        int a;
        cin>>a;
        adj[i].push_back(a-1);
        adj[a-1].push_back(i);
    }    
    dfs(0,-1,adj,answer);
    for(int i = 0;i<n;i++){
        cout<<answer[i]-1<<" ";
        
    }
    
}
