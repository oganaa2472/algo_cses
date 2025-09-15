#include <bits/stdc++.h>
using namespace std;

 void dfs(vector<vector<char>>& grid,int i,int j,int rows,int cols){
        if(i<0||i>=rows||j<0||j>=cols||grid[i][j]!='.'){
            return;
        }
        grid[i][j]='#';
        dfs(grid,i+1,j,rows,cols);
        dfs(grid,i-1,j,rows,cols);
        dfs(grid,i,j+1,rows,cols);
        dfs(grid,i,j-1,rows,cols);
}
int numIslands(vector<vector<char>>& grid) {
        int rows = grid.size();
        if (rows==0) return 0;
        int col = grid[0].size();
        int ans = 0;
        for(int i = 0;i<rows;i++){
            for(int j = 0;j<col;j++){
                if(grid[i][j]=='.'){
                    dfs(grid,i,j,rows,col);
                    ans++;
                }
            }
        } 
        return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<char>> grid(n,vector<char>(m));
    for (int i = 0; i < n; i++) {
        for(int j = 0;j<m;j++){
            cin>>grid[i][j];
        }
       
    }

    cout<<numIslands(grid);
    return 0;
}
