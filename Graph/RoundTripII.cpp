#include <bits/stdc++.h>
using namespace std;
struct Edge {
    int from; // Эхлэх зангилаа
    int to;   // Очих зангилаа
};
bool dfs(int node,vector<bool>& visited,vector<bool>&pathVisited,vector<vector<int>>&adj,vector<int>&path,int& cycleStart){
    visited[node] = true;
    pathVisited[node] = true;
    path.push_back(node);
    for(auto v:adj[node]){
        if(!visited[v]){
            if(dfs(v,visited,pathVisited,adj,path,cycleStart)){
                return true;
            }
        }else if(pathVisited[v]) {
            cycleStart = v;
            path.push_back(v);
            return true;
        }
    }
    pathVisited[node] = false;
    path.pop_back();
    return false;
}
int main() {
	// your code goes here
    int n, m; // n: зангилааны тоо, m: ирмэгийн тоо
    cin >> n >> m;
    vector<vector<int>> adj(n+1);// Бүх ирмэгийн жагсаалт
    for (int i = 0; i<m; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
    }
 
   vector<bool> visited(n+1,false);
   vector<bool> pathVisited(n+1,false);
    int cycleStart = -1;
    for(int i =1;i<=n;i++)
    {
        if(!visited[i]){
             vector<int> path;
            if(dfs(i,visited,pathVisited,adj,path,cycleStart)){
                // path.insert(0,path.begin());
               vector<int> cycle;
                for (int j = path.size() - 1; j >= 0; --j) {
                    cycle.push_back(path[j]);
                    if (path[j] == cycleStart && cycle.size() > 1)
                        break;
                }
                reverse(cycle.begin(), cycle.end());

                cout << cycle.size() << "\n";
                for (int node : cycle)
                    cout << node << " ";
                cout << "\n";
                return 0;
            } 
        }
        
    }
    cout<<"IMPOSSIBLE"<<endl;
    return 0;
}
