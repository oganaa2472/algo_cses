#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

// Чиглэлүүд: Right, Left, Down, Up
// dx, dy болон move_char-ийн дараалал ижил байх ёстой
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
const char move_char[4] = {'R', 'L', 'D', 'U'};

int main() {
    // Input хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    pair<int, int> start, end;

    // Grid унших болон Start/End цэгийг олох
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') start = {i, j};
            if (grid[i][j] == 'B') end = {i, j};
        }
    }

    // BFS эхлүүлэх
    queue<pair<int, int>> q;
    q.push(start);

    // parent[i][j] нь (i, j) нүдэнд ирэхийн тулд хийсэн алхамыг хадгална (U, D, L, R)
    vector<vector<char>> parent(n, vector<char>(m, 0));
    
    // Visited массив
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    visited[start.first][start.second] = true;

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();

        int x = curr.first;
        int y = curr.second;

        // B цэг дээр ирсэн бол зогсоно
        if (x == end.first && y == end.second) {
            break; 
        }

        // 4 зүг рүү шалгах
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // Grid дотор байгаа эсэх, Хана биш эсэх, Өмнө нь очоогүй эсэх
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && 
                grid[nx][ny] != '#' && !visited[nx][ny]) {
                
                visited[nx][ny] = true;
                parent[nx][ny] = move_char[i]; // Ямар үйлдэл хийж ирснээ хадгална
                q.push({nx, ny});
            }
        }
    }

    // Хэрэв B цэгт хүрээгүй бол (parent нь хоосон хэвээрээ)
    if (!visited[end.first][end.second]) {
        cout << "NO" << endl;
        return 0;
    }

    // Backtracking: B-ээс А хүртэл замаа мөшгих
    cout << "YES" << endl;
    string path = "";
    pair<int, int> curr = end;

    while (curr != start) {
        char move = parent[curr.first][curr.second];
        path += move;

        // Буцаж алхах (Coordinate update)
        if (move == 'U') curr.first++;      // U хийж ирсэн бол буцахдаа доошоо явна
        else if (move == 'D') curr.first--; // D хийж ирсэн бол буцахдаа дээшээ явна
        else if (move == 'L') curr.second++;
        else if (move == 'R') curr.second--;
    }

    // Backtrack хийсэн учраас зам маань урвуу байгаа. Түүнийг эргүүлнэ.
    reverse(path.begin(), path.end());

    cout << path.length() << endl;
    cout << path << endl;

    return 0;
}