#include <iostream>
#include <string>

using namespace std;

string target_path;
bool visited[7][7];
int ans = 0;

// Хөлгөөс гарсан эсэхийг шалгах
bool is_valid(int r, int c) {
    return r >= 0 && r < 7 && c >= 0 && c < 7 && !visited[r][c];
}

void solve(int r, int c, int steps) {
    // Хэрэв зорилтот цэгт хүрсэн бол
    if (r == 6 && c == 0) {
        if (steps == 48) ans++;
        return;
    }
    
    // Алхам дууссан бол зогсоно
    if (steps == 48) return;

    // ОНОВЧЛОЛ: Хөлөг хуваагдаж байгаа эсэхийг шалгах
    if ((!is_valid(r + 1, c) && !is_valid(r - 1, c)) && (is_valid(r, c - 1) && is_valid(r, c + 1))) return;
    if ((!is_valid(r, c + 1) && !is_valid(r, c - 1)) && (is_valid(r + 1, c) && is_valid(r - 1, c))) return;

    visited[r][c] = true;
    char move = target_path[steps];

    // Down
    if ((move == '?' || move == 'D') && r < 6 && !visited[r + 1][c]) {
        solve(r + 1, c, steps + 1);
    }
    // Up
    if ((move == '?' || move == 'U') && r > 0 && !visited[r - 1][c]) {
        solve(r - 1, c, steps + 1);
    }
    // Left
    if ((move == '?' || move == 'L') && c > 0 && !visited[r][c - 1]) {
        solve(r, c - 1, steps + 1);
    }
    // Right
    if ((move == '?' || move == 'R') && c < 6 && !visited[r][c + 1]) {
        solve(r, c + 1, steps + 1);
    }

    visited[r][c] = false; // Backtrack
}

int main() {
    cin >> target_path;
    solve(0, 0, 0);
    cout << ans << endl;
    return 0;
}