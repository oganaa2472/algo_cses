#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 8;
int board[N][N];
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// Check if a move is valid
bool is_valid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N && board[x][y] == 0;
}

// Count onward moves for Warnsdorff's rule
int count_onward_moves(int x, int y) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (is_valid(nx, ny)) count++;
    }
    return count;
}

// Knight's Tour using Warnsdorff's heuristic
bool knight_tour(int x, int y, int move_num) {
    board[x][y] = move_num;
    if (move_num == N * N) return true;

    vector<pair<int, pair<int, int>>> next_moves;

    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (is_valid(nx, ny)) {
            int onward = count_onward_moves(nx, ny);
            next_moves.push_back({onward, {nx, ny}});
        }
    }

    // Sort by least onward moves (Warnsdorff's rule)
    sort(next_moves.begin(), next_moves.end());

    for (auto& move : next_moves) {
        int nx = move.second.first;
        int ny = move.second.second;
        if (knight_tour(nx, ny, move_num + 1)) return true;
    }

    board[x][y] = 0; // backtrack
    return false;
}

int main() {
    int x, y;
    cin >> x >> y;
    x--; y--; // Convert to 0-based

    // Initialize board with 0s
    for (int i = 0; i < N; i++)
        fill(board[i], board[i] + N, 0);

    if (knight_tour(x, y, 1)) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << board[i][j] << " ";
            cout << "\n";
        }
    } else {
        cout << "No solution found.\n";
    }

    return 0;
}
