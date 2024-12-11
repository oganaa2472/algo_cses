#include <bits/stdc++.h>
using namespace std;
 

void dfs(int child,vector<vector<int>>&adj,vector<bool>& visited){
    if(visited[child]) return;
    visited[child] = true;
    for(auto c:adj[child]){
        dfs(c,adj,visited);
    }
}
int main() {
    int n, m;
    cin >> n >> m;
    
    
    vector<vector<int>> adj(n+1);
    vector<vector<int>> adj2(n+1);
    int a,b;
    for(int i = 0;i<m;i++){
        cin>>a>>b;
        adj[a].push_back(b);
        adj2[b].push_back(a);
    }
    
    int count = 0;
    vector<bool> visited(n+1,false);
    dfs(1,adj,visited);
    for(int i = 1;i<=n;i++){
        if(visited[i]==false){
            cout<<"NO"<<endl;
            cout<<1<<" "<<i;
            return 0;
        }
    }
    fill(visited.begin(), visited.end(), false);
    dfs(1,adj2,visited);
    
    for(int i = 1;i<=n;i++){
        if(visited[i]==false){
            cout<<"NO"<<endl;
            cout<<i<<" "<<1;
            return 0;
        }
    }
    cout<<"YES"<<endl;
//   if(answer.size()==0){
//     cout<<"YES"<<endl;
//   }else{
//     cout<<"NO"<<endl;
//     for(auto ans:answer){
//         cout<<ans<<" ";
//     }
//   }

    
   
    return 0;
}