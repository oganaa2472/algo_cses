class Solution {
public:
    bool dfs(int node,int color,vector<vector<int>>& graph,vector<int>& vis){
        
        vis[node] = color;
        for(auto ch:graph[node]){
            if(vis[ch]==-1){
                if(!dfs(ch,1-color,graph,vis)) return false;
            }else if(vis[ch]==color){
                return false;
            }
            
        }
        return true;
    }
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> visited(n,-1);

        for(int i = 0;i<n;i++){
            if(visited[i]==-1){
                if(!dfs(i,0,graph,visited)) return false;
            }
        }
        return true;
    }
};