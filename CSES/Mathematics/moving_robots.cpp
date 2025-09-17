#include <bits/stdc++.h>
using namespace std;

int main() {
    int k;
    cin >> k;
    const int N = 8;
    vector<vector<vector<double>>> dp(N, vector<vector<double>>(N, vector<double>(k+1,0.0)));
    
    double expectedEmpty = 0.0;
    
    // Precompute moves for a robot starting from (i,j)
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    
    // probability for each square to be empty
    vector<vector<double>> probEmpty(N, vector<double>(N,1.0));
    
    for(int startX=0; startX<N; startX++) {
        for(int startY=0; startY<N; startY++) {
            // reset dp for this robot
            for(int x=0;x<N;x++)
                for(int y=0;y<N;y++)
                    for(int s=0;s<=k;s++)
                        dp[x][y][s]=0;
            dp[startX][startY][0] = 1.0;
            for(int step=1; step<=k; step++){
                for(int x=0;x<N;x++){
                    for(int y=0;y<N;y++){
                        double sum = 0.0;
                        int cnt = 0;
                        for(auto d: dirs){
                            int nx = x + d.first;
                            int ny = y + d.second;
                            if(nx>=0 && nx<N && ny>=0 && ny<N){
                                sum += dp[nx][ny][step-1]/((nx>0)+(nx<7)+(ny>0)+(ny<7));
                            }
                        }
                        dp[x][y][step] = sum;
                    }
                }
            }
            // update probability square is empty
            for(int x=0;x<N;x++){
                for(int y=0;y<N;y++){
                    probEmpty[x][y] *= (1.0 - dp[x][y][k]);
                }
            }
        }
    }
    
    double ans = 0.0;
    for(int x=0;x<N;x++)
        for(int y=0;y<N;y++)
            ans += probEmpty[x][y];
    
    cout << fixed << setprecision(6) << ans << "\n";
}
