// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>
using namespace std;
void dfs(int i,int j, vector<vector<char>>& b){
    int n = b.size();
    int m = b[0].size();
    if(i>=n||i<0||j<0||j>=m||b[i][j]=='#') return;
    b[i][j] = '#';
    dfs(i+1,j,b);
    dfs(i,j-1,b);
    dfs(i-1,j,b);
    dfs(i,j+1,b);
    
}
int main() {
   
   int n,m;
   cin>>n>>m;
   
   vector<vector<char>> board(n,vector<char>(m));
   
   for(int i = 0;i<n;i++){
       for(int j = 0;j<m;j++){
           cin>>board[i][j];
       }
   }
   int answer = 0;
   
   for(int i=0;i<n;i++){
       for(int j=0;j<m;j++){
           if(board[i][j]=='.'){
               answer++;
               dfs(i,j,board);
           }
       }
   }
    cout<<answer<<endl;
    return 0;
}