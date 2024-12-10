// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>
using namespace std;

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