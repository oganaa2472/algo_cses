#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> board(8);
bool col[8], diag1[16], diag2[16];
int count = 0;

void solve(int r) {
    // 8 хатныг бүгдийг нь байрлуулж дууссан бол нэг боломж оллоо
    if (r == 8) {
        count++;
        return;
    }

    for (int c = 0; c < 8; c++) {
        // Шалгах нөхцөлүүд:
        // 1. Нүд чөлөөтэй (.) байх
        // 2. Багана ашиглагдаагүй байх
        // 3. Хоёр диагональ ашиглагдаагүй байх
        if (board[r][c] == '.' && !col[c] && !diag1[r + c] && !diag2[r - c + 7]) {
            // Хатан тавих (Төлөвийг тэмдэглэх)
            col[c] = diag1[r + c] = diag2[r - c + 7] = true;
            
            // Дараагийн мөр рүү шилжих
            solve(r + 1);
            
            // Буцаад төлөвийг чөлөөлөх (Backtrack)
            col[c] = diag1[r + c] = diag2[r - c + 7] = false;
        }
    }
}

int main() {
    for (int i = 0; i < 8; i++) {
        cin >> board[i];
    }

    solve(0); // 0-р мөрөөс эхэлнэ
    cout << count << endl;

    return 0;
}