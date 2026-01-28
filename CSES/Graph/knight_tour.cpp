#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Морьны 8 нүүдэл
const int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

int board[8][8];

// Нүд хөлөг дотор байгаа эсэх, мөн хоосон эсэхийг шалгах
bool isValid(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8 && board[x][y] == 0;
}

// Тухайн (x, y) нүднээс цааш хэдэн тийшээ нүүж болохыг тоолох (Degree)
int getDegree(int x, int y) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (isValid(x + dx[i], y + dy[i])) {
            count++;
        }
    }
    return count;
}

// Backtracking функц
bool solve(int x, int y, int moveCount) {
    board[x][y] = moveCount;

    // 64 нүд дүүрсэн бол амжилттай дууссан
    if (moveCount == 64) return true;

    // Дараагийн боломжит нүүдлүүдийг хадгалах вектор
    // {degree, index_of_move}
    vector<pair<int, int>> nextMoves;

    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (isValid(nx, ny)) {
            // Warnsdorff's Rule: Дараагийн нүдний degree-г тооцох
            int degree = getDegree(nx, ny);
            nextMoves.push_back({degree, i});
        }
    }

    // Degree-ээр нь өсөх дарааллаар эрэмбэлэх (Heuristic)
    sort(nextMoves.begin(), nextMoves.end());

    // Эрэмбэлэгдсэн дарааллаар туршиж үзэх
    for (auto p : nextMoves) {
        int i = p.second;
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (solve(nx, ny, moveCount + 1)) return true;
    }

    // Хэрэв шийдэл олдохгүй бол буцааж тэглэх (Backtrack)
    board[x][y] = 0;
    return false;
}

int main() {
    // Input/Output хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int startX, startY;
    // CSES дээр X нь багана (col), Y нь мөр (row) байдлаар өгөгддөг.
    // Бидний код x=row, y=col гэж бичигдсэн тул swap хийж болно, 
    // эсвэл зүгээр л (y-1, x-1) гэж дуудна.
    cin >> startX >> startY;

    // 0-based index руу шилжүүлэх (мөр, багана хоёрын байрлалыг анхаарах)
    // startY нь мөр, startX нь багана гэж үзье.
    solve(startY - 1, startX - 1, 1);

    // Хэвлэх
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}