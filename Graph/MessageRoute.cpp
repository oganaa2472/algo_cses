#include <bits/stdc++.h>
using namespace std;
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
    vector<bool> visited(n+1,false);
    queue<int> q;
    q.push(1);
    visited[1] =true;
    vector<int> parent(n+1,-1);
    
    while(!q.empty()){
        int node = q.front();
        q.pop();
        
               
            if(node == n){
            vector<int> answer;
            int curNode = n;
            
            while(curNode!=-1){
                answer.push_back(curNode);
                int beforeNode = parent[curNode];
                // answer.push_back(beforeNode);
                curNode = beforeNode;
            }
            
            reverse(answer.begin(),answer.end());
    
            cout << answer.size() << endl;
            for(int i = 0;i<answer.size();i++)
            {
                cout<<answer[i]<<" ";
            }
            
            
            
            return 0;
        }
        for(auto ch:adj[node]){
            if(!visited[ch]){
                q.push(ch);
                parent[ch] = node;
                visited[ch] = true;
            }   
        }
    }
    cout<<"IMPOSSIBLE";
 

    
   
    return 0;
}