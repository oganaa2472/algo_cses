#include <bits/stdc++.h>
using namespace std;

bool isValid(int x, int y, int t, vector<vector<int>>& area) {
    int n = area.size();
    int m = area[0].size();
    if (x < 0 || y < 0 || x >= n || y >= m) return false;
    if (area[x][y] <= t) return false;
    return true;
}

bool isEscape(int x, int y, int timer, vector<vector<int>>& area) {
    int n = area.size();
    int m = area[0].size();
    if (!isValid(x, y, timer, area)) return false;
    if (x == 0 || y == 0 || x == n - 1 || y == m - 1) return true;
    return false;
}

vector<vector<int>> moves{{0, 1, 0}, {1, 0, 1}, {0, -1, 2}, {-1, 0, 3}};

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> area(n, vector<int>(m, INT_MAX));
    
    vector<pair<int, int>> monsters;
    pair<int, int> me;
   
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            if (c == '#') {
                area[i][j] = 0;
            } else if (c == 'M') {
                area[i][j] = 0;
                monsters.push_back({i, j});
            } else if (c == 'A') {
                me = {i, j};
            }
        }
    }

    if (me.first == 0 || me.second == 0 || me.first == n - 1 || me.second == m - 1) {
        cout << "YES" << endl;
        cout << 0 << endl;
        return 0;
    }
    
    queue<pair<pair<int, int>, int>> q;
    for (auto m : monsters) {
        q.push(make_pair(m, 0));
    }

    // Preprocess monster times
    while (!q.empty()) {
        int cx = q.front().first.first;
        int cy = q.front().first.second;
        int timer = q.front().second;
        q.pop();
        timer++;

        for (auto mv : moves) {
            int tx = cx + mv[0];
            int ty = cy + mv[1];
            if (isValid(tx, ty, timer, area)) {
                area[tx][ty] = timer;
                q.push({{tx, ty}, timer});
            }
        }
    }
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            cout<<area[i][j]<<"    ";
        }
        cout<<endl;
    }
    queue<pair<pair<int, int>, int>> meQ;
    meQ.push(make_pair(me, 0));

    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));
    queue<pair<pair<int,int>,int>> mq;
      mq.push(make_pair(me,0));
    //   par_mp[si] = {-1,-1};
        
      while(!mq.empty())
      {
        int cx = mq.front().first.first;
        int cy = mq.front().first.second;
        int timer = mq.front().second; 
        timer++; mq.pop();
        for(auto mv: moves)
        {
          int tx = cx+mv[0];
          int ty = cy+mv[1];
          if(isEscape(tx,ty,timer,area))
          {
            cout<<"YES"<<endl;
            return 0;
          }
          if(isValid(tx,ty,timer,area))
          {
            parent[tx][ty] = {cx,cy};
            area[tx][ty] = timer;
            q.push({{tx,ty},timer});
          }
        }
      }
      
    // while (!meQ.empty()) {
    //     int cx = meQ.front().first.first;
    //     int cy = meQ.front().first.second;
    //     int timer = meQ.front().second;
    //     meQ.pop();
    //     timer++;

       
    //     for (auto& mo : moves) {
    //         int newX = cx + mo[0];
    //         int newY = cy + mo[1];
    //          if (isEscape(cx, cy, timer, area)) {
    //         // Path reconstruction
    //         string path;
    //         int curX = cx,curY = cy;
    //         while(curX!=-1&&curY!=-1){
    //             pair<int,int> p= parent[curX][curY];
    //             if (p.first == -1 && p.second == -1) break;
    //              for(auto& mo:moves){
    //                  if(mo[0]==p.first&&mo[1]==p.second){
    //                      if(mo[2]==0){
    //                          path+="U";
    //                      }else if(mo[2]==1){
    //                           path+="R";
    //                      }else if(mo[2]==2){
    //                           path+="D";
    //                      }else {
    //                           path+="L";
    //                      }
    //                      break;
    //                  }
    //              }
    //              curX = p.first;
    //              curY = p.second;
    //         }
    //         cout<<"YES"<<endl;
    //         reverse(path.begin(),path.end());
    //         cout<<path<<endl;
    //         return 0;
    //     }

    //         if (isValid(newX, newY, timer, area)) {
    //             parent[newX][newY] = {cx, cy};
    //             area[newX][newY] = timer;
    //             meQ.push({{newX, newY}, timer});
    //         }
    //     }
    // }

    cout << "NO" << endl;
    return 0;
}
