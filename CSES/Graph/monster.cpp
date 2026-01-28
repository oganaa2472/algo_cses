#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

const int INF = 1e9;
int n, m;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
char dChar[4] = {'D', 'U', 'R', 'L'};

// Замаа хадгалах бүтэц
// from_x, from_y: Хаанаас ирсэн бэ
// dir: Ямар үйлдэл хийж ирсэн бэ (D, U, L, R)
struct Parent {
    int x, y;
    char dir;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    vector<string> grid(n);
    vector<vector<int>> monster_dist(n, vector<int>(m, INF));
    vector<vector<int>> player_dist(n, vector<int>(m, INF));
    vector<vector<Parent>> path(n, vector<Parent>(m));
    
    queue<pair<int, int>> q_monster;
    queue<pair<int, int>> q_player;
    pair<int, int> start_pos;

    // Grid унших & Эхлэх цэгүүдийг олох
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'M') {
                q_monster.push({i, j});
                monster_dist[i][j] = 0;
            } else if (grid[i][j] == 'A') {
                start_pos = {i, j};
                q_player.push({i, j});
                player_dist[i][j] = 0;
            }
        }
    }

    // 1. BFS for Monsters (Мангасуудын очих хугацааг тооцох)
    while (!q_monster.empty()) {
        pair<int, int> curr = q_monster.front();
        q_monster.pop();

        for (int i = 0; i < 4; i++) {
            int nx = curr.first + dx[i];
            int ny = curr.second + dy[i];

            // Grid дотор байгаа эсэх, Хана биш эсэх, Өмнө нь очоогүй эсэх
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && 
                grid[nx][ny] != '#' && monster_dist[nx][ny] == INF) {
                
                monster_dist[nx][ny] = monster_dist[curr.first][curr.second] + 1;
                q_monster.push({nx, ny});
            }
        }
    }

    // 2. BFS for Player (Тоглогч зугтах замыг хайх)
    // Хэрэв эхлэл нь аль хэдийн зах дээр байвал
    if (start_pos.first == 0 || start_pos.first == n - 1 || 
        start_pos.second == 0 || start_pos.second == m - 1) {
        cout << "YES" << endl;
        cout << 0 << endl;
        return 0;
    }

    pair<int, int> end_pos = {-1, -1};

    while (!q_player.empty()) {
        pair<int, int> curr = q_player.front();
        q_player.pop();

        // Зах дээр ирсэн эсэхийг шалгах
        if (curr.first == 0 || curr.first == n - 1 || 
            curr.second == 0 || curr.second == m - 1) {
            end_pos = curr;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nx = curr.first + dx[i];
            int ny = curr.second + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && 
                grid[nx][ny] != '#' && player_dist[nx][ny] == INF) {
                
                // ГОЛ НӨХЦӨЛ: Мангасаас түрүүлж очих ёстой
                // Миний дараагийн алхам (curr + 1) нь мангасын хугацаанаас бага байх ёстой
                if (player_dist[curr.first][curr.second] + 1 < monster_dist[nx][ny]) {
                    player_dist[nx][ny] = player_dist[curr.first][curr.second] + 1;
                    path[nx][ny] = {curr.first, curr.second, dChar[i]}; // Замаа хадгалах
                    q_player.push({nx, ny});
                }
            }
        }
    }

    if (end_pos.first == -1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        string result_path = "";
        pair<int, int> curr = end_pos;

        // Backtracking
        while (curr != start_pos) {
            Parent p = path[curr.first][curr.second];
            result_path += p.dir;
            curr = {p.x, p.y};
        }

        reverse(result_path.begin(), result_path.end());
        cout << result_path.length() << endl;
        cout << result_path << endl;
    }

    return 0;
}