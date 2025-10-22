#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) cin >> grid[i];

    vector<vector<bool>> visited(n, vector<bool>(n, false));
    vector<pair<int,int>> frontier;
    frontier.push_back({0,0});
    visited[0][0] = true;

    string ans;
    ans += grid[0][0];

    int dx[2] = {1, 0};
    int dy[2] = {0, 1};

    while (true) {
        vector<pair<int,int>> next_frontier;
        char min_char = 'Z'+1;

        for(auto [x,y]:frontier){
            for(int d=0;d<2;d++){
                int nx = x + dx[d];
                int ny = y+dy[d];
                if (nx < n && ny < n && !visited[nx][ny]) {
                    min_char = min(min_char, grid[nx][ny]);
                }
            }
        }
        if(min_char>'Z') break; // no more moves;

        // add minimal with char
           // Add positions with minimal char
        for (auto [x,y] : frontier) {
            for (int d = 0; d < 2; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx < n && ny < n && !visited[nx][ny] && grid[nx][ny] == min_char) {
                    next_frontier.push_back({nx, ny});
                    visited[nx][ny] = true;
                }
            }
        }
 
        ans += min_char;

    }

    cout << ans << "\n";
    return 0;
}
