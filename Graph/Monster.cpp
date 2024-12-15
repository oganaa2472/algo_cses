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

vector<vector<int>> moves = {{-1, 0, 0}, {1, 0, 1}, {0, 1, 2}, {0, -1, 3}};

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
                area[i][j] = 0;
                me = {i, j};
            }
        }
    }

    if (me.first == 0 || me.second == 0 || me.first == n - 1 || me.second == m - 1) {
        cout << "YES" << endl;
        cout << 0 << endl;
        return 0;
    }
    
    // BFS for monsters
    queue<pair<pair<int, int>, int>> q;
    for (auto m : monsters) {
        q.push(make_pair(m, 0));
    }

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

    // BFS for the player
    queue<pair<pair<int, int>, int>> mq;
    mq.push(make_pair(me, 0));

    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));
    parent[me.first][me.second] = {-1, -1};

    while (!mq.empty()) {
        int cx = mq.front().first.first;
        int cy = mq.front().first.second;
        int timer = mq.front().second;
        mq.pop();
        timer++;

        for (auto& mv : moves) {
            int tx = cx + mv[0];
            int ty = cy + mv[1];

            if (isEscape(tx, ty, timer, area)) {
                // Path reconstruction
                string path;
                parent[tx][ty] = {cx, cy};  // Record the last move
                int curX = tx, curY = ty;
                while (curX != -1 && curY != -1) {
                    pair<int, int> p = parent[curX][curY];
                    if (p.first == -1 && p.second == -1) break;

                    if (p.first == curX - 1) path += 'D';
                    else if (p.first == curX + 1) path += 'U';
                    else if (p.second == curY - 1) path += 'R';
                    else if (p.second == curY + 1) path += 'L';

                    curX = p.first;
                    curY = p.second;
                }

                reverse(path.begin(), path.end());
                cout << "YES" << endl;
                cout<<path.size()<<endl;
                cout << path << endl;
                return 0;
            }

            if (isValid(tx, ty, timer, area)) {
                parent[tx][ty] = {cx, cy};
                area[tx][ty] = timer;
                mq.push({{tx, ty}, timer});
            }
        }
    }

    cout << "NO" << endl;
    return 0;
}
