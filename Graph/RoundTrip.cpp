#include <bits/stdc++.h>
using namespace std;
bool isPossible=false;
void printResult(int node,vector<int>&path){
	isPossible = true;
	int count =1;
	string result = "";
	result+= to_string(node)+" ";
	for(int i = path.size()-1;i>=0;i--){
		result += to_string(path[i]);
		count++;
		if(path[i]==node) break;
		else result+=" "; 
	}
	cout<<count<<" "<<endl;
	cout<<result<<endl;
}
void dfs(int parent,int u, vector<bool> &visited,
                           vector<vector<int>> &adj,vector<int>&answer) {
    
    
    if(isPossible) return;
    if(visited[u]==true){
        if(answer.size()>2){
            printResult(u,answer);
        }
    }
    visited[u] = true;
    

    
    answer.push_back(u);
    for(auto &v : adj[u]) {
        if(v==parent) continue;
        dfs(u,v,visited,adj,answer);
    }
    answer.pop_back();
   
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
    
    
    
    vector<bool> visited(n+1,0);
    vector<int> answer;
    
    for(int i = 1;i<=n;i++){
        if(visited[i]==false){
            dfs(-1,i,visited,adj,answer);
        }
    }
    
    if(isPossible==false)
	    cout<<"IMPOSSIBLE"<<endl;
		
	

 

    
   
    return 0;
}