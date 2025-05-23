#include <bits/stdc++.h>
using namespace std;
 
 
void dfs(int node,vector<int>& vis,vector<vector<int>>& adj,stack<int>& st){
    
    vis[node] = true;
    for(auto it:adj[node]){
        if(!vis[it]) dfs(it,vis,adj,st);
    }
    st.push(node);
}
void reverseDfs(int node,vector<int>& vis,vector<vector<int>>& adj,int answer,vector<int>&comp){
    
    vis[node] = true;
    comp[node] = answer;
    for(auto it:adj[node]){
        if(!vis[it]) reverseDfs(it,vis,adj,answer,comp);
    }
   
}
int main() {
    int n,m;
    cin>>n>>m;
    vector<vector<int>> adj(n+1);
    
    for(int i = 0;i<m;i++){
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
    }
    
    vector<int> visit(n+1,0);
    
    stack<int> st;
    for(int i = 1;i<=n;i++){
        if(!visit[i]){
            dfs(i,visit,adj,st);
        }
    }
    vector<vector<int>> reverseAdj(n+1);
    for(int i = 1;i<=n;i++){
        visit[i] = false;
        for(auto it:adj[i]){
            reverseAdj[it].push_back(i);
        }
    }
    int scc=0;
    vector<int> answer(n+1,0);
    while(!st.empty()){
        int top = st.top();
        st.pop();
        if(!visit[top]){
            scc++;
            reverseDfs(top,visit,reverseAdj,scc,answer);
            
        }
        
    }
    cout<<scc<<endl;
    for(int i = 1;i<=n;i++){
        cout<<answer[i]<<" ";
    }
   
   
  
    
}