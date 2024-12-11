// #include <bits/stdc++.h>
// using namespace std;
 
// vector<tuple<long, long, char>> direction = {{1, 0, 'D'}, {-1, 0, 'U'}, {0, 1, 'R'}, {0, -1, 'L'}};
// int main() {
//     int n, m;
//     cin >> n >> m;
 
//     vector<vector<char>> board(n, vector<char>(m));
//     vector<vector<bool>> visited(n, vector<bool>(m, false));
    
//     int endX = -1, endY = -1;
//     queue<pair<int, int,string>> q;
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < m; j++) {
//             cin >> board[i][j];
//             if (board[i][j] == 'A') {
//                 q.push({i, j,""});
//                 visited[i][j] = true;
//             } else if (board[i][j] == 'B') {
//                 endX = i;
//                 endY = j;
//             }
//         }
//     }
//     if (q.empty() || endX == -1 || endY == -1) {
//         cout << "NO" << endl;
//         return 0;
//     }
//     // vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));
//     while (!q.empty()) {
//             auto [x, y,answer] = q.front();
//             q.pop();
 
//             if (x == endX && y == endY) {
                
//                 // string answer;
//                 // int curX = endX,curY = endY;
//                 // while (curX != -1 && curY != -1) {
//                 //         auto [px, py] = parent[curX][curY];
//                 //         if (px == -1 && py == -1) break;

//                 //         for (auto [dx, dy, cch] : direction) {
//                 //             if (px + dx == curX && py + dy == curY) {
//                 //                 answer += cch;
//                 //                 break;
//                 //             }
//                 //         }
//                 //         curX = px;
//                 //         curY = py;
//                 // }
//                 // reverse(answer.begin(),answer.end());
//                 cout << "YES" << endl;
//                 cout << answer.size() << endl;
//                 cout << answer << endl;
//                 return 0;
//             }
 
//            for (auto [dx, dy, ch] : direction) {
//                 long newX = x + dx;
//                 long newY = y + dy;
//                 if (newX < 0 || newX >= n || newY < 0 || newY >= m) continue;
//                 if (board[newX][newY] == '#') continue;
//                 if (visited[newX][newY]) continue;
//                 visited[newX][newY] = true;
//                 q.push({newX, newY,answer+ch});

//                 // parent[newX][newY] = {x,y};
//             }

        
        
//     }
 
//     cout << "NO" << endl;
//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;
 
vector<tuple<long, long, char>> direction = {{1, 0, 'D'}, {-1, 0, 'U'}, {0, 1, 'R'}, {0, -1, 'L'}};
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> board(n, vector<char>(m));
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    
    int endX = -1, endY = -1;
    queue<pair<int,pair<int,string>>> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
            if (board[i][j] == 'A') {
                q.push({i,{j,""}});
                visited[i][j] = true;
            } else if (board[i][j] == 'B') {
                endX = i;
                endY = j;
            }
        }
    }
    if (q.empty() || endX == -1 || endY == -1) {
        cout << "NO" << endl;
        return 0;
    }
    // vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));
    while (!q.empty()) {
            pair<int,pair<int,string>>pq = q.front();
            int x = pq.first;
            int y=pq.second.first;
            string answer = pq.second.second;
            q.pop();
 
            if (x == endX && y == endY) {
                
                // string answer;
                // int curX = endX,curY = endY;
                // while (curX != -1 && curY != -1) {
                //         auto [px, py] = parent[curX][curY];
                //         if (px == -1 && py == -1) break;

                //         for (auto [dx, dy, cch] : direction) {
                //             if (px + dx == curX && py + dy == curY) {
                //                 answer += cch;
                //                 break;
                //             }
                //         }
                //         curX = px;
                //         curY = py;
                // }
                // reverse(answer.begin(),answer.end());
                cout << "YES" << endl;
                cout << answer.size() << endl;
                cout << answer << endl;
                return 0;
            }
 
           for (auto [dx, dy, ch] : direction) {
                long newX = x + dx;
                long newY = y + dy;
                if (newX < 0 || newX >= n || newY < 0 || newY >= m) continue;
                if (board[newX][newY] == '#') continue;
                if (visited[newX][newY]) continue;
                visited[newX][newY] = true;
                
                q.push({newX,{newY,answer+ch}});

                // parent[newX][newY] = {x,y};
            }

        
        
    }
 
    cout << "NO" << endl;
    return 0;
}